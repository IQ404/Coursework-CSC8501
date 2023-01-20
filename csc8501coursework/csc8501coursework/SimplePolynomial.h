
#ifndef SIMPLEPOLYNOMIAL_H_INCLUDED
#define SIMPLEPOLYNOMIAL_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "Rational.h"


class SimplePolynomial {
public:
	SimplePolynomial(){}
	SimplePolynomial(const std::vector<Rational>& v)
		: coefficients{ v }
	{  }

	void print_polynomial(std::ostream& os) {
		os << "P(x) = ";
		for (int i = 4; i >= 0; i--) {
			if (head) print_head_term(os, i);
			else print_body_term(os, i);
		}
		head = true;
		os << std::endl;
	}

	void print_function_value(Rational x) {  // To std::cout
		std::cout << "P(" << x << ") = " << function_value(x) << std::endl;
	}

	Rational function_value(Rational x) {
		Rational y{ 0 };
		for (int p = 4; p >= 0; p--) {
			y = y + term_value(p, x);
		}
		return y;
	}

private:
	std::vector<Rational> coefficients;
	bool head = true;

	void print_head_term(std::ostream& os, int i) {
		if (coefficients[4 - i] == 0) {
			if (i == 0) os << "0";
			return;
		}
		if (coefficients[4 - i] > 0) os << ((coefficients[4 - i] == 1) ? "" : toString(coefficients[4 - i]));
		else os << ((coefficients[4 - i] == -1) ? "-" : toString(coefficients[4 - i]));
		os << ((i == 0) ? ((coefficients[4 - i] == 1 || coefficients[4 - i] == -1) ? "1" : "") : ((i == 1) ? "x " : ("x^" + std::to_string(i) + " ")));
		head = false;
	}

	void print_body_term(std::ostream& os, int i) {
		if (coefficients[4 - i] == 0) return;
		if (coefficients[4 - i] > 0) os << "+ " << ((coefficients[4 - i] == 1) ? "" : toString(coefficients[4 - i]));
		else os << "- " << ((coefficients[4 - i] == -1) ? "" : (toString(coefficients[4 - i] * (-1))));
		os << ((i == 0) ? ((coefficients[4 - i] == 1 || coefficients[4 - i] == -1) ? "1" : "") : ((i == 1) ? "x " : ("x^" + std::to_string(i) + " ")));
	}

	Rational term_value(int p, Rational x) {
		Rational val = coefficients[4 - p];
		for (int i = 0; i < p; i++) {
			val = val * x;
		}
		return val;
	}
};

class SimplePolynomialSet {
public:
	void add(const SimplePolynomial& sp) {
		v.push_back(sp);
	}

	SimplePolynomial get(int index) {
		return v[index - 1];
	}

	int get_size() {
		return v.size();
	}

	void print_SimplePolynomials() {  // To std::cout
		if (v.size()) {
			for (int p = 0; p < v.size(); p++) {
				std::cout << "\t" << p + 1 << ". ";
				v[p].print_polynomial(std::cout);
			}
		}
		else std::cout << "\tNo polynomial stored.\n";
	}

private:
	std::vector<SimplePolynomial> v;
};

#endif // !SIMPLEPOLYNOMIAL_H_INCLUDED
