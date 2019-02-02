#include <iostream>
#include <fstream>
#include "firker.h"

int main(){
	LeastSqFirKer ker;
	ker.setRank(50);
	ker.setSampFreq(1000.);

	std::cout << std::boolalpha << ker.setSpecs({100.},{0.,1.}) << std::endl;
	ker.setWindow(LeastSqFirKer::Window::blackman);
	ker.calc();
	std::vector<double> v(ker.getKernel());
	std::fstream fs("ker.txt", std::fstream::out);
	for(auto i : v){
		fs << i << " ";
	}
	std::vector<double> t(FirKer::toBode(ker.transmission(1000)));
	std::fstream fs2("trns.txt", std::fstream::out);
	for(auto i : t){
		fs2 << i << " ";
	}
	std::cout << "Sampling frequency: " << ker.getSampFreq() << " KHz" "\n" <<  "Done" << std::endl;

	return 0;
}
