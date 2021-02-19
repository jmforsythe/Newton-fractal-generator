#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include "complex.hpp"

class Polynomial {
private:
	std::vector<Complex> _coeff;
	int _degree;

public:
	Polynomial(std::vector<Complex> coeff);
	Polynomial();
	
	int getDegree();
	
	std::string toString();
	
	Complex evaluate(Complex z);
	
	Polynomial derivative();
};

std::ostream & operator << (std::ostream & str, Polynomial & p);

#endif