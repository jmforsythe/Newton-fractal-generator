#include "colour.h"
#include <iostream>

Colour::Colour() {
	_r = 0;
	_g = 0;
	_b = 0;
}

Colour::Colour(int r, int g, int b) {
	_r = r;
	_g = g;
	_b = b;
}

Colour Colour::scale(double intensity) {
	return Colour((int)(_r*intensity), (int)(_g*intensity), (int)(_b*intensity));
}