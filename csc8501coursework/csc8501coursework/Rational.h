#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include "Exception.h"

using posInt = unsigned long long;

class Rational {
	friend std::ostream& operator<<(std::ostream& os, const Rational& frac);
	friend Rational operator/(int i, const Rational& frac);
public:
	Rational(int n = 1, int d = 1)
		: numerator{ (n >= 0) ? posInt(n) : posInt(-n) }, denominator{ (d > 0) ? posInt(d) : posInt(-d) }, positive{ (n * d >= 0) ? true : false }
	{
		if (denominator == 0ull) throw DenominatorBeingZero{};
		fraction_reduction();
	}

	Rational operator*(const Rational& frac) {
		posInt n = numerator * frac.numerator;
		posInt d = denominator * frac.denominator;
		if (n == 0ull) return Rational{ 0ull,1ull,true };
		return ((positive == frac.positive) ? (Rational{ n,d,true }) : (Rational{ n,d,false }));
	}

	/*Rational operator*(int i) {
		
	}*/

	Rational operator+(const Rational& frac) {
		if (numerator == 0ull || frac.numerator == 0ull) return (numerator == 0ull) ? frac : *this;
		posInt lcm = LCM(denominator, frac.denominator);
		posInt n = 0ull;
		bool p = positive;
		if (positive != frac.positive) {
			n = (numerator * (lcm / denominator) > frac.numerator * (lcm / frac.denominator)) ? (numerator * (lcm / denominator) - frac.numerator * (lcm / frac.denominator)) : (frac.numerator * (lcm / frac.denominator) - numerator * (lcm / denominator));
			p = (numerator * (lcm / denominator) > frac.numerator * (lcm / frac.denominator)) ? positive : frac.positive;
		}
		else n = numerator * (lcm / denominator) + frac.numerator * (lcm / frac.denominator);
		return ((n == 0ull) ? (Rational{ 0,1,true }) : (Rational{ n,lcm,p }));
	}

	bool operator!=(int i) {
		Rational r{ ((i >= 0) ? posInt(i) : posInt(-i)), 1ull, ((i >= 0) ? true : false) };
		if (numerator == r.numerator && denominator == r.denominator && positive == r.positive) return false;
		return true;
	}

	bool operator!=(const Rational& r) {
		if (numerator == r.numerator && denominator == r.denominator && positive == r.positive) return false;
		return true;
	}

	bool operator==(int i) {
		if (*this != i) return false;
		return true;
	}

	bool operator<(int i) {
		Rational r{ ((i >= 0) ? posInt(i) : posInt(-i)), 1ull, ((i >= 0) ? true : false)};
		if (!positive && r.positive) return true;
		if (positive && !(r.positive)) return false;
		if (positive) {
			if (numerator < denominator * r.numerator) return true;
			return false;
		}
		if (numerator > denominator * r.numerator) return true;
		return false;
	}

	bool operator>(int i) {
		if (!(*this < i) && (*this != i)) return true;
		return false;
	}

	posInt get_numerator() { return numerator; }
	posInt get_denominator() { return denominator; }
	bool get_sign() { return positive; }

private:
	posInt numerator;
	posInt denominator;
	bool positive;  // including 0

	Rational(posInt n, posInt d, bool p)
		: numerator{ n }, denominator{ d }, positive{ p }
	{
		fraction_reduction();
	}

	void fraction_reduction() {
		if (numerator == 0ull) { denominator = 1ull; return; }
		posInt gcd = GCD(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
	}

	posInt GCD(posInt n, posInt d) {
		if (d == 0ull) return n;
		return GCD(d, n % d);
	}

	posInt LCM(posInt n, posInt d) {
		posInt lcm = 0ull;
		if (n >= d) lcm = n;
		else lcm = d;
		while (lcm % n != 0ull || lcm % d != 0ull) lcm++;
		return lcm;
	}
};

std::string toString(const Rational& frac);

#endif // !RATIONAL_H_INCLUDED

