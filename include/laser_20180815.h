# ifndef LASER_H_
# define LASER_H_

# include "../include/netxpto_20180815.h"

class Laser : public Block {

public:

	//##############################################################################################################

	Laser(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) : Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }

	void setSymbolPeriod(double sPeriod) { symbolPeriod = sPeriod; }

	void setOpticalPower(double oPower) { opticalPower = oPower; }

	void setOpticalPower_dBm(double oPower_dBm) { opticalPower = 1e-3*pow(10, oPower_dBm / 10); }

	void setWavelength(double wlength) { outputOpticalWavelength = wlength;  outputOpticalFrequency = SPEED_OF_LIGHT / outputOpticalWavelength; }
	double getWavelength() { return outputOpticalWavelength; }

	void setFrequency(double freq) { outputOpticalFrequency = freq;  outputOpticalWavelength = SPEED_OF_LIGHT / outputOpticalFrequency; }
	double getFrequency() { return outputOpticalFrequency; }

	void setFrequencyMismatch(double fMismatch) { frequencyMismatch = fMismatch; }
	double getFrequenyMismatch() { return frequencyMismatch; }

	void setPhase(double lOscillatorPhase) { phase = lOscillatorPhase; }
	double const getPhase(void) { return phase; }

	void setSignaltoNoiseRatio(double sNoiseRatio) { signaltoNoiseRatio = sNoiseRatio; }
	double const getSignaltoNoiseRatio(void) { return signaltoNoiseRatio; }

	void setLaserLinewidth(double laserLinewidth) { laserLineWidth = laserLinewidth; }
	double getLaserLinewidth() { return laserLineWidth; }

	void setLaserRIN(double lRIN) { laserRIN = lRIN; }
	double getLaserRIN() { return laserRIN; }

	//##############################################################################################################

private:

	/* State Variables */

	double phase{ 0 };

	/* Input Parameters */

	double opticalPower{ 1.0 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	
	double samplingPeriod{ 0.0 };
	double symbolPeriod{ 0.0 };
	double laserLineWidth{ 0.0 };
	double laserRIN{ 0.0 };
	double frequencyMismatch{ 0.0 };

	default_random_engine generatorRIN;
	default_random_engine generatorPhaseNoise;
	double signaltoNoiseRatio{ 0 };

};

#endif 
