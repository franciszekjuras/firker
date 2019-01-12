#include <iostream>
#include <fstream>
#include "firker.h"

int main(){
	EqRippleFirKer ker;
	ker.setRank(200);
	ker.setSampFreq(1000.);

	std::cout << std::boolalpha << ker.setSpecs(std::vector<double>{100., 200., 400.}, std::vector<double>{0., 1., 0., 0.7}) << std::endl;
	ker.calc();
	std::vector<double> v(ker.getKernel());
	std::fstream fs("ker.txt", std::fstream::out);
	for(auto i : v){
		fs << i << " ";
	}
	std::vector<double> t(FirKer::toBode(ker.transmission(100000)));
	std::fstream fs2("trns.txt", std::fstream::out);
	for(auto i : t){
		fs2 << i << " ";
	}
	std::cout << "Sampling frequency: " << ker.getSampFreq() << " KHz" "\n" <<  "Done" << std::endl;

	return 0;
}
