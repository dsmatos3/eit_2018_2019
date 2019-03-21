# include "../include/m_qam_receiver_20180815.h"

MQamReceiver::MQamReceiver(initializer_list<Signal *> inputSignals, initializer_list<Signal *> outputSignals) : SuperBlock(inputSignals, outputSignals) {

	//###################################### Default Input Parameters Values #########################################################

	/*
	double bitRate{ 1e3 };
	int numberOfBits{ 1000 };
	int frameLength{ 10 };
	int headerLength{ 0 };
	vector<vector<t_real>> iqAmplitudesValues{ { 0, 0, 0, 1 },{ PI / 2, 0, 1,1 },{ -PI / 4, 1, 0, 1 },{ PI / 4, 1, 1, 1 } };
	// the in-phase componente is used to select both the basis and the bit, 00 => 0 (basis=0, bit=0), 01 => PI/2, 10 => -PI/4, 11 => PI/
	// the quadrature componente is used as a clock
	pulse_shapper_filter_type filterType{ pulse_shapper_filter_type::Square };
	int samplesPerSymbol{ 16 };
	//bool logValue{ true };
	//string logFileName{ "SuperBlock_Alice.txt" };
	//string signalsFolderName{ "signals/SuperBlock_Alice" };
	
	
	//############################################# Blocks ##########################################################################

	BinarySource_.setBitPeriod(1 / (2 * bitRate));
//	BinarySource_.setNumberOfBits(numberOfBits);

	QuantumFramer_.setFrameLength(frameLength);
	QuantumFramer_.setHeaderLength(headerLength);

	MQamMapper_.setIqAmplitudes(iqAmplitudesValues);

	DiscreteToContinuousTime_Basis.setNumberOfSamplesPerSymbol(samplesPerSymbol);

	PulseShaper_Basis.setFilterType(filterType);
	PulseShaper_Basis.setPulseWidth(1 / bitRate);

	DiscreteToContinuousTime_Bits.setNumberOfSamplesPerSymbol(samplesPerSymbol);

	PulseShaper_Bits.setFilterType(filterType);
	PulseShaper_Bits.setPulseWidth(1 / bitRate);
	
	DiscreteToContinuousTime_.setNumberOfSamplesPerSymbol(samplesPerSymbol);

	PulseShaper_.setFilterType(filterType);
	PulseShaper_.setSaveImpulseResponse(true);

	DiscreteToContinuousTime_1.setNumberOfSamplesPerSymbol(samplesPerSymbol);

	TimeDelay_.setTimeDelay(1 / bitRate / 2);
	TimeDelay_.setTimeDelay(0);

*/
};

void MQamReceiver::initialize()
{
	OpticalSignal_In.setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	OpticalSignal_In.setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	OpticalSignal_In.setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	LocalOscillator_In.setSymbolPeriod(inputSignals[1]->getSymbolPeriod());
	LocalOscillator_In.setSamplingPeriod(inputSignals[1]->getSamplingPeriod());
	LocalOscillator_In.setFirstValueToBeSaved(inputSignals[1]->getFirstValueToBeSaved());

	setSuperBlockSystem(
		{	
			&OpticalHybrid_,
			&BalancedPhotodetector_1_,
			&BalancedPhotodetector_2_,
			&TiAmplifier_1_,
			&TiAmplifier_2_,
			&ReceiverFilter_1_,
			&ReceiverFilter_2_,
			&WhiteNoise_1_,
			&WhiteNoise_2_,
			&Add_1_,
			&Add_2_,
			&Sampler_1_,
			&Sampler_2_,
			&Decoder_
		}
	);

	outputSignals[0]->setSymbolPeriod(BinaryData_Out.getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(BinaryData_Out.getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(BinaryData_Out.getFirstValueToBeSaved());

	setLogValue(logValue);
	setLogFileName(logFileName);
	setSignalsFolderName(signalsFolderName);
};

bool MQamReceiver::runBlock()
{

	if (!experimental::filesystem::is_directory(signalsFolderName) || !experimental::filesystem::exists(signalsFolderName)) {
		experimental::filesystem::create_directory(signalsFolderName);
	}

	int ready = inputSignals[0]->ready();
	int space = OpticalSignal_In.space();
	int process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_complex opticalIn;
		inputSignals[0]->bufferGet(&opticalIn);
		OpticalSignal_In.bufferPut(opticalIn);
	}

	ready = inputSignals[1]->ready();
	space = LocalOscillator_In.space();
	process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_complex opticalIn;
		inputSignals[1]->bufferGet(&opticalIn);
		LocalOscillator_In.bufferPut(opticalIn);
	}

	bool alive = SuperBlock::runBlock(signalsFolderName);

	if (firstTime) {
		setOpenFile(false);
		firstTime = false;
	}

	ready = BinaryData_Out.ready();
	space = outputSignals[0]->space();

	process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_binary binaryDataOut = BinaryData_Out.bufferGet();
		outputSignals[0]->bufferPut(binaryDataOut);
	}

	return alive;
};
