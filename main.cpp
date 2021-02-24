#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include "newtonfractal.hpp"

int main(int argc, char* argv[]) {
	
	// Default NewtonFractal params
	struct NFParams nfp;
	nfp.p = Polynomial({Complex(-1), Complex(), Complex(), Complex(1)});
	nfp.origin = Complex(-1.0, 1.0);
	nfp.pixel_height = 1024;
	nfp.pixel_width = 1024;
	nfp.width = 2.0;
	nfp.height = 2.0;
	nfp.num_colours = 5;
	nfp.palette = {Colour(255,0,0), Colour(0,255,0), Colour(0,0,255), Colour(0,255,255), Colour(255,0,255)};
	nfp.colour_iterations = true;
	nfp.max_iter_depth = 4000;
	nfp.verbose = false;
	
	// Add command line arguments parsing
	// -v: verbose, give progress updates and display polynomial
	// -c [coefficients]: coefficients in ascending order
	// -x[i] next argument is x^i coefficient, incompatible with -c
	// -pw [int]: nfp.pixel_width
	// -ph [int]: nfp.pixel_height
	// -o [a+bi]: nfp.origin
	// -cw [double]: nfp.width
	// -ch [double]: nfp.height
	// -p [filename]: path to file containing colour palette
	// --noshading: nfp.colour_iterations = false
	// --maxdepth [int]: max_iter_depth
	
	if (argc>1) {
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
		if (nfp.verbose) std::cout << p << std::endl;
		if (p.get_degree() == 0) {
			std::cout << "Cannot perform process on constant polynomial" << std::endl;
			return 0;
		}
		nfp.p = p;
	}
	
	NewtonFractal nf(nfp);
	Colour *fractal_colour_array = nf.create_fractal();
	
	std::string filename = nfp.p.to_string() + ".ppm";
	
	std::ofstream image_file(filename);
	
	image_file << "P3 " << nfp.pixel_width << " " << nfp.pixel_height << " " << 255 << std::endl;
	
	for (int i=0; i<nfp.pixel_height*nfp.pixel_width; i++) {
		auto c = fractal_colour_array[i];
		image_file << (int)c._r << " " << (int)c._g << " " << (int)c._b << " ";
		if (i%nfp.pixel_width == 0) {
			image_file << std::endl;
		}
	}
	return 0;
};