#include "netxpto_20180418.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <bitset>

#include "binary_source_20180523.h"
#include "sink_20180118.h"
#include "arithmetic_encoder.h"
#include "arithmetic_decoder.h"
#include "fork_20180112.h"
#include "bit_error_rate_20180424.h"

int main()
{
	// #####################################################################################################
	// ################################# System Input Parameters ###########################################
	// #####################################################################################################

	const unsigned long		RNG_SEQ_LEN = 3*5*6*7*8*9;	// 2*3*4*6*8*10;
	const unsigned int		BITS_PER_SYMB = 5;
	const unsigned long		SRC_NUM_SYMBS = 1 << BITS_PER_SYMB;
	const unsigned int		INPUT_ORIGIN = 0;  // 0: "File" or 1: "Random"
	const double			PROB_OF_ZERO = 0.1;

	// #####################################################################################################
	// ################################# Simulation Parameters #############################################
	// #####################################################################################################

	string bit_seq = ""; 
	std::ifstream t("InputTextFile.txt");
	std::string str;
	bitset<8> bits;

	// Generate the binary source data
	switch (INPUT_ORIGIN) {

	case 0:							// From File
		t.seekg(0, std::ios::end);
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);
		str.assign((std::istreambuf_iterator<char>(t)),
					std::istreambuf_iterator<char>());

		for (unsigned int i = 0; i < str.length(); i++)
		{
			bits = bitset<8>(str[i]);
			bit_seq += bits.to_string();
		}
		break;

	case 1:							// From pseudo random generator
		std::random_device rd;
		std::mt19937 gen{ rd() };
		std::bernoulli_distribution dis{ PROB_OF_ZERO };

		for (int i = 0; i < RNG_SEQ_LEN; ++i)
			bit_seq.push_back(dis(gen) + '0');
		break;
	}

	// Compute the cumulative symbol counts

	vector<unsigned int> symb_counts(SRC_NUM_SYMBS, 1);
	unsigned int symb = 0;
	unsigned int nbits = 0;
	for (unsigned int i = 0; i < bit_seq.length(); i++) {
		symb = (symb << 1) + (bit_seq.at(i) - '0');
		nbits++;
		if (nbits == BITS_PER_SYMB) {
			symb_counts[symb] = symb_counts[symb]++;
			nbits = 0;
			symb = 0;
		}
	}

	const string				BIT_SEQ		= bit_seq;
	const unsigned int			BIT_SEQ_LEN = bit_seq.length();
	const double	            SYMB_SEQ_LEN = (unsigned int) BIT_SEQ_LEN / BITS_PER_SYMB;
	const vector<unsigned int>	SYMB_COUNTS	= symb_counts;

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S1{ "S1.sgn" };
	Binary S1_1{ "S1_1.sgn" };
	Binary S1_2{ "S1_2.sgn" };
	//S1.setSaveSignal(false);

	Binary S2{ "S2.sgn" };
	Binary S2_1{ "S2_1.sgn" };
	Binary S2_2{ "S2_2.sgn" };
	//S2.setSaveSignal(false);

	Binary S3{ "S3.sgn" };
	//S2.setSaveSignal(false);

	Binary S4{ "S4.sgn" };

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	BinarySource B0_binsrc{ vector <Signal*>{}, vector <Signal*> {&S1} };
	B0_binsrc.setBitPeriod(1);
	B0_binsrc.setNumberOfBits(BIT_SEQ_LEN);
	//B0_binsrc.setProbabilityOfZero(0.1);
	B0_binsrc.setMode(DeterministicCyclic);
	B0_binsrc.setBitStream(BIT_SEQ);

	Fork B1_fork{ vector <Signal*> {&S1}, vector <Signal*> {&S1_1, &S1_2} };

	ArithmeticEncoder B2_arithenc{ vector <Signal*> {&S1_1}, vector <Signal*> {&S2} };
	B2_arithenc.init(SYMB_SEQ_LEN, BITS_PER_SYMB, SYMB_COUNTS);

	Fork B3_fork{ vector <Signal*> {&S2}, vector <Signal*> {&S2_1, &S2_2} };

	ArithmeticDecoder B4_arithdec{ vector <Signal*> {&S2_1}, vector <Signal*> {&S3} };
	B4_arithdec.init(SYMB_SEQ_LEN, BITS_PER_SYMB, SYMB_COUNTS);

	Sink B5_sink(vector <Signal*> {&S2_2}, vector <Signal*> {});
	B5_sink.setDisplayNumberOfSamples(false);

	BitErrorRate B6_ber{ vector <Signal*> {&S1_2, &S3}, vector <Signal*> {&S4} };

	Sink B7_sink(vector <Signal*> {&S4}, vector <Signal*> {});
	B7_sink.setDisplayNumberOfSamples(true);

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector <Block*> {&B0_binsrc, &B1_fork, &B2_arithenc, &B3_fork, &B4_arithdec, &B5_sink,
										&B6_ber, &B7_sink} };

	// #####################################################################################################
	// ############################################ Run ####################################################
	// #####################################################################################################

	MainSystem.run();

	unsigned int NumBitsEnc = abs(B5_sink.numberOfSamples);
	long double Lenc, CodeEff;
    long double Hsrc = PROB_OF_ZERO * log2(1 / PROB_OF_ZERO) + (1 - PROB_OF_ZERO) * log2(1 / (1 - PROB_OF_ZERO));
	
	Hsrc = 0;
	for (int i = 0; i < SYMB_COUNTS.size(); i++)
		if (SYMB_COUNTS.at(i) > 1)
			Hsrc += (SYMB_COUNTS.at(i)-1)/(SYMB_SEQ_LEN) * log2(1 / ((SYMB_COUNTS.at(i)-1) / SYMB_SEQ_LEN));

	Lenc = NumBitsEnc / SYMB_SEQ_LEN;
	CodeEff = Hsrc / Lenc;

	return 0;
}