#ifndef ASSERV_STREAM_DECODER_H
#define ASSERV_STREAM_DECODER_H
#include <cstdint>
#include <string>
#include <queue>
#include <vector>

class  AsservStream_uartDecoder
{
public:

	explicit AsservStream_uartDecoder(unsigned int nb_values_maximum_in_sample = 50);
    virtual ~AsservStream_uartDecoder(){};

	void reset();

	void processBytes(uint8_t *buffer, unsigned int nbBytes);
	bool getDecodedSample(std::vector<float> &sample);

	bool getNewDescription(std::vector<std::string> &description);

	uint8_t configBuffer[512];
	uint8_t descriptionBuffer[4*1024];
	int nbValues;
	bool configAvailable = false;

private:
	bool isCurrentSampleValid = false;

	std::queue<std::vector<float>> decodedSampleQueue;
	std::vector<std::string> decodedDescription;
	bool description_available;

	void synchroLookUp(uint8_t byte);
	void getRemainingData(uint8_t byte);
	void getRemainingConfig(uint8_t byte);
	void getRemainingConnectionInformations(uint8_t byte);

	typedef void (AsservStream_uartDecoder::*stateFunction)(uint8_t byte);
	stateFunction currentState;

	int nb_values_maximum_in_sample;
	float *currentSample;

	unsigned int currentSampleSize;


	int synchroLookUp_nbSynchroByteFound;
	int synchroLookUp_nbSynchroConfigByteFound;
	int synchroLookUp_nbSynchroConnectionByteFound;

	int getRemainingData_nbByteRead;

	int getRemainingConfig_nbByteRead;
	int getRemainingConfig_nbByteToRead;

	int getRemainingConnectionInformations_nbByteRead;
	uint32_t getRemainingConnectionInformations_nbByteToRead;
};

#endif

