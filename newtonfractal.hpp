#ifndef NEWTONFRACTAL_H
#define NEWTONFRACTAL_H

#include <iostream>
#include <vector>

#include "newton.hpp"
#include "polynomial.hpp"
#include "complex.hpp"

#include "colour.hpp"

struct NFParams {
	Polynomial p;
	Complex origin; // top left of image
	int pixel_height, pixel_width;
	double width, height;
	bool colour_iterations;
	int max_iter_depth;
	bool verbose;
	size_t num_colours;
	std::vector<Colour> palette;
};


class NewtonFractal {
private:
	Complex _origin;
	double _width, _height, _dzw, _dzh;
	
	Newton _iterator;
	std::vector<Complex> _roots;
		
	bool _color_iterations, _verbose;
	
	size_t _pixel_width, _pixel_height;
	
	std::vector<Colour> _palette;
	size_t _num_colours;
	
public:	
	NewtonFractal(NFParams &nfp);
	
	void print_roots();
	
	int find_root(Complex root);
	
	Complex pixel_to_complex(int i, int j);
	
	Colour * create_fractal();
};

#endif