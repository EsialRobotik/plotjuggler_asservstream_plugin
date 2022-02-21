#ifndef ASSERV_STREAM_DECODER_H
#define ASSERV_STREAM_DECODER_H
#include <cstdint>
#include <queue>
#include <vector>

class  AsservStream_uartDecoder
{
public:

	AsservStream_uartDecoder();
    virtual ~AsservStream_uartDecoder(){};
    void setNumberValuesInSample(int nbValuesInSample);

	void processBytes(uint8_t *buffer, unsigned int nbBytes);

	bool getDecodedSample(std::vector<float> &sample);

	uint8_t configBuffer[512];
	int nbValues;
	bool configAvailable = false;

private:
	bool isCurrentSampleValid = false;

	std::queue<std::vector<float>> decodedSampleQueue;

	void synchroLookUp(uint8_t byte);
	void getRemainingData(uint8_t byte);
	void getRemainingConfig(uint8_t byte);

	typedef void (AsservStream_uartDecoder::*stateFunction)(uint8_t byte);
	stateFunction currentState;

	int nbValueInSample;
	float *currentSample;
};

#endif

