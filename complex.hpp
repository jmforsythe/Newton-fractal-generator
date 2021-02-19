#ifndef COMPLEX_H
#define COMPLEX_H
#include <string>

class Complex {
private:
	double _x, _y;
public:
	Complex(double x, double y);
	Complex(double x);
	Complex();
	
	double getReal() const;
	double getImag() const;
	
	std::string toString() const;
	
	double abs2() const;
	
	Complex conjugate() const;
	
	Complex reciprocal() const;
};

Complex operator+(const Complex &a, const Complex &b);

Complex operator-(const Complex &a, const Complex &b);

Complex operator*(const Complex &a, const Complex &b);
Complex operator*(const Complex &a, const double &b);
Complex operator*(const double &a, const Complex &b);

Complex operator/(const Complex &a, const Complex &b);
Complex operator/(const Complex &a, const double &b);
Complex operator/(const double &a, const Complex &b);

bool operator==(const Complex &a, const Complex &b);

std::ostream & operator<< (std::ostream & str, const Complex & z);

#endif