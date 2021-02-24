#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include "newtonfractal.hpp"

std::vector<std::string> flags = {"-c", "-v", "-pw", "-ph", "-o", "-cw", "-ch", "-p", "--noshading", "--maxdepth"};

int get_next_flag(int arg_pos, int argc, char* argv[]) {
	for (int i=arg_pos+1; i<argc; i++) {
		// if argv[i] in flags
		if (std::find(flags.begin(), flags.end(), argv[i]) != flags.end()) return i;
	}
	return argc;
}

Complex char_arr_to_complex(char * char_arr) {
	std::regex expression("(.*)([+-].*)i");
	std::smatch match;
	std::string str(char_arr);
	std::regex_match(str, match, expression);
	switch (match.size()) {
		case 2:
			return Complex(std::stod(match[1]));
		case 3:
			return Complex(std::stod(match.str(1)), std::stod(match.str(2)));
		default:
			return Complex();
	}
}

Polynomial parse_coeff(int arg_pos, int last_pos, char* argv[]) {
	std::vector<Complex> coeff;
		std::regex expression("(.*)([+-].*)i");
		for (int i=arg_pos; i<last_pos; i++) {
			coeff.push_back(char_arr_to_complex(argv[i]));
		}
	Polynomial p(coeff);
	return Polynomial(coeff);
}

void parse_arg(int arg_pos, int argc, char* argv[], struct NFParams &nfp) {
	// -v: verbose, give progress updates and display polynomial
	// -c [coefficients]: coefficients in ascending order
	// -pw [int]: nfp.pixel_width
	// -ph [int]: nfp.pixel_height
	// -o [a+bi]: nfp.origin
	// -cw [double]: nfp.width
	// -ch [double]: nfp.height
	// -p [filename]: path to file containing colour palette
	// --noshading: nfp.colour_iterations = false
	// --maxdepth [int]: max_iter_depth
	
	std::string arg = argv[arg_pos];
	if (arg == "-v") nfp.verbose=true;
	else if (arg == "-c") nfp.p = parse_coeff(arg_pos+1, get_next_flag(arg_pos, argc, argv), argv);
	else if (arg == "-pw") nfp.pixel_width = std::stoi(argv[arg_pos+1]);
	else if (arg == "-ph") nfp.pixel_height = std::stoi(argv[arg_pos+1]);
	else if (arg == "-o") nfp.origin = char_arr_to_complex(argv[arg_pos+1]);
	else if (arg == "-cw") nfp.width = std::stoi(argv[arg_pos+1]);
	else if (arg == "-ch") nfp.height = std::stoi(argv[arg_pos+1]);
	//else if (arg == "-p") TODO, user defined palette
	else if (arg == "--noshading") nfp.colour_iterations = false;
	else if (arg == "--maxdepth") nfp.max_iter_depth = std::stoi(argv[arg_pos+1]);
}

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

	
	for (int i=1; i<argc; i++) {
		parse_arg(i, argc, argv, nfp);
	}
	
	
	
	
	if (nfp.p.get_degree() == 0) {
		std::cout << "Cannot perform process on constant polynomial" << std::endl;
		return 0;
	}
	
	if (nfp.verbose) std::cout << nfp.p << std::endl;
	
	NewtonFractal nf(nfp);
	Colour *fractal_colour_array = nf.create_fractal();
	
	std::string filename = nfp.p.to_string() + ".ppm";
	
	std::ofstream image_file(filename);
	
	// P3 = ascii, P6 = binary
	/*
	image_file << "P3 " << nfp.pixel_width << " " << nfp.pixel_height << " " << 255 << std::endl;
	
	for (int i=0; i<nfp.pixel_height*nfp.pixel_width; i++) {
		auto c = fractal_colour_array[i];
		image_file << (int)c._r << " " << (int)c._g << " " << (int)c._b << " ";
		if ((i+1)%nfp.pixel_width == 0) {
			image_file << std::endl;
		}
	}
	*/
	
	image_file << "P6 " << nfp.pixel_width << " " << nfp.pixel_height << " " << 255 << std::endl;
	
	for (int i=0; i<nfp.pixel_height*nfp.pixel_width; i++) {
		auto c = fractal_colour_array[i];
		image_file << (char)c._r << (char)c._g << (char)c._b;
		if ((i+1)%nfp.pixel_width == 0) {
			image_file << std::endl;
		}
	}
	
	return 0;
};