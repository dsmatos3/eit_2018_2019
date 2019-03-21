# ifndef ELECTRICAL_FILTER_H_
# define ELECTRICAL_FILTER_H_

# include "..\include\netxpto_20180815.h"

enum Filter { LowPass, Defined, Unitary};

class ElectricalFilter : public FIR_Filter {

public:

	//##############################################################################################################

	ElectricalFilter(initializer_list<Signal *> InputSig, initializer_list<Signal *> OutputSig) :FIR_Filter(InputSig, OutputSig) {};

	void initialize(void);
	
	//##############################################################################################################

	void lowPass(vector<t_real> &impulseResponse, int impulseResponseLength, double cutoffFrequency, double samplingPeriod, double symbolPeriod);

	void setImpulseResponseTimeLength(int impResponseTimeLength) { impulseResponseTimeLength = impResponseTimeLength; };
	int const getImpulseResponseTimeLength(void) { return impulseResponseTimeLength; };

	void setCutoffFrequency(double cOffFrequency) { cutoffFrequency = cOffFrequency; };
	double const getCutoffFrequency() { return cutoffFrequency; };

	void setFilterType(Filter fType) { filterType = fType; };
	Filter const getFilterType(void) { return filterType; };

	void setImpulseResponse(vector<t_real> ir) { impulseResponse = ir; };
	vector<t_real> getImpulseResponse(void) { return impulseResponse; };

private:

	Filter filterType{ LowPass };
	WindowType windowType{ Hann };
	int impulseResponseTimeLength{ 128 };

	double cutoffFrequency{ 5 }; //hertz
	vector<double> window;

};
#endif