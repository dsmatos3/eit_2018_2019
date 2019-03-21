# include "../include/laser_20180815.h"

void Laser::initialize(void) {

	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setSymbolPeriod(symbolPeriod);

	outputSignals[0]->setCentralWavelength(getWavelength());
	outputSignals[0]->setCentralFrequency(getFrequency());
}


bool Laser::runBlock(void) {

	int process = outputSignals[0]->space();

	if (process == 0) return false;

	double samplingPeriod = outputSignals[0]->getSamplingPeriod();

	t_real phNoiseVar = 2 * PI * laserLineWidth * samplingPeriod;
			
	normal_distribution<double> dist_phaseNoise;
	normal_distribution<double> dist_RIN;
		
	t_real intVar = (1 / samplingPeriod) * laserRIN * pow(opticalPower, 2);

	unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();

	generatorPhaseNoise.seed(seed);

	double cm_phNoise(0.0);
	for (int i = 0; i < process; i++) {

		// Laser phase noise
		t_real phNoise = sqrt(phNoiseVar)*dist_phaseNoise(generatorPhaseNoise); 
		cm_phNoise += phNoise;

		// Laser intensity noise
	    t_real intNoise = sqrt(intVar)*dist_RIN(generatorRIN);

		// Laser transmitted optical field
		phase += cm_phNoise + frequencyMismatch*2*PI*samplingPeriod;
		t_complex out = sqrt((opticalPower + intNoise)/2)*exp(1.0i*phase);

		outputSignals[0]->bufferPut(out);
	}

	return true;
}
