#ifndef NEWTON_H
#define NEWTON_H

#include "polynomial.h"
#include "complex.h"

class Newton {
private:
	Polynomial _f;
	Polynomial _fp;
	Complex _root;
	int _numIterations;
	int _err;

public:
	static const int MAXITER = 40;
	static constexpr double TOL = 1.0e-10;
	static constexpr double TOL2 = TOL*TOL;
	
	Newton();
	Newton(Polynomial p);
	
	int getError();
	int getNumIterations();
	Complex getRoot();
	Polynomial getF();
	Polynomial getFp();
	
	void iterate(Complex z0);
};

#endif