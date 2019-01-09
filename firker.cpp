#include <algorithm>
#include <utility>
#include <cmath>
#include "firker.h"

//---> Base Filter Kernel Class <---//
FirKer::FirKer(){

}


void FirKer::invalidate(){this->valid = false;}

void FirKer::validate(){this->valid = true;}

bool FirKer::isValid(){return this->valid;}

bool FirKer::setRank(int rank){
	if(rank < 0)
		return false;
	if(rank != this->rank){
		this->rank = rank;
		invalidate();
	}
	return true;
}

const std::vector<double>& FirKer::getKernel() const{
	return ker;
}

//---> Equiripple Filter Kernel <---//

EqRippleFirKer::EqRippleFirKer(){
	gains.push_back(1.);
}


bool EqRippleFirKer::setSpecs(const std::vector<double>& freqs, const std::vector<double>& gains){
	if((freqs.size()+1) != gains.size())
		return false;
	if( freqs[0]<=0. || !std::is_sorted(freqs.begin(),freqs.end()) || !std::all_of(gains.begin(),gains.end(),[](double x) {return x>=0.;}))
		return false;
	if(freqs != this->freqs || gains != this->gains){
		this->freqs = freqs; this->gains = gains;
		invalidate();
	}
	return true;
}

bool EqRippleFirKer::calc(){
	if(this->isValid())
		return true;
	//specification validation
	if(freqs.size()!=0 && freqs.back() >= .5)
		return false;
	//body

	ker.resize(rank);
	double accg = 0.; auto gcrr = gains.begin();
	std::vector<std::pair<double,double>> spc;

	for(auto f : freqs){
		accg = *gcrr - *(++gcrr);
		if(accg != 0.)
			spc.push_back(std::make_pair(f, accg));
	}

	double t;
	if(rank%2 == 0){
		t = 0.5;
		if(gains.back()!=0.)
			spc.push_back(std::make_pair(0.5,gains.back()));
	}
	else{
		t = 1.;
		double acc = 0; auto g = gains.begin();
		for(auto f : freqs)
			acc += 2.*f*(*g - *(++g));
		acc += *g;
		ker[rank/2] = acc;
	}

	for(int k = ((rank - 1)/2)+1; k < rank; ++k){
		double acc = 0;
		for(auto s : spc)
			acc += s.second*std::sin(2.*M_PI*s.first*t);
		acc /= M_PI * t;
		t += 1.;
		ker[k] = acc;
	}

	for(int k = 0, j = rank - 1; k < rank/2;){
		ker[k++] = ker[j--];
	}


	this->validate();
	return true;
}
