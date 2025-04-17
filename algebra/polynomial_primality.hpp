/**
 * Implementation of the primality test for polynomials.
 * A polynomial is considered to be prime if it is irreducible in a given field.
 * Time complexity: O(poly(n))
 * Space complexity: O(n)
 * Created on 17.04.2025
 */

#include "finite_field.hpp"

#ifndef ALGORITHMS_POLYNOMIAL_PRIMALITY_HPP
#define ALGORITHMS_POLYNOMIAL_PRIMALITY_HPP

/**
 * Find a non-trivial (with degree >= 1) divisor of A over Zp
 * @param A     polynomial with coefficients in {0, ..., p-1}
 * @param p     prime for modular arithmetic
 * @return      non-trivial divisor of A or f(x)=0 if A is irreducible
 */
poly_zp is_prime (const poly_zp & A, int p) {
    poly_zp::p = p;
    poly_zp X({0, 1}), W({0, 1});
    int d = A.deg();
    for (int k = 1; k < d; k++) {
        W = pow(W, p, A);
        poly_zp div = gcd(A, W - X);
        if (div.deg() > 0) {
            return div;
        }
    }
    return poly_zp({0});
}

#endif //ALGORITHMS_POLYNOMIAL_PRIMALITY_HPP