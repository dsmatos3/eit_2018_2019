# ifndef M_QAM_RECEIVER_H_
# define M_QAM_RECEIVER_H_

# include "../include/netxpto_20180815.h"

# include "../include/optical_hybrid_20180815.h"
# include "../include/balanced_photodetector_20180815.h"
# include "../include/ti_amplifier_20180815.h"
# include "../include/pulse_shaper_20180815.h"
# include "../include/white_noise_20180815.h"
# include "../include/add_20180815.h"
# include "../include/sampler_20180815.h"
# include "../include/decoder_20180815.h"

class MQamReceiver : public SuperBlock {

public:

	//##############################################################################################################

	MQamReceiver(initializer_list<Signal *> inputSig, initializer_list<Signal *> outputSig);

	void initialize(void);
	bool runBlock(void);

	bool firstTime{ true };

	//##############################################################################################################

	// Photodiodes config
	void  setPhotodiodesResponsivity(t_real Responsivity) { BalancedPhotodetector_1_.setResponsivity(Responsivity); BalancedPhotodetector_2_.setResponsivity(Responsivity); };

	// TI Amplifier config
	void setGain(t_real gain) { TiAmplifier_1_.setGain(gain); TiAmplifier_2_.setGain(gain); };
	t_real getGain(void) { TiAmplifier_1_.getGain(); };

	void setAmplifierInputNoisePowerSpectralDensity(t_real NoiseSpectralDensity) { TiAmplifier_1_.setInputReferredNoisePowerSpectralDensity(NoiseSpectralDensity); TiAmplifier_2_.setInputReferredNoisePowerSpectralDensity(NoiseSpectralDensity); };
	t_real getAmplifierInputNoisePowerSpectralDensity(void) { TiAmplifier_1_.getInputReferredNoisePowerSpectralDensity(); };

	void setTiAmplifierFilterType(Filter fType) { TiAmplifier_1_.setFilterType(fType); TiAmplifier_2_.setFilterType(fType); };

	void setTiAmplifierCutoffFrequency(double ctfFreq) { TiAmplifier_1_.setCutoffFrequency(ctfFreq); TiAmplifier_2_.setCutoffFrequency(ctfFreq); }

	void setTiAmplifierImpulseResponseTimeLength_symbolPeriods(int irl) { TiAmplifier_1_.setImpulseResponseTimeLength(irl);  TiAmplifier_2_.setImpulseResponseTimeLength(irl); }

	void setElectricalFilterImpulseResponse(vector<t_real> ir) { TiAmplifier_1_.setImpulseResponse(ir); TiAmplifier_2_.setImpulseResponse(ir);; }

	void setElectricalImpulseResponseFilename(string fName) { TiAmplifier_1_.setImpulseResponseFilename(fName); TiAmplifier_2_.setImpulseResponseFilename(fName); }

	void setElectricalSeeBeginningOfImpulseResponse(bool sBeginningOfImpulseResponse) { TiAmplifier_1_.setSeeBeginningOfImpulseResponse(sBeginningOfImpulseResponse); TiAmplifier_2_.setSeeBeginningOfImpulseResponse(sBeginningOfImpulseResponse); };
	double const getElectricalSeeBeginningOfImpulseResponse(void) { return TiAmplifier_1_.getSeeBeginningOfImpulseResponse(); };

	// General Noise
	void setNoiseSamplingPeriod(t_real SamplingPeriod) {WhiteNoise_1_.setSamplingPeriod(SamplingPeriod); WhiteNoise_2_.setSamplingPeriod(SamplingPeriod); TiAmplifier_1_.setNoiseSamplingPeriod(SamplingPeriod); TiAmplifier_2_.setNoiseSamplingPeriod(SamplingPeriod); };
	void setNoiseSymbolPeriod(t_real nSymbolPeriod) { WhiteNoise_1_.setSymbolPeriod(nSymbolPeriod); WhiteNoise_2_.setSymbolPeriod(nSymbolPeriod); TiAmplifier_1_.setNoiseSymbolPeriod(nSymbolPeriod); TiAmplifier_2_.setNoiseSymbolPeriod(nSymbolPeriod); };

