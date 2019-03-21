# ifndef DECODER_H_
# define DECODER_H_

# include "..\include\netxpto_20180815.h"

// Implements a IQ Decoder.
class Decoder : public Block {

public:

	//##############################################################################################################

	Decoder(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :Block(InputSig, OutputSig) {};


	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setM(int mValue);
	int getM() { return m; };

	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues);
	vector<t_iqValues> getIqAmplitudes() { return iqAmplitudes; }

	//##############################################################################################################

private:

	/* Input Parameters */

	t_integer m{ 4 };

	vector<t_complex> iqAmplitudes{ { 1,1 },{ -1,1 },{ 1,-1 },{ -1,-1 } };

	/* State Variables */

	bool firstTime{ true };

};

# endif
