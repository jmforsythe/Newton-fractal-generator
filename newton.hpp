#ifndef NEWTON_H
#define NEWTON_H

#include "polynomial.hpp"
#include "complex.hpp"

class Newton {
private:
	Polynomial _f;
	Polynomial _fp;
	Complex _root;
	int _num_iterations;
	int _err;

public:
	static const int MAXITER = 4000;
	static constexpr double TOL = 1.0e-10;
	static constexpr double TOL2 = TOL*TOL;
	
	Newton();
	Newton(Polynomial p);
	
	int get_error();
	size_t get_num_iterations();
	Complex get_root();
	Polynomial get_f();
	Polynomial get_fp();
	
	void iterate(Complex z0);
};

#endif
