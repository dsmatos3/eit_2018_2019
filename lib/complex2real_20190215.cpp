# include "netxpto_20190215.h"
# include "complex2real_20190215.h"

using namespace std;



void Complex2Real::initialize(void) {

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->
		getFirstValueToBeSaved());
	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->
		getFirstValueToBeSaved());

}



bool Complex2Real::runBlock(void) {


	int ready = inputSignals[0]->ready();

	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[1]->space();
	int space = min(space1, space2);

	int process = min(ready, space);

	if (process == 0) return false;

	// Signal type verification
	signal_value_type sType = inputSignals[0]->getValueType();
	signal_value_type sTypeOut1 = outputSignals[0]->getValueType();
	signal_value_type sTypeOut2 = outputSignals[1]->getValueType();


	// Only real input signals are acceptable.
	if (sTypeOut1 != RealValue) {
		cout << "ERROR: real_to_complex.cpp (input signal0 "
			"signal_value_type not RealValue)\n";
		return false;
	}
	if (sTypeOut2 != RealValue) {
		cout << "ERROR: real_to_complex.cpp (input signal1 "
			"signal_value_type not RealValue)\n";
		return false;
	}
	// Only complex output signals are acceptable.
	if (sType != ComplexValue) {
		cout << "ERROR: real_to_complex.cpp (output signal "
			"signal_value_type not ComplexValue)\n";
		return false;
	}


	// Buffer processing
	t_complex in;
	t_real re, im;
	t_complex valueX;
	for (int i = 0; i < process; i++) {

		inputSignals[0]->bufferGet(&in);

		outputSignals[0]->bufferPut(real(in));
		outputSignals[1]->bufferPut(imag(in));

	}

	return true;
}
