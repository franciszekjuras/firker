#include <iostream>
#include <fstream>
#include "firker.h"

int main(){
	EqRippleFirKer ker;
	ker.setRank(1000);
	ker.setSampFreq(1000.);

	ker.setSpecs({100.,101.},{0.,0.,1.,1.},{1.,1.});
	ker.calc();
	std::cout << "L: " << ker.getKernel().size() << "\n";
	ker.setRank(999);
	ker.setSpecs({100.,101.},{0.,0.,1.,1.},{1.,1.});
	ker.calc();
	std::cout << "L: " << ker.getKernel().size() << "\n";
	ker.setSpecs({100.,101.,200.,201.},{0.,0.,1.,1.,0.,0.},{1.,1.,1.});
	ker.calc();
	std::cout << "L: " << ker.getKernel().size() << "\n";
	ker.setSpecs({100.,101.},{1.,1.,0.,0.},{1.,1.});
	ker.calc();
	std::cout << "L: " << ker.getKernel().size() << "\n";
	// std::fstream fs("ker.txt", std::fstream::out);
	// for(auto i : v){
	// 	fs << i << " ";
	// }
	// std::vector<double> t(FirKer::toBode(ker.transmission(1000)));
	// std::fstream fs2("trns.txt", std::fstream::out);
	// for(auto i : t){
	// 	fs2 << i << " ";
	// }
	// std::cout << "Sampling frequency: " << ker.getSampFreq() << " KHz" "\n" <<  "Done" << std::endl;

	return 0;
}
