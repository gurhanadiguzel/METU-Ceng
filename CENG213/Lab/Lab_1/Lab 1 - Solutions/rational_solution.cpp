#include <iostream>
#include "rational.hpp"

// Default (zero-argument) constructor
Rational::Rational()
{
    numer = denom = 0;
}

// Two argument constructor
Rational::Rational(int num, int den)
{
    /* TO-DO: fill the constructor */
    numer = num;
    denom = den;
}

void Rational::setNumerator(int num)
{
    numer = num;
}

int Rational::getNumerator()
{
    /* TO-DO */
    return numer;
}

void Rational::setDenominator(int den)
{
    /* TO-DO */
    denom = den;
}

int Rational::getDenominator()
{
    /* TO-DO */
    return denom;
}

void Rational::print()
{
    /* TO-DO */
    std::cout << numer << "/" << denom << std::endl;
}

// Returns a + b
Rational Rational::add(Rational rhs)
{
    /* TO-DO */
    Rational result;

    int num = numer * rhs.denom + rhs.numer * denom;
    int den = denom * rhs.denom;

    result.numer = num;
    result.denom = den;

    // Simplify the result if possible. Note that we
    // are not passing "result" as an argument to
    // "simplify". Instead we are calling the "simplify"
    // function of the "result" object.

    result.simplify();

    return result;
}

// Returns a * b
Rational Rational::multiply(Rational rhs)
{
    /* TO-DO: fill multiply */
    Rational result;

    int num = this->numer * rhs.numer;
    int den = this->denom * rhs.denom;

    result.numer = num;
    result.denom = den;

    result.simplify();

    return result;
}

void Rational::simplify()
{
    /* TO-DO: fill simplify */
    // Note that numer and denom are members
    // of "this" object. We can actually write
    // them as this->numer and this->denom.
    int factor = gcd(numer, denom);

    numer /= factor;
    denom /= factor;
}

int Rational::gcd(int a, int b)
{
    int c;

    if(a<0)
        a = a * -1;
    if(b<0)
        b = b * -1;

    while (a != 0)
    {
        c = a;
        a = b % a;
        b = c;
    }

    return b;
}