	// Thermal noise config
	void setThermalNoiseSpectralDensity(t_real NoiseSpectralDensity) { WhiteNoise_1_.setNoiseSpectralDensity(NoiseSpectralDensity); WhiteNoise_2_.setNoiseSpectralDensity(NoiseSpectralDensity); };
	void setThermalNoisePower(t_real NoiseSpectralDensity) { WhiteNoise_1_.setNoisePower(NoiseSpectralDensity); WhiteNoise_2_.setNoisePower(NoiseSpectralDensity); };
	void setThermalConstantPower(bool cp) { WhiteNoise_1_.setConstantPower(cp); WhiteNoise_2_.setConstantPower(cp); };
	void setSeeds(array<int, 2> noiseSeeds) { WhiteNoise_1_.setSeed(noiseSeeds[0]); WhiteNoise_2_.setSeed(noiseSeeds[1]); };
	void setSeedType(SeedType seedType) { WhiteNoise_1_.setSeedType(seedType); WhiteNoise_2_.setSeedType(seedType); };


	// Pulse shaper config
	void setImpulseResponseTimeLength(int impResponseTimeLength) { ReceiverFilter_1_.setImpulseResponseTimeLength_symbolPeriods(impResponseTimeLength); ReceiverFilter_2_.setImpulseResponseTimeLength_symbolPeriods(impResponseTimeLength); };
	void setFilterType(pulse_shapper_filter_type fType) { ReceiverFilter_1_.setFilterType(fType); ReceiverFilter_2_.setFilterType(fType); };
	void setRollOffFactor(double rOffFactor) { ReceiverFilter_1_.setRollOffFactor(rOffFactor);  ReceiverFilter_2_.setRollOffFactor(rOffFactor); };
	void usePassiveFilterMode(bool pFilterMode) { ReceiverFilter_1_.setPassiveFilterMode(pFilterMode); ReceiverFilter_2_.setPassiveFilterMode(pFilterMode); }
	void setRrcNormalizeEnergy(bool ne) { ReceiverFilter_1_.setRrcNormalizeEnergy(ne); ReceiverFilter_2_.setRrcNormalizeEnergy(ne); };
	void setMFImpulseResponseFilename(string fName) { ReceiverFilter_1_.setImpulseResponseFilename(fName); ReceiverFilter_2_.setImpulseResponseFilename(fName); }
	void setMFSeeBeginningOfImpulseResponse(bool sBeginningOfImpulseResponse) { ReceiverFilter_1_.setSeeBeginningOfImpulseResponse(sBeginningOfImpulseResponse); ReceiverFilter_2_.setSeeBeginningOfImpulseResponse(sBeginningOfImpulseResponse); };
	double const getMFSeeBeginningOfImpulseResponse(void) { return ReceiverFilter_1_.getSeeBeginningOfImpulseResponse(); };

	// Sampler config
	void setSamplesToSkip(int sToSkip) { Sampler_1_.setSamplesToSkip(sToSkip); Sampler_2_.setSamplesToSkip(sToSkip); };
	//void setSamplerOpticalPower_dBm(double optPower_dBm) { B14.setOutputOpticalPower_dBm(optPower_dBm); B15.setOutputOpticalPower_dBm(optPower_dBm); };


	// Decoder config
	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues) { Decoder_.setIqAmplitudes(iqAmplitudesValues); };
	vector<t_iqValues> const getIqAmplitudes(void) { return Decoder_.getIqAmplitudes(); };



	/*
	// Amplifier config
	void setAmplification(t_real Amplification) { B04.setGain(Amplification); B05.setGain(Amplification); };
	*/

	//##############################################################################################################

