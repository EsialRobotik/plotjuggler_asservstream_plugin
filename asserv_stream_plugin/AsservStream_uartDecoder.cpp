#include "AsservStream_uartDecoder.h"
#include <cstdio>
#include <functional>
#include <sstream>

#define CALL_MEMBER(object,ptrToMember)  ((object).*(ptrToMember))


AsservStream_uartDecoder::AsservStream_uartDecoder(unsigned int nb_values_maximum_in_sample): nb_values_maximum_in_sample(nb_values_maximum_in_sample), currentSampleSize(0)
{
	currentSample = new float[nb_values_maximum_in_sample];
	currentState = &AsservStream_uartDecoder::synchroLookUp;
    reset();
}


void AsservStream_uartDecoder::reset()
{
    description_available = false;
    nbValues = 0;
    asservFrequency = 1;
	synchroLookUp_nbSynchroByteFound = 0;
	synchroLookUp_nbSynchroConfigByteFound = 0;
	synchroLookUp_nbSynchroConnectionByteFound = 0;
	getRemainingData_nbByteRead = 0;
	getRemainingConfig_nbByteRead = 0;
	getRemainingConfig_nbByteToRead = 0;
	getRemainingConnectionInformations_nbByteRead = 0;
	getRemainingConnectionInformations_nbByteToRead = 0;
}

unsigned int AsservStream_uartDecoder::getAsservFrequency() const
{
    if( asservFrequency == 1)
        printf("asservFrequency is set to the default value, this probably not the expected behaviour :) \n");


    return asservFrequency;
}

void AsservStream_uartDecoder::processBytes(uint8_t *buffer, unsigned int nbBytes)
{
	for(int i=0; i<nbBytes; i++)
		CALL_MEMBER(*this,currentState)(buffer[i]);
}


