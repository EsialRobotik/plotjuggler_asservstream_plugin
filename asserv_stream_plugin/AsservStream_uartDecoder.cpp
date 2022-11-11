#include "AsservStream_uartDecoder.h"
#include <cstdio>
#include <functional>
#include <sstream>

#define CALL_MEMBER(object,ptrToMember)  ((object).*(ptrToMember))


AsservStream_uartDecoder::AsservStream_uartDecoder(unsigned int nb_values_maximum_in_sample): nb_values_maximum_in_sample(nb_values_maximum_in_sample), currentSampleSize(0)
{
    description_available = false;
	currentSample = new float[nb_values_maximum_in_sample];
	nbValues = 0;
	currentState = &AsservStream_uartDecoder::synchroLookUp;
}



void AsservStream_uartDecoder::processBytes(uint8_t *buffer, unsigned int nbBytes)
{
	for(int i=0; i<nbBytes; i++)
		CALL_MEMBER(*this,currentState)(buffer[i]);
}


void AsservStream_uartDecoder::synchroLookUp(uint8_t byte)
{
	constexpr uint32_t synchroWord = 0xCAFED00D;
	static int nbSynchroByteFound = 0;

	constexpr uint32_t synchroWord_config = 0xCAFEDECA;
	static int nbSynchroConfigByteFound = 0;

	constexpr uint32_t synchroWord_connection = 0xDEADBEEF;
	static int nbSynchroConnectionByteFound = 0;

	bool publish_sample = false;

    if( byte == ((uint8_t*)&synchroWord)[nbSynchroByteFound] )
    {
    	nbSynchroByteFound++;
    }
    else if( byte == ((uint8_t*)&synchroWord_config)[nbSynchroConfigByteFound] )
    {
    	nbSynchroConfigByteFound++;
    }
    else if( byte == ((uint8_t*)&synchroWord_connection)[nbSynchroConnectionByteFound] )
    {
        nbSynchroConnectionByteFound++;
    }
    else
    {
    	isCurrentSampleValid = false;
    	nbSynchroByteFound = 0;
    	nbSynchroConfigByteFound = 0;
    	nbSynchroConnectionByteFound = 0;
    	printf("drop ..\n");
    }

   if( nbSynchroByteFound == sizeof(synchroWord) )  // Synchro found !
   {
        nbSynchroByteFound = 0;
        nbSynchroConfigByteFound = 0;
        nbSynchroConnectionByteFound = 0;
		currentState =  &AsservStream_uartDecoder::getRemainingData;

		if( isCurrentSampleValid)
		{
		    publish_sample = true;
		}
   }

   if( nbSynchroConfigByteFound == sizeof(synchroWord_config) )  // config Synchro found !
   {
       nbSynchroByteFound = 0;
       nbSynchroConfigByteFound = 0;
       nbSynchroConnectionByteFound = 0;
		currentState =  &AsservStream_uartDecoder::getRemainingConfig;

		if( isCurrentSampleValid)
		{
		    publish_sample = true;
		}
   }

   if( nbSynchroConnectionByteFound == sizeof(synchroWord_connection) )  // config Synchro found !
   {
       printf("description message! ..\n");
       nbSynchroByteFound = 0;
       nbSynchroConfigByteFound = 0;
       nbSynchroConnectionByteFound = 0;
		currentState =  &AsservStream_uartDecoder::getRemainingConnectionInformations;

		if( isCurrentSampleValid)
		{
		    publish_sample = true;
		}
   }


   if( publish_sample)
   {
       std::vector<float> sample(currentSample, &currentSample[currentSampleSize/sizeof(float)] );
       decodedSampleQueue.push(sample);
       isCurrentSampleValid = false;
       currentSampleSize = 0;
   }

}

void AsservStream_uartDecoder::getRemainingData(uint8_t byte)
{
    static int nbByteRead = 0;

    uint8_t *currentDecodedSamplePtr = (uint8_t*)currentSample;
    currentDecodedSamplePtr[nbByteRead++] = byte;

    if( currentSampleSize == 0 && nbByteRead == sizeof(uint32_t) )
    {
        // The first 32bit was read, it contains the total sample size.
        currentSampleSize = *((uint32_t*)currentDecodedSamplePtr);
        nbByteRead = 0;


        if( currentSampleSize  > nb_values_maximum_in_sample*sizeof(float))
        {
            printf("Want to retrieve %d sample in the stream.... probably garbage ?\n", currentSampleSize);
            // probably garbage !
            nbByteRead = 0;
            currentState =  &AsservStream_uartDecoder::synchroLookUp;
            isCurrentSampleValid = false;
        }
    }

    if(currentSampleSize > 0 && nbByteRead == currentSampleSize)
    {   
        nbByteRead = 0;
		currentState =  &AsservStream_uartDecoder::synchroLookUp;
		isCurrentSampleValid = true;
	}
}

void AsservStream_uartDecoder::getRemainingConfig(uint8_t byte)
{
    static int nbByteRead = 0;
    static int nbByteToRead = 0;

    if( nbByteToRead == 0 )
    {
    	nbByteToRead = byte;
    }
    else
    {
    	configBuffer[nbByteRead++] = byte;
    	if( nbByteRead == nbByteToRead)
    	{
    		nbValues = nbByteRead;
    		configAvailable = true;
    		nbByteRead = 0;
    		nbByteToRead = 0;
    		currentState =  &AsservStream_uartDecoder::synchroLookUp;
    	}
    }

}

void AsservStream_uartDecoder::getRemainingConnectionInformations(uint8_t byte)
{
    static int nbByteRead = 0;
    static uint32_t nbByteToRead = 0;

    descriptionBuffer[nbByteRead++] = byte;

    if( nbByteToRead == 0 && nbByteRead == sizeof(uint32_t) )
    {
        uint32_t *ptr = (uint32_t*)descriptionBuffer;
    	nbByteToRead = *ptr;
    	printf("read %d bytes for descr\n", nbByteToRead);
    	nbByteRead = 0;
    }

    if( nbByteToRead > 0 && nbByteRead == nbByteToRead)
    {
        descriptionBuffer[nbByteRead] = 0;
        nbByteRead = 0;
        nbByteToRead = 0;
        currentState =  &AsservStream_uartDecoder::synchroLookUp;

        std::string str((char*)descriptionBuffer);
        std::stringstream s_stream(str);
        while(s_stream.good())
        {
            std::string substr;
            getline(s_stream, substr, ','); //get first string delimited by comma
            if(substr.length() > 0 )
            {
                decodedDescription.push_back(substr);
            }
        }
        description_available = true;
    }
}

bool AsservStream_uartDecoder::getDecodedSample(std::vector<float> &sample)
{
	if(decodedSampleQueue.empty() )
		return false;
	sample = decodedSampleQueue.front();
	decodedSampleQueue.pop();
	return true;
}


bool AsservStream_uartDecoder::getNewDescription(std::vector<std::string> &description)
{
    if( description_available )
    {
        description = decodedDescription;
        description_available = false;
        return true;
    }
    else
    {
        return false;
    }


}

