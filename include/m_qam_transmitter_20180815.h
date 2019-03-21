# ifndef M_QAM_TRANSMITTER_H_
# define M_QAM_TRANSMITTER_H_

# include "../include/netxpto_20180815.h"

# include "../include/m_qam_mapper_20180815.h"
# include "../include/discrete_to_continuous_time_20180815.h"
# include "../include/pulse_shaper_20180815.h"
# include "../include/iq_modulator_20180815.h"

class MQamTransmitter : public SuperBlock {

public:

	//##############################################################################################################

	MQamTransmitter(initializer_list<Signal *> inputSig, initializer_list<Signal *> outputSig);

	void initialize(void);
	bool runBlock(void);

	bool firstTime{ true };

	//##############################################################################################################

	// MQamMapper_

	void setM(int mValue) { MQamMapper_.setM(mValue); };
	void setIqAmplitudes(vector<vector<t_real>> iqAmplitudesValues) { MQamMapper_.setIqAmplitudes(iqAmplitudesValues); };

	void setFirstTime(bool fTime) { MQamMapper_.setFirstTime(fTime); }; 
	bool getFirstTime() { return MQamMapper_.getFirstTime(); };

	// DiscreteToContinuousTime_

	void setNumberOfSamplesPerSymbol(int nSamplesPerSymbol) { DiscreteToContinuousTime_1_.setNumberOfSamplesPerSymbol(nSamplesPerSymbol); DiscreteToContinuousTime_2_.setNumberOfSamplesPerSymbol(nSamplesPerSymbol);};
	int const getNumberOfSamplesPerSymbol(void) { return DiscreteToContinuousTime_1_.getNumberOfSamplesPerSymbol(); };

	// PulseShapper_
	void setImpulseResponseTimeLength_symbolPeriods(int impResponseTimeLength) { PulseShaper_1_.setImpulseResponseTimeLength_symbolPeriods(impResponseTimeLength); PulseShaper_2_.setImpulseResponseTimeLength_symbolPeriods(impResponseTimeLength);};
	int const getImpulseResponseTimeLength_symbolPeriods(void) { return PulseShaper_1_.getImpulseResponseTimeLength_symbolPeriods(); };

	void setFilterType(pulse_shapper_filter_type fType) { PulseShaper_1_.setFilterType(fType); PulseShaper_2_.setFilterType(fType);};
	pulse_shapper_filter_type const getFilterType(void) { return PulseShaper_1_.getFilterType(); };

	void setRollOffFactor(double rOffFactor) { PulseShaper_1_.setRollOffFactor(rOffFactor); PulseShaper_2_.setRollOffFactor(rOffFactor);};
	double const getRollOffFactor() { return PulseShaper_1_.getRollOffFactor(); };

	void setPulseWidth(double pWidth) { PulseShaper_1_.setPulseWidth(pWidth); PulseShaper_2_.setPulseWidth(pWidth);};
	double const getPulseWidth() { return PulseShaper_1_.getPulseWidth(); };

	void setPassiveFilterMode(bool pFilterMode) { PulseShaper_1_.setPassiveFilterMode(pFilterMode); PulseShaper_2_.setPassiveFilterMode(pFilterMode);};
	bool const getPassiveFilterMode() { return PulseShaper_1_.getPassiveFilterMode(); };

	//###############################################################################################################

private:

	// #####################################################################################################
	// ################################## Input Parameters #################################################
	// #####################################################################################################

	string signalsFolderName{ "signals/SuperBlock_MQamTransmitter" };
	bool logValue{ true };
	string logFileName{ "SuperBlock_MQamTransmitter.txt" };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary BinaryData_In{ "S0_BinaryData_In.sgn" };
	
	TimeDiscreteAmplitudeContinuousReal MQamMapperOut_1{ "S1_MQamMapperOut_1.sgn" };

	TimeDiscreteAmplitudeContinuousReal MQamMapperOut_2{ "S2_MQamMapperOut_2.sgn" };

	TimeContinuousAmplitudeContinuousReal DiscreteToContinuousTimeOut_1{ "S3_DiscreteToContinuousTimeOut_1.sgn" };

	TimeContinuousAmplitudeContinuousReal DiscreteToContinuousTimeOut_2{ "S4_DiscreteToContinuousTimeOut_2.sgn" };

	TimeContinuousAmplitudeContinuousReal PulseShaperOut_1{ "S5_PulseShaperOut_1.sgn" };

	TimeContinuousAmplitudeContinuousReal PulseShaperOut_2{ "S6_PulseShaperOut_2.sgn" };

	OpticalSignal TxLocalOscillator_In{ "S7_TxLocalOscillator_In.sgn" };

	OpticalSignal OpticalSignal_Out{ "S8_OpticalSignal_Out.sgn" };



	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	MQamMapper MQamMapper_{ { &BinaryData_In},{ &MQamMapperOut_1, &MQamMapperOut_2 } };
	
	DiscreteToContinuousTime DiscreteToContinuousTime_1_{ { &MQamMapperOut_1 },{ &DiscreteToContinuousTimeOut_1 } };

	DiscreteToContinuousTime DiscreteToContinuousTime_2_{ { &MQamMapperOut_2 },{ &DiscreteToContinuousTimeOut_2 } };

	PulseShaper PulseShaper_1_{ { &DiscreteToContinuousTimeOut_1 },{ &PulseShaperOut_1 } };

	PulseShaper PulseShaper_2_{ { &DiscreteToContinuousTimeOut_2 },{ &PulseShaperOut_2 } };

	IqModulator IqModulator_{ { &PulseShaperOut_1, &PulseShaperOut_2, &TxLocalOscillator_In },{ &OpticalSignal_Out } };

};

# endif


