#include <stdio.h>
#include <iostream>
#include <string>

#include "newtonfractal.hpp"

NewtonFractal::NewtonFractal(Polynomial &p, Complex &origin, double width, double height) {
	_roots = std::vector<Complex>();
	_iterator = Newton(p);
	_origin = origin;
	_width = width;
	_height = height;
	_dzw = _width / (NUMPIXELSWIDTH - 1);
	_dzh = _height / (NUMPIXELSHEIGHT - 1);
}

void NewtonFractal::printRoots() {
	int i;
	for (i=0; i<_roots.size(); i++) {
		std::cout << _roots[i] << std::endl;
	}
}
	
int NewtonFractal::findRoot(Complex root) {
	int i;
	for (int i=0; i<_roots.size(); i++) {
		if ((root - _roots[i]).abs2() < Newton::TOL2) return i;
	}
	return -1;
}
	
Complex NewtonFractal::pixelToComplex(int i, int j) {
	return Complex(_origin.getReal() + i*_dzw, _origin.getImag() - j*_dzh);
}

Colour * NewtonFractal::createFractal(bool colorIterations) {
	const int numColours = 5;
	const Colour colour_array[5] = {Colour(255,0,0), Colour(0,255,0), Colour(0,0,255), Colour(0,255,255), Colour(255,0,255)};

	Colour *out_array = new Colour [NUMPIXELSWIDTH * NUMPIXELSHEIGHT];
	
	_colorIterations = colorIterations;
	
	int i, j;
	for (i=0; i<NUMPIXELSHEIGHT; i++) {
		for (j=0; j<NUMPIXELSWIDTH; j++) {
			_iterator.iterate(pixelToComplex(j,i));
			size_t array_index = i*NUMPIXELSWIDTH + j;
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
				c = colour_array[rootIndex % numColours];
				if (_colorIterations) {
					double intensity = 1.0f - (double)_iterator.getNumIterations()/(double)Newton::MAXITER;
					out_array[array_index] = c.scale(intensity);
				} else {
					out_array[array_index] = c;
				}
			}
		}
		if (i%100 == 0) std::cout << i << "/" << NUMPIXELSHEIGHT << std::endl;
	}
	return out_array;
}