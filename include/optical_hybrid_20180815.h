# ifndef OPTICAL_HYBRID_H_
# define OPTICAL_HYBRID_H_

# include "..\include\netxpto_20180815.h"


class OpticalHybrid : public Block {

public:

	//##############################################################################################################

	OpticalHybrid(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) : Block(InputSig, OutputSig) {};
	//OpticalHybrid(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};
	//OpticalHybrid() {};

	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setTransferMatrix(array<complex<double>, 8> TransferMatrix) { matrix = TransferMatrix; }
	array<complex<double>, 8> const getTransferMatrix(void) { return matrix; }

private:

	bool firstTime{ true };

	t_complex div = 1 / 2;
	t_complex unit = 1;
	complex<t_real> imaginary=sqrt(-1);
	array <complex<double>, 8> matrix = { { 1 / 2, 1 / 2, 1 / 2, -1 / 2, 1 / 2, sqrt(-1) / 2, 1 / 2, -sqrt(-1) / 2 } };

};

#endif 