private:

	// #####################################################################################################
	// ################################## Input Parameters #################################################
	// #####################################################################################################

	string signalsFolderName{ "signals/SuperBlock_MQamReceiver" };
	bool logValue{ true };
	string logFileName{ "SuperBlock_MQamReceiver.txt" };

	//double samplingPeriod{ 0.0 };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	OpticalSignal OpticalSignal_In{ "S0_OpticalSignal_In.sgn" };
	OpticalSignal LocalOscillator_In{ "S1_LocalOscillator_In.sgn" };

	OpticalSignal OpticalHybridOut_S_Plus_L{ "S2_OpticalHybridOut_S_Plus_L.sgn" }; // S+L
	OpticalSignal OpticalHybridOut_S_Minus_L{ "S3_OpticalHybridOut_S_Minus_L.sgn" }; // S-L
	OpticalSignal OpticalHybridOut_S_Plus_iL{ "S4_OpticalHybridOut_S_Plus_iL.sgn" }; // S+iL
	OpticalSignal OpticalHybridOut_S_Minus_iL{ "S5_OpticalHybridOut_S_Minus_iL.sgn" }; // S-iL

	TimeContinuousAmplitudeContinuousReal BalancedPhotodetectorOut_1{ "S6_BalancedPhotodetectorOut_1.sgn" }; // Photodiode's output
	TimeContinuousAmplitudeContinuousReal BalancedPhotodetectorOut_2{ "S7_BalancedPhotodetectorOut_2.sgn" }; // Photodiode's output

	TimeContinuousAmplitudeContinuousReal TiAmplifierOut_1{ "S8_TiAmplifierOut_1.sgn" }; // TI_Amplifier output
	TimeContinuousAmplitudeContinuousReal TiAmplifierOut_2{ "S9_TiAmplifierOut_2.sgn" }; // TI_Amplifier output

	TimeContinuousAmplitudeContinuousReal ReceiverFilterOut_1{ "S10_ReceiverFilterOut_1.sgn" }; // Filtered
	TimeContinuousAmplitudeContinuousReal ReceiverFilterOut_2{ "S11_ReceiverFilterOut_2.sgn" }; // Filtered

	TimeContinuousAmplitudeContinuousReal WhiteNoiseOut_1{ "S12_WhiteNoiseOut_1.sgn" }; // White noise
	TimeContinuousAmplitudeContinuousReal WhiteNoiseOut_2{ "S13_WhiteNoiseOut_2.sgn" }; // White noise

	TimeContinuousAmplitudeContinuousReal AddOut_1{ "S14_AddOut_1.sgn" }; // Add
	TimeContinuousAmplitudeContinuousReal AddOut_2{ "S15_AddOut_2.sgn" }; // Add

	TimeDiscreteAmplitudeContinuousReal SamplerOut_1{ "S16_SamplerOut_1.sgn" }; // Sampled 
	TimeDiscreteAmplitudeContinuousReal SamplerOut_2{ "S17_SamplerOut_2.sgn" }; // Sampled 

	Binary BinaryData_Out{ "S18_Binary_Data_Out.sgn" }; // recovery Sequence


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	OpticalHybrid OpticalHybrid_{ {&OpticalSignal_In, &LocalOscillator_In },{ &OpticalHybridOut_S_Plus_L, &OpticalHybridOut_S_Minus_L, &OpticalHybridOut_S_Plus_iL, &OpticalHybridOut_S_Minus_iL } };

	BalancedPhotodetector BalancedPhotodetector_1_{ { &OpticalHybridOut_S_Plus_L, &OpticalHybridOut_S_Minus_L }, { &BalancedPhotodetectorOut_1 } };
	BalancedPhotodetector BalancedPhotodetector_2_{ { &OpticalHybridOut_S_Plus_iL, &OpticalHybridOut_S_Minus_iL }, { &BalancedPhotodetectorOut_2 } };
	
	TiAmplifier TiAmplifier_1_{ { &BalancedPhotodetectorOut_1 }, { &TiAmplifierOut_1 }, "signals/SuperBlock_MQamReceiver/TiAmplifier_1" };
	TiAmplifier TiAmplifier_2_{ { &BalancedPhotodetectorOut_2 }, { &TiAmplifierOut_2 }, "signals/SuperBlock_MQamReceiver/TiAmplifier_2" };

	PulseShaper ReceiverFilter_1_{ { &TiAmplifierOut_1 },{ &ReceiverFilterOut_1 } }; // Matched Filter
	PulseShaper ReceiverFilter_2_{ { &TiAmplifierOut_2 },{ &ReceiverFilterOut_2 } }; // Matched Filter

	WhiteNoise WhiteNoise_1_{ {},{ &WhiteNoiseOut_1 } };
	WhiteNoise WhiteNoise_2_{ {},{ &WhiteNoiseOut_2 } };

	Add Add_1_{ { &ReceiverFilterOut_1, &WhiteNoiseOut_1 },{ &AddOut_1 } };
	Add Add_2_{ { &ReceiverFilterOut_2, &WhiteNoiseOut_2 },{ &AddOut_2 } };

	Sampler Sampler_1_{ { &AddOut_1 },{ &SamplerOut_1 } };
	Sampler Sampler_2_{ { &AddOut_2 },{ &SamplerOut_2 } };
	
	Decoder Decoder_{ { &SamplerOut_1, &SamplerOut_2 },{ &BinaryData_Out } };

};

#endif
