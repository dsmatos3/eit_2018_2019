# ifndef TI_AMPLIFIER_H_
# define TI_AMPLIFIER_H_

# include "../include/netxpto_20180815.h"

# include "../include/white_noise_20180815.h"
# include "../include/add_20180815.h"
# include "../include/ideal_amplifier_20180815.h"
# include "../include/electrical_filter_20180815.h" 


class TiAmplifier : public SuperBlock {

public:

	//##############################################################################################################

	TiAmplifier(initializer_list<Signal *> inputSignals, initializer_list<Signal *> outputSignals) : SuperBlock(inputSignals, outputSignals) {};
	TiAmplifier(initializer_list<Signal *> inputSignals, initializer_list<Signal *> outputSignals, string sFolderName) : SuperBlock(inputSignals, outputSignals) { signalsFolderName = sFolderName; };

	void initialize(void);
	bool runBlock(void);

	bool firstTime{ true };

	//##############################################################################################################

	void setInputReferredNoisePowerSpectralDensity(double newInputReferredNPDS) { WhiteNoise_.setNoiseSpectralDensity(newInputReferredNPDS); }
	double const getInputReferredNoisePowerSpectralDensity(void) { WhiteNoise_.getNoiseSpectralDensity(); }

	void setNoiseSamplingPeriod(t_real samplingPeriod) { WhiteNoise_.setSamplingPeriod(samplingPeriod); }
	t_real getNoiseSamplingPeriod(void) { return WhiteNoise_.getSamplingPeriod(); };

	void setNoiseSymbolPeriod(t_real symPeriod) { WhiteNoise_.setSymbolPeriod(symPeriod); }
	t_real getNoiseSymbolPeriod(void) { return WhiteNoise_.getSymbolPeriod(); };

	void setGain(double ga) { IdealAmplifier_.setGain(ga); };
	double const getGain(void) { IdealAmplifier_.getGain(); }

	void setFilterType(Filter filterType) { ElectricalFilter_.setFilterType(filterType); };
	double const getFilterType(void) { return ElectricalFilter_.getFilterType(); };

	void setCutoffFrequency(double cutoffFreq) { ElectricalFilter_.setCutoffFrequency(cutoffFreq); };
	double const getCutoffFrequency(void) { return ElectricalFilter_.getCutoffFrequency(); };

	void setImpulseResponseTimeLength(int impResponseTimeLength) { ElectricalFilter_.setImpulseResponseTimeLength(impResponseTimeLength); };
	int const getImpulseResponseTimeLength(void) { return ElectricalFilter_.getImpulseResponseTimeLength(); };

	void setImpulseResponse(vector<t_real> ir) { ElectricalFilter_.setImpulseResponse(ir); };
	vector<t_real> getImpulseResponse(void) { ElectricalFilter_.getImpulseResponse(); };

	void setImpulseResponseFilename(string fName) { ElectricalFilter_.setImpulseResponseFilename(fName); }
	string getImpulseResponseFilename(void) { ElectricalFilter_.getImpulseResponseFilename(); }

	void setImpulseResponseLength(int impResponseLength) { ElectricalFilter_.setImpulseResponseLength(impResponseLength); };
	int const getImpulseResponseLength(void) { return ElectricalFilter_.getImpulseResponseLength(); };

	void setSeeBeginningOfImpulseResponse(bool sBegginingOfImpulseResponse) { ElectricalFilter_.setSeeBeginningOfImpulseResponse(sBegginingOfImpulseResponse); };
	double const getSeeBeginningOfImpulseResponse(void) { return ElectricalFilter_.getSeeBeginningOfImpulseResponse(); };

	//###############################################################################################################

private:

	// #####################################################################################################
	// ################################## Input Parameters #################################################
	// #####################################################################################################

	string signalsFolderName{ "SuperBlock_TiAmplifier" };
	bool logValue{ true };
	string logFileName{ "SuperBlock_TiAmplifier.txt" };

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	TimeContinuousAmplitudeContinuousReal ElectricalSignal_In{ "S0_ElectricalSignal_In.sgn" };
	TimeContinuousAmplitudeContinuousReal WhiteNoiseOut{ "S1_WhiteNoiseOut.sgn" }; // Amplified
	TimeContinuousAmplitudeContinuousReal AddOut{ "S2_AddOut.sgn" }; // Noise
	TimeContinuousAmplitudeContinuousReal IdealAmplifierOut{ "S3_IdealAmplifierOut.sgn" }; // Noisy Amplified Signal
	TimeContinuousAmplitudeContinuousReal ElectricalSignal_Out{ "S4_ElectricalFilterOut.sgn" }; // Filtered Noisy Signal

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	WhiteNoise WhiteNoise_{ {},{&WhiteNoiseOut} };
	Add Add_{ {&ElectricalSignal_In, &WhiteNoiseOut},{ &AddOut } };
	IdealAmplifier IdealAmplifier_{ { &AddOut },{ &IdealAmplifierOut } };
	ElectricalFilter ElectricalFilter_{ { &IdealAmplifierOut }, { &ElectricalSignal_Out } };

};


#endif
