#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "newtonfractal.h"

int main(int argc, char* argv[]) {
	std::vector<Complex> coeff;
	std::regex expression("(.*)([+-].*)i");
	for (int i=1; i<argc; i++) {
		std::smatch match;
		std::string str(argv[i]);
		std::regex_match(str, match, expression);
		switch (match.size()) {
			case 2:
				coeff.push_back(Complex(std::stod(match[1]))); break;
			case 3:
				coeff.push_back(Complex(std::stod(match.str(1)), std::stod(match.str(2)))); break;
			default:
				coeff.push_back(Complex()); break;
		}
	}
	Polynomial p(coeff);
	std::cout << p << std::endl;
	if (p.getDegree() == 0) {
		std::cout << "Cannot perform process on constant polynomial" << std::endl;
		return 0;
	}
	Complex origin(-1.0, 1.0);
	double width = 2.0;
	double height = 2.0;
	
	NewtonFractal nf(p, origin, width, height);
	Colour *fractal_colour_array = nf.createFractal(true);
	
	std::string filename = p.toString() + ".ppm";
	
	std::ofstream ImageFile(filename);
	
	ImageFile << "P3 " << NewtonFractal::NUMPIXELSWIDTH << " " << NewtonFractal::NUMPIXELSHEIGHT << " " << 255 << std::endl;
	
	for (int i=0; i<NewtonFractal::NUMPIXELSHEIGHT*NewtonFractal::NUMPIXELSWIDTH; i++) {
		auto c = fractal_colour_array[i];
		ImageFile << (int)c._r << " " << (int)c._g << " " << (int)c._b << " ";
		if (i%NewtonFractal::NUMPIXELSWIDTH == 0) {
			ImageFile << std::endl;
		}
	}
	return 0;
};