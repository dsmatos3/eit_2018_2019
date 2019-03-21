# include "optical_filter_20190215.h"


OpticalFilter::OpticalFilter(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal) :SuperBlock(inputSignal, outputSignal) {
	/*	inputSignals = inputSignal;
		outputSignals = outputSignal;

		numberOfInputSignals = inputSignal.size();
		numberOfOutputSignals = outputSignal.size();
		*/
	setSaveInternalSignals(true);
	
	B1.initializeBlock(vector<Signal *> { inputSignals[0] }, vector<Signal *> {&OPT_FILT01, &OPT_FILT02});    // Complex2Real
	 
	B2.initializeBlock(vector<Signal *> {&OPT_FILT01}, vector<Signal *> {&OPT_FILT03});                       // Real Filter
	B2.setCutoffFrequency(bandwidth / 2);
	B2.setFilterType(filterType);
	B2.setImpulseResponseTimeLength(impulseResponseTimeLength);
	
	B3.initializeBlock(vector<Signal *> {&OPT_FILT02}, vector<Signal *> {&OPT_FILT04});                       // Imag Filter
	B3.setCutoffFrequency(bandwidth / 2);
	B3.setFilterType(filterType);
	B3.setImpulseResponseTimeLength(impulseResponseTimeLength);

	B4.initializeBlock(vector<Signal *> {&OPT_FILT03, &OPT_FILT04}, vector<Signal *> {outputSignals[0]});          // Real2Complex
	setModuleBlocks({ &B1, &B2, &B3, &B4 });

};

void OpticalFilter::setDirName(string newDirName) {
	dirName = newDirName;
	OPT_FILT01.setFolderName(dirName);
	OPT_FILT02.setFolderName(dirName);
	OPT_FILT03.setFolderName(dirName);
	OPT_FILT04.setFolderName(dirName);
}