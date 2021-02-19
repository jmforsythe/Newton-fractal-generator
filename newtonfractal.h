#ifndef NEWTONFRACTAL_H
#define NEWTONFRACTAL_H

#include <iostream>
#include <vector>

#include "newton.h"
#include "polynomial.h"
#include "complex.h"

#include "colour.h"

class NewtonFractal {
private:
	Complex _origin;
	double _width, _height, _dzw, _dzh;
	
	Newton _iterator;
	std::vector<Complex> _roots;
		
	bool _colorIterations;
	
public:
	static const int NUMPIXELSWIDTH = 512;
	static const int NUMPIXELSHEIGHT = 512;
	
	NewtonFractal(Polynomial &p, Complex &origin, double width, double height);
	
	void printRoots();
	
	int findRoot(Complex root);
	
	Complex pixelToComplex(int i, int j);
	
	Colour * createFractal(bool colorIterations);
};

#endif