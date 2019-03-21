# ifndef WHITE_NOISE_H_
# define WHITE_NOISE_H_

# include "..\include\netxpto_20180815.h"

enum SeedType { RandomDevice, DefaultDeterministic, SingleSelected};

class WhiteNoise : public Block {

public:

	//##############################################################################################################

	WhiteNoise(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :Block(InputSig, OutputSig) {};
	//MQamMapper(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};
	//MQamMapper() {};

	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setSamplingPeriod(double sPeriod) {
		samplingPeriod = sPeriod;
		if (constantPower)
		{
			spectralDensity = noisePower * (samplingPeriod); // Update noise power when sampling period changes
		}
		else {
			noisePower = spectralDensity * (1 / samplingPeriod); // Update noise power when spectral density changes
		}

	};
	double getSamplingPeriod(void) { return samplingPeriod; };

	void setSymbolPeriod(double symPeriod) { symbolPeriod = symPeriod; };
	double getSymbolPeriod(void) { return symbolPeriod; };

	void setNoiseSpectralDensity(double SpectralDensity) {
		spectralDensity = SpectralDensity;
		noisePower = spectralDensity * (1 / samplingPeriod); // Update noise power when sampling period changes
	}

	void setNoisePower(double np) {
		noisePower = np;
		spectralDensity = noisePower * (samplingPeriod); // Update noise power when sampling period changes
	}

	void setConstantPower(bool cp) { constantPower = cp; };

	double const getNoiseSpectralDensity(void) { return spectralDensity; }

	void setSeedType(SeedType sType) { seedType = sType; };
	SeedType const getSeedType(void) { return seedType; };

	void setSeed(int newSeed) { seed = newSeed; }
	int getSeed(void) { return seed; }


private:

	bool firstTime{ true };

	SeedType seedType{ RandomDevice };

	random_device randomDevice;

	default_random_engine generator1;
	default_random_engine generator2;
	default_random_engine generator3;
	default_random_engine generator4;

	array<int, std::mt19937::state_size> seed_data;

	int seed{ 1 };

	double spectralDensity{ 1.5e-17 };		// Spectral density is considered to be one sided. If two sided, pass half the value.
	double samplingPeriod{ 1.0 };
	double symbolPeriod{ 1.0 };
	double noisePower{ spectralDensity * 1 / samplingPeriod };
	bool constantPower{ 0 };

};


#endif
