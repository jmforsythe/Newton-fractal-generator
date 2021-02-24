#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include "complex.hpp"

class Polynomial {
private:
	std::vector<Complex> _coeff;
	size_t _degree;

public:
	Polynomial(std::vector<Complex> coeff);
	Polynomial();
	
	size_t get_degree();
	
	std::string to_string();
	
	Complex evaluate(Complex z);
	
	Polynomial derivative();
};

std::ostream & operator << (std::ostream & str, Polynomial & p);

#endif