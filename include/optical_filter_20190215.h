# ifndef PROGRAM_INCLUDE_OPTFILT_H_
# define PROGRAM_INCLUDE_OPTFILT_H_

# include "netxpto_20190215.h"
# include "complex2real_20190215.h"
# include "electrical_filter_20190215.h" 
# include "real_to_complex_20180221.h"

// #########################################################################################################
// This block currently implements an optical filter. Currently, it is only possible to have the filter
// centered on the carrier frequency of the signal. Right now this is assumed automatically by default.
// #########################################################################################################


// Trans-Impedance Amplifier superblock
class OpticalFilter : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################
	TimeContinuousAmplitudeContinuousReal OPT_FILT01{ "OPT_FILT01.sgn" }; // Real Input
	TimeContinuousAmplitudeContinuousReal OPT_FILT02{ "OPT_FILT02.sgn" }; // Imag Input
	TimeContinuousAmplitudeContinuousReal OPT_FILT03{ "OPT_FILT03.sgn" }; // Real Filtered Output
	TimeContinuousAmplitudeContinuousReal OPT_FILT04{ "OPT_FILT04.sgn" }; // Imag Filtered Output

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	Complex2Real B1;
	ElectricalFilter B2;
	ElectricalFilter B3;
	RealToComplex2 B4;

	/* State Variables */

	/* Input Parameters */

	bool firsTime{ true };

public:

	/* Methods */

	OpticalFilter() {};
	OpticalFilter(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	void setDirName(string newDirName);
	string getDirName(void) { return dirName; };

	void setBandwidth(t_real bw) { bandwidth = bw; B2.setCutoffFrequency(bw / 2); B3.setCutoffFrequency(bw / 2);};
	t_real getBandwidth(void) { return bandwidth; };

	void setFilterType(Filter ft) { filterType = ft; };
	Filter getFilterType(void) { return filterType; }

	void setImpulseResponseTimeLength(int irtl) {
		impulseResponseTimeLength = irtl;
		B2.setImpulseResponseTimeLength(impulseResponseTimeLength);
		B3.setImpulseResponseTimeLength(impulseResponseTimeLength);
	}

	int getImpulseResponseTimeLength(void) { return impulseResponseTimeLength; };
	/* Set Methods */

	// Signal gain is assumed to be equal to internal noise gain.

private:
	string dirName{ "" };
	t_real bandwidth{ 100e9 };
	Filter filterType{ LowPass };
	int impulseResponseTimeLength{ 16 };
};


#endif
