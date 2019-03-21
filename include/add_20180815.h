# ifndef ADD_H_
# define ADD_H_

# include "..\include\netxpto_20180815.h"


class Add : public Block {

public:

	//##############################################################################################################

	Add(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	//##############################################################################################################

private:

	bool firstTime{ true };

};

#endif
