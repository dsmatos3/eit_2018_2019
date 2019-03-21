# ifndef PULSE_SHAPER_H_
# define PULSE_SHAPER_H_

//# include <vector>
# include "../include/netxpto_20180815.h"


enum class pulse_shapper_filter_type { RaisedCosine, Gaussian, Square, RootRaisedCosine };

/* Raised-cosine filter FIR implementation. */
class PulseShaper : public FIR_Filter{

public:

	//#########################################################################################################################

	PulseShaper(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :FIR_Filter(InputSig, OutputSig) {};
	//PulseShaper(vector<Signal *> &InputSig, vector<Signal *> OutputSig) :FIR_Filter(InputSig, OutputSig){};
	//PulseShaper() :FIR_Filter() {};

	void initialize(void);

	//#########################################################################################################################

	void setImpulseResponseTimeLength_symbolPeriods(int impResponseTimeLength){ impulseResponseTimeLength = impResponseTimeLength; };
	int const getImpulseResponseTimeLength_symbolPeriods(void) { return impulseResponseTimeLength; };

	void setFilterType(pulse_shapper_filter_type fType){ filterType = fType; };
	pulse_shapper_filter_type const getFilterType(void){ return filterType; };

	void setRollOffFactor(double rOffFactor){ rollOffFactor = rOffFactor; };
	double const getRollOffFactor(){ return rollOffFactor; };

	void setPulseWidth(double pWidth) { pulseWidth = pWidth; };
	double const getPulseWidth() { return pulseWidth; };

	void setPassiveFilterMode(bool pFilterMode){ passiveFilterMode = pFilterMode; };
	bool const getPassiveFilterMode() { return passiveFilterMode; };

	void setRrcNormalizeEnergy(bool ne) { rrcNormalizeEnergy = ne; };
	bool getRrcNormalizeEnergy(void) { return rrcNormalizeEnergy; };

	//#########################################################################################################################

private:

	/* Input Parameters */
	pulse_shapper_filter_type filterType{ pulse_shapper_filter_type::RaisedCosine };

	int impulseResponseTimeLength{ 16 };				// in units of symbol period

	double pulseWidth{ 5e-10 };

	double rollOffFactor{ 0.9 };						// Roll-off factor (roll) for the raised-cosine filter

	bool passiveFilterMode{ false };

	bool rrcNormalizeEnergy{ false };                   // Set filter energy to 1, otherwise amplitude == 1

};

# endif


