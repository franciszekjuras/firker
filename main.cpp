#include <iostream>
#include <fstream>
#include "firker.h"

int main(){
	EqRippleFirKer ker;
	ker.setRank(200);
	// ker.setSpecs(std::vector<double>{0.2,0.3}, std::vector<double>{1.,0.,1.});
	// ker.calc();

	std::cout << std::boolalpha << ker.setSpecs(std::vector<double>{.1, .2, .4}, std::vector<double>{0., 1., 0., 0.7}) << std::endl;
	ker.calc();
	std::vector<double> v(ker.getKernel());
	std::fstream fs("ker.txt", std::fstream::out);
	for(auto i : v){
		fs << i << " ";
	}
	std::cout << "Done" << std::endl;

	return 0;
}
