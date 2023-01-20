
#include "Matrix.h"
#include "SimplePolynomial.h"
#include <iomanip>
#include "Rational.h"
#include "States.h"
#include "BasicMath.h"


int main() {
	std::cin.exceptions(std::cin.exceptions() | std::ios_base::badbit);
	std::cout.exceptions(std::cout.exceptions() | std::ios_base::badbit);
	try {
		States program;
		program.run();
	}
	catch (const std::ios::failure&) {
		std::cout << "\n\nSERIOUS ERROR OCCURRED: IO stream went bad. Program terminating... Please restart the program.\n";
	}
}