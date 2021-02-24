#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include <cassert>
#include "Complex.hpp"

Complex::Complex(double x, double y) {
	_x = x;
	_y = y;
}
Complex::Complex(double x) {
	_x = x;
	_y = 0;
}
Complex::Complex() {
	_x = 0;
	_y = 0;
}

double Complex::get_real() const {
	return _x;
}
double Complex::get_imag() const {
	return _y;
}

std::string Complex::to_string() const {
	std::stringstream s;
	s << _x;
	if (_y >= 0) s << "+" << _y;
	else s << "-" << -_y;
	s << "i";
	return s.str();
}

double Complex::abs2() const {
	return (_x * _x) + (_y * _y);
}

Complex Complex::conjugate() const {
	return Complex(_x, -_y); 
}

Complex Complex::reciprocal() const {
	return conjugate()/abs2();
}

Complex operator+(const Complex &a, const Complex &b) {
	double ar,br,ai,bi;
	ar = a.get_real();
	br = b.get_real();
	ai = a.get_imag();
	bi = b.get_imag();
	return Complex(ar + br, ai + bi);
}

Complex operator-(const Complex &a, const Complex &b) {
	double ar,br,ai,bi;
	ar = a.get_real();
	br = b.get_real();
	ai = a.get_imag();
	bi = b.get_imag();
	return Complex(ar - br, ai - bi);
}

Complex operator*(const Complex &a, const Complex &b) {
	double ar,br,ai,bi;
	ar = a.get_real();
	br = b.get_real();
	ai = a.get_imag();
	bi = b.get_imag();
	return Complex((ar*br) - (ai*bi), (ai*br) + (ar*bi));
}

Complex operator*(const Complex &a, const double &b) {
	double ar,ai;
	ar = a.get_real();
	ai = a.get_imag();
	return Complex(ar*b, ai*b);
}

Complex operator*(const double &a, const Complex &b) {
	return b*a;
}

Complex operator/(const Complex &a, const Complex &b) {
	return a*b.reciprocal();
}

Complex operator/(const Complex &a, const double &b) {
	return a*(1.0/b);
}

Complex operator/(const double &a, const Complex &b) {
	return b.reciprocal()*a;
}

bool operator==(const Complex &a, const Complex &b) {
	return (a.get_real() == b.get_real() && a.get_imag() == b.get_imag());
}

std::ostream & operator<< (std::ostream & str, const Complex & z) {
	str << z.to_string();
	return str;
}