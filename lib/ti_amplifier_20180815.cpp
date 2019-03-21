# include "../include/ti_amplifier_20180815.h"


void TiAmplifier::initialize()
{
	ElectricalSignal_In.setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	ElectricalSignal_In.setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	ElectricalSignal_In.setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	setSuperBlockSystem(
		{
			&WhiteNoise_,
			&Add_,
			&IdealAmplifier_,
			&ElectricalFilter_
		}
	);

	outputSignals[0]->setSymbolPeriod(ElectricalSignal_Out.getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(ElectricalSignal_Out.getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(ElectricalSignal_Out.getFirstValueToBeSaved());

	setLogValue(logValue);
	setLogFileName(logFileName);
	setSignalsFolderName(signalsFolderName);
};

bool TiAmplifier::runBlock()
{

	if (!experimental::filesystem::is_directory(signalsFolderName) || !experimental::filesystem::exists(signalsFolderName)) {
		experimental::filesystem::create_directory(signalsFolderName);
	}

	int ready = inputSignals[0]->ready();
	int space = ElectricalSignal_In.space();
	int process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_real signalIn;
		inputSignals[0]->bufferGet(&signalIn);
		ElectricalSignal_In.bufferPut(signalIn);
	}

	bool alive = SuperBlock::runBlock(signalsFolderName);

	if (firstTime) {
		setOpenFile(false);
		firstTime = false;
	}

	ready = ElectricalSignal_Out.ready();
	space = outputSignals[0]->space();

	process = min(ready, space);

	for (auto k = 0; k != process; k++)
	{
		t_real signalOut = ElectricalSignal_Out.bufferGet();
		outputSignals[0]->bufferPut(signalOut);
	}

	return alive;
}