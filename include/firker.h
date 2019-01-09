#ifndef _FIRKER_H_
#define _FIRKER_H_
#include <vector>

class FirKer
{
public:
	FirKer();

	virtual bool calc() = 0;
	bool isValid();

	//bool setFrequency();
	bool setRank(int rank);
	const std::vector<double>& getKernel() const;
	
protected:
	bool valid;
	int rank;
	std::vector<double> ker;
	void invalidate();
	void validate();

};


class EqRippleFirKer : public FirKer
{
public:
	EqRippleFirKer();
	bool setSpecs(const std::vector<double>& freqs, const std::vector<double>& gains);
	bool calc();

protected:
	std::vector<double> freqs;
	std::vector<double> gains;

};



#endif //_FIRKER_H_