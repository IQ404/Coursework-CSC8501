#ifndef BASICMATH_H_INCLUDED
#define BASICMATH_H_INCLUDED

inline int power(int x, int n) {  // n >= 0
	if (n) return x * power(x, n - 1);
	return 1;
}

#endif // !BASICMATH_H_INCLUDED

