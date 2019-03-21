# include "../include/m_qam_transmitter_20180815.h"

MQamTransmitter::MQamTransmitter(initializer_list<Signal *> inputSignals, initializer_list<Signal *> outputSignals) : SuperBlock(inputSignals, outputSignals) {
	/*
	//###################################### Default Input Parameters Values #########################################################
	
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

void MQamTransmitter::initialize()
{

	BinaryData_In.setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	BinaryData_In.setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	BinaryData_In.setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	TxLocalOscillator_In.setSymbolPeriod(inputSignals[1]->getSymbolPeriod());
	TxLocalOscillator_In.setSamplingPeriod(inputSignals[1]->getSamplingPeriod());
	TxLocalOscillator_In.setFirstValueToBeSaved(inputSignals[1]->getFirstValueToBeSaved());

	setSuperBlockSystem(
		{	
			&MQamMapper_,
			&DiscreteToContinuousTime_1_,
			&PulseShaper_1_,
			&DiscreteToContinuousTime_2_,
			&PulseShaper_2_,
			&IqModulator_
		}
	);

	outputSignals[0]->setSymbolPeriod(OpticalSignal_Out.getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(OpticalSignal_Out.getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(OpticalSignal_Out.getFirstValueToBeSaved());

	setLogValue(logValue);
	setLogFileName(logFileName);
	setSignalsFolderName(signalsFolderName);
};

bool MQamTransmitter::runBlock()
{

	if (!experimental::filesystem::is_directory(signalsFolderName) || !experimental::filesystem::exists(signalsFolderName)) {
		experimental::filesystem::create_directory(signalsFolderName);
	}

	int ready = inputSignals[0]->ready();
	int space = BinaryData_In.space();
	int process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_binary dataIn;
		inputSignals[0]->bufferGet(&dataIn);
		BinaryData_In.bufferPut(dataIn);
	}

	ready = inputSignals[1]->ready();
	space = TxLocalOscillator_In.space();
	process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_complex opticalIn;
		inputSignals[1]->bufferGet(&opticalIn);
		TxLocalOscillator_In.bufferPut(opticalIn);
	}

	bool alive = SuperBlock::runBlock(signalsFolderName);

	if (firstTime) {
		setOpenFile(false);
		firstTime = false;
	}

	ready = OpticalSignal_Out.ready();
	space = outputSignals[0]->space();

	process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_complex opticalOut = OpticalSignal_Out.bufferGet();
		outputSignals[0]->bufferPut(opticalOut);
	}

	return alive;
}
