# ifndef PHOTODIODE_H_
# define PHOTODIODE_H_

# include "..\include\netxpto_20180815.h"

class BalancedPhotodetector : public Block {

public:

	//##############################################################################################################

	BalancedPhotodetector(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :Block(InputSig, OutputSig) {};
	//Photodiode(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};
	//Photodiode() {};

	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setResponsivity(t_real Responsivity) { responsivity = Responsivity; }
	double const getResponsivity(void) { return responsivity; }

	void useNoise(bool sNoise) { shotNoise = sNoise; }

	void useThermalNoise(bool sNoise) { thermalNoise = sNoise; }
	void setThermalNoiseAmplitude(double amplitude) { thermalNoiseAmplitude = amplitude; }
	double const getThermalNoiseAmplitude(void) { return thermalNoiseAmplitude; };

	//##############################################################################################################


private:

	bool firstTime{ true };
	int aux = 0;
	bool firstPass{ true };
	double t = 0;

	double frequencyMismatch{ 0 };
	double responsivity = 1;
	bool shotNoise{ false };

	bool thermalNoise{ false };
	t_real thermalNoiseAmplitude = 4.7626e-06;

	default_random_engine generatorAmp1;
	default_random_engine generatorAmp2;

};

#endif 
