# ifndef PROGRAM_INCLUDE_COMPLEX2REAL_H_
# define PROGRAM_INCLUDE_COMPLEX2REAL_H_

# include "netxpto_20190215.h"


// Creates a complex signal from two real signals
class Complex2Real : public Block {

	/* State Variables */
	bool firstTime{ true };

public:

	/* Methods */
	Complex2Real() {};
	Complex2Real(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :
		Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

};

# endif
