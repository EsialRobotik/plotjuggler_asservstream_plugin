#include "AsservStream_uartDecoder.h"
#include <cstdio>
#include <functional>

#define CALL_MEMBER(object,ptrToMember)  ((object).*(ptrToMember))


AsservStream_uartDecoder::AsservStream_uartDecoder()
{
	nbValueInSample = 0;
	currentSample = nullptr;
	nbValues = 0;
	currentState = &AsservStream_uartDecoder::synchroLookUp;
}

void AsservStream_uartDecoder::setNumberValuesInSample(int nbValuesInSample)
{
	nbValueInSample = nbValuesInSample;
	currentSample = new float[nbValueInSample];
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

    if( byte == ((uint8_t*)&synchroWord)[nbSynchroByteFound] )
    {
    	nbSynchroByteFound++;
    }
    else if( byte == ((uint8_t*)&synchroWord_config)[nbSynchroConfigByteFound] )
    {
    	nbSynchroConfigByteFound++;
    }
    else
    {
    	isCurrentSampleValid = false;
    	nbSynchroByteFound = 0;
    	nbSynchroConfigByteFound = 0;
    	printf("drop ..\n");
    }

   if( nbSynchroByteFound == sizeof(synchroWord) )  // Synchro found !
   {
		nbSynchroByteFound = 0;
		nbSynchroConfigByteFound = 0;
		currentState =  &AsservStream_uartDecoder::getRemainingData;

		if( isCurrentSampleValid)
		{
			std::vector<float> sample(currentSample, currentSample+nbValueInSample );
			uint32_t *timestamp = (uint32_t*)&currentSample[0];
			sample[0] = float(*timestamp);
			decodedSampleQueue.push(sample);
		}
   }


   if( nbSynchroConfigByteFound == sizeof(synchroWord_config) )  // config Synchro found !
   {
		nbSynchroByteFound = 0;
		nbSynchroConfigByteFound = 0;
		currentState =  &AsservStream_uartDecoder::getRemainingConfig;


		if( isCurrentSampleValid)
		{
			std::vector<float> sample(currentSample, currentSample+nbValueInSample );
			decodedSampleQueue.push(sample);
		}
   }

}

void AsservStream_uartDecoder::getRemainingData(uint8_t byte)
{
    static int nbByteRead = 0;
    uint8_t *currentDecodedSamplePtr = (uint8_t*)currentSample;
    currentDecodedSamplePtr[nbByteRead++] = byte;


    if(nbByteRead == (nbValueInSample*4))
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
			printf("Read %d bytes \n", nbValues);
    		nbByteRead = 0;
    		nbByteToRead = 0;
    		currentState =  &AsservStream_uartDecoder::synchroLookUp;
    	}
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
