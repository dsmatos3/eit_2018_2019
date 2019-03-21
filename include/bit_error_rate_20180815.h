# ifndef BIT_ERROR_RATE_H_
# define BIT_ERROR_RATE_H_

# include "..\include\netxpto_20180815.h"


class BitErrorRate : public Block {

public:

	//##############################################################################################################

	BitErrorRate(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :Block(InputSig, OutputSig) {};


	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

	void setConfidence(double P) { alpha = 1 - P; }
	double const getConfidence(void) { return 1 - alpha; }

	void setMidReportSize(int M) { m = M; }
	int const getMidReportSize(void) { return m; }

	void setLowestMinorant(double lMinorant) { lowestMinorant = lMinorant; }
	double getLowestMinorant(void) { return lowestMinorant; }

	//##############################################################################################################

private:

	bool firstTime{ true };
	double coincidences{ 0.0 };
	double receivedBits{ 0.0 };
	double lowestMinorant{ 1e-10 };
    
	int firstPass{ 1 };

	double alpha{ 0.05 };
	double z{ 0 };
	int m{ 0 };
	int n{ 0 };
};


#endif
