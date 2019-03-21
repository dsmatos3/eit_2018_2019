# ifndef SAMPLER_H_
# define SAMPLER_H_

# include "..\include\netxpto_20180815.h"


class Sampler : public Block {

public:

	//##############################################################################################################

	Sampler(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setSamplesToSkip(int sToSkip) { samplesToSkip = sToSkip; }
	int const getSamplesToSkip(void) { return samplesToSkip; }

	//##############################################################################################################

private:

	bool firstTime{ true };


	bool firstPass{ true };
	bool repeatedPass{ false };
	int samplesToSkip{ 0 };
	int count{ 0 };
	bool aux1{ false };

};

#endif 