void AsservStream_uartDecoder::synchroLookUp(uint8_t byte)
{
	constexpr uint32_t synchroWord = 0xCAFED00D;
	constexpr uint32_t synchroWord_config = 0xCAFEDECA;
	constexpr uint32_t synchroWord_connection = 0xDEADBEEF;

	bool publish_sample = false;

    if( byte == ((uint8_t*)&synchroWord)[synchroLookUp_nbSynchroByteFound] )
    {
    	synchroLookUp_nbSynchroByteFound++;
    }
    else if( byte == ((uint8_t*)&synchroWord_config)[synchroLookUp_nbSynchroConfigByteFound] )
    {
    	synchroLookUp_nbSynchroConfigByteFound++;
    }
    else if( byte == ((uint8_t*)&synchroWord_connection)[synchroLookUp_nbSynchroConnectionByteFound] )
    {
        synchroLookUp_nbSynchroConnectionByteFound++;
    }
    else
    {
    	isCurrentSampleValid = false;
    	synchroLookUp_nbSynchroByteFound = 0;
    	synchroLookUp_nbSynchroConfigByteFound = 0;
    	synchroLookUp_nbSynchroConnectionByteFound = 0;
    	printf("drop ..\n");
    }

   if( synchroLookUp_nbSynchroByteFound == sizeof(synchroWord) )  // Synchro found !
   {
        synchroLookUp_nbSynchroByteFound = 0;
        synchroLookUp_nbSynchroConfigByteFound = 0;
        synchroLookUp_nbSynchroConnectionByteFound = 0;
		currentState =  &AsservStream_uartDecoder::getRemainingData;

		if( isCurrentSampleValid)
		{
		    publish_sample = true;
		}
   }

   if( synchroLookUp_nbSynchroConfigByteFound == sizeof(synchroWord_config) )  // config Synchro found !
   {
       synchroLookUp_nbSynchroByteFound = 0;
       synchroLookUp_nbSynchroConfigByteFound = 0;
       synchroLookUp_nbSynchroConnectionByteFound = 0;
		currentState =  &AsservStream_uartDecoder::getRemainingConfig;

		if( isCurrentSampleValid)
		{
		    publish_sample = true;
		}
   }

   if( synchroLookUp_nbSynchroConnectionByteFound == sizeof(synchroWord_connection) )  // config Synchro found !
   {
        printf("description message! ..\n");
        synchroLookUp_nbSynchroByteFound = 0;
        synchroLookUp_nbSynchroConfigByteFound = 0;
        synchroLookUp_nbSynchroConnectionByteFound = 0;
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
    uint8_t *currentDecodedSamplePtr = (uint8_t*)currentSample;
    currentDecodedSamplePtr[getRemainingData_nbByteRead++] = byte;

    if( currentSampleSize == 0 && getRemainingData_nbByteRead == sizeof(uint32_t) )
    {
        // The first 32bit was read, it contains the total sample size.
        currentSampleSize = *((uint32_t*)currentDecodedSamplePtr);
        getRemainingData_nbByteRead = 0;


        if( currentSampleSize  > nb_values_maximum_in_sample*sizeof(float))
        {
            printf("Want to retrieve %d sample in the stream.... probably garbage ?\n", currentSampleSize);
            // probably garbage !
            getRemainingData_nbByteRead = 0;
            currentState =  &AsservStream_uartDecoder::synchroLookUp;
            isCurrentSampleValid = false;
        }
    }

    if(currentSampleSize > 0 && getRemainingData_nbByteRead == currentSampleSize)
    {   
        getRemainingData_nbByteRead = 0;
		currentState =  &AsservStream_uartDecoder::synchroLookUp;
		isCurrentSampleValid = true;
	}
}

void AsservStream_uartDecoder::getRemainingConfig(uint8_t byte)
{
    configBuffer[getRemainingConfig_nbByteRead++] = byte;

    if( getRemainingConfig_nbByteToRead == 0 && getRemainingConfig_nbByteRead == sizeof(uint32_t) )
    {
        uint32_t *ptr = (uint32_t*)configBuffer;
    	getRemainingConfig_nbByteToRead = *ptr;
        configBufferSize = getRemainingConfig_nbByteToRead;
    	printf("%d bytes to read for configuration \n", configBufferSize);
    	getRemainingConfig_nbByteRead = 0;
    }

    if( getRemainingConfig_nbByteToRead > 0 && getRemainingConfig_nbByteRead == getRemainingConfig_nbByteToRead)
	{
	  configBuffer[getRemainingConfig_nbByteRead] = 0;
	  getRemainingConfig_nbByteRead = 0;
	  getRemainingConfig_nbByteToRead = 0;
	  currentState =  &AsservStream_uartDecoder::synchroLookUp;
	  configAvailable = true;
	}


}

void AsservStream_uartDecoder::getRemainingConnectionInformations(uint8_t byte)
{
    descriptionBuffer[getRemainingConnectionInformations_nbByteRead++] = byte;

    if( getRemainingConnectionInformations_nbByteToRead == 0 && getRemainingConnectionInformations_nbByteRead == sizeof(uint32_t) )
    {
        uint32_t *ptr = (uint32_t*)descriptionBuffer;
    	getRemainingConnectionInformations_nbByteToRead = *ptr;
    	printf("%d bytes to read for description \n", getRemainingConnectionInformations_nbByteToRead);
    	getRemainingConnectionInformations_nbByteRead = 0;
    }

    if( getRemainingConnectionInformations_nbByteToRead > 0 && getRemainingConnectionInformations_nbByteRead == getRemainingConnectionInformations_nbByteToRead)
    {
        descriptionBuffer[getRemainingConnectionInformations_nbByteRead] = 0;
        getRemainingConnectionInformations_nbByteRead = 0;
        getRemainingConnectionInformations_nbByteToRead = 0;
        currentState =  &AsservStream_uartDecoder::synchroLookUp;

        std::string str((char*)descriptionBuffer);
        std::stringstream s_stream(str);
        while(s_stream.good())
        {
            std::string substr;
            getline(s_stream, substr, ','); //get first string delimited by comma

            std::string freq_str("freq=");
            int freqFind = substr.find(freq_str);


            if(substr.length() > 0 && freqFind == -1 ) // Ie: a description has been found and the substring isn't the asserv frequency !
            {
                decodedDescription.push_back(substr);
            }
            else if(freqFind == 0 )
            {
                substr.erase(0, freq_str.size());
                asservFrequency = atoi(substr.c_str());
                printf("Found freq => %d\n", asservFrequency);
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

