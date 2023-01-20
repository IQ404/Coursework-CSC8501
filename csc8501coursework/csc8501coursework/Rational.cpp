#include "Rational.h"

std::ostream& operator<<(std::ostream& os, const Rational& frac) {
	if (frac.numerator == 0) os << "0";
	else {
		os << ((frac.positive) ? "" : "-");
		if (frac.denominator == 1) os << frac.numerator;
		else os << frac.numerator << '/' << frac.denominator;
	}
	return os;
}

std::string toString(const Rational& frac) {
	std::ostringstream buffer;
	buffer << frac;
	return buffer.str();
}

Rational operator/(int i, const Rational& frac) {
	if (i == 0) return Rational{ 0 };
	if (i > 0) return Rational{ posInt(i) * frac.denominator, frac.numerator, frac.positive };
	return Rational{ posInt(-i) * frac.denominator, frac.numerator, !(frac.positive) };
}

