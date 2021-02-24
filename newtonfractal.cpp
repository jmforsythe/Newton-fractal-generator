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
	_colorIterations = nfp.colour_iterations;
	_verbose = nfp.verbose;
	_num_colours = nfp.num_colours;
	_palette = nfp.palette;
}

void NewtonFractal::printRoots() {
	for (size_t i=0; i<_roots.size(); i++) {
		std::cout << _roots[i] << std::endl;
	}
}
	
int NewtonFractal::findRoot(Complex root) {
	for (size_t i=0; i<_roots.size(); i++) {
		if ((root - _roots[i]).abs2() < Newton::TOL2) return i;
	}
	return -1;
}
	
Complex NewtonFractal::pixelToComplex(int i, int j) {
	return Complex(_origin.getReal() + i*_dzw, _origin.getImag() - j*_dzh);
}

Colour * NewtonFractal::createFractal() {
	Colour *out_array = new Colour [_pixel_width * _pixel_height];
	
	int i, j;
	for (i=0; i<_pixel_height; i++) {
		for (j=0; j<_pixel_width; j++) {
			_iterator.iterate(pixelToComplex(j,i));
			size_t array_index = i*_pixel_width + j;
			Colour c;
			if (_iterator.getError() == -2) {
				out_array[array_index] = Colour(255,255,255);
			} else {
				Complex root = _iterator.getRoot();
				int rootIndex = findRoot(root);
				if (rootIndex == -1) {
					_roots.push_back(root);
					rootIndex = _roots.size() - 1;
				}
				c = _palette[rootIndex % _num_colours];
				if (_colorIterations) {
					Colour c_scaled(c);
					for (int k=0; k<_iterator.getNumIterations(); k++) {
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