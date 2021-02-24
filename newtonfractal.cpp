#include <stdio.h>
#include <iostream>
#include <string>

#include "newtonfractal.hpp"

NewtonFractal::NewtonFractal(struct NFParams &nfp) {
	_roots = std::vector<Complex>();
	_iterator = Newton(nfp.p);
	_origin = nfp.origin;
	_width = nfp.width;
	_height = nfp.height;
	_pixel_height = nfp.pixel_height;
	_pixel_width = nfp.pixel_width;
	_dzh = _height / (_pixel_width - 1);
	_dzw = _width / (_pixel_height - 1);
	_color_iterations = nfp.colour_iterations;
	_verbose = nfp.verbose;
	_num_colours = nfp.num_colours;
	_palette = nfp.palette;
}

void NewtonFractal::print_roots() {
	for (size_t i=0; i<_roots.size(); i++) {
		std::cout << _roots[i] << std::endl;
	}
}
	
int NewtonFractal::find_root(Complex root) {
	for (size_t i=0; i<_roots.size(); i++) {
		if ((root - _roots[i]).abs2() < Newton::TOL2) return i;
	}
	return -1;
}
	
Complex NewtonFractal::pixel_to_complex(int i, int j) {
	return Complex(_origin.get_real() + i*_dzw, _origin.get_imag() - j*_dzh);
}

Colour * NewtonFractal::create_fractal() {
	Colour *out_array = new Colour[_pixel_width * _pixel_height];
	
	for (size_t i=0; i<_pixel_height; i++) {
		for (size_t j=0; j<_pixel_width; j++) {
			_iterator.iterate(pixel_to_complex(j,i));
			size_t array_index = i*_pixel_width + j;
			Colour c;
			if (_iterator.get_error() == -2) {
				out_array[array_index] = Colour(255,255,255);
			} else {
				Complex root = _iterator.get_root();
				int root_index = find_root(root);
				if (root_index == -1) {
					_roots.push_back(root);
					root_index = _roots.size() - 1;
				}
				c = _palette[root_index % _num_colours];
				if (_color_iterations) {
					Colour c_scaled(c);
					for (size_t k=0; k<_iterator.get_num_iterations(); k++) {
						c_scaled = c_scaled.scale(0.98);
					}
					out_array[array_index] = c_scaled;
				} else {
					out_array[array_index] = c;
				}
			}
		}
		if (_verbose && i%100 == 0) std::cout << i << "/" << _pixel_height << std::endl;
	}
	if (_verbose) std::cout << _pixel_height << "/" << _pixel_height << std::endl;
	return out_array;
}