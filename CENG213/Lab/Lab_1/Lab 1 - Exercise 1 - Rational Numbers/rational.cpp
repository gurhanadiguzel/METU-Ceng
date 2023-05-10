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
    numer =num;
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
    std::cout<< numer << "/" << denom << std::endl;
}

// Returns a + b
Rational Rational::add(Rational rhs)
{
    Rational result;
    
    /* TO-DO: fill add */
    result.numer= numer*rhs.denom + denom*rhs.numer;
    result.denom= denom * rhs.denom;
    
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
    Rational result1;
    
    /* TO-DO: fill multiply */
    result1.numer = numer* rhs.numer;
    result1.denom = denom * rhs.denom;
    
    // Simplify the result if possible.
    
    result1.simplify();
    return result1;

}

void Rational::simplify()
{
    /* TO-DO: fill simplify */
    int c;
    c = gcd(numer,denom);
    numer /= c;
    denom /=c;
    
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
