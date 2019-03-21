# ifndef IDEAL_AMPLIFIER_H_
# define IDEAL_AMPLIFIER_H_

# include "..\include\netxpto_20180815.h"

class IdealAmplifier : public Block {

public:

	//##############################################################################################################

	IdealAmplifier(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :Block(InputSig, OutputSig) {};
	//MQamMapper(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};
	//MQamMapper() {};

	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setGain(double ga) { gain = ga; }
	double getGain() { return gain; }

	//##############################################################################################################

private:

	double gain{ 1e4 };

};

#endif
