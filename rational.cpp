/*Jonathan Flessner		20-August-2013
**Description: Defines a rational numbers class. Represents the numerator and denominator as ints.
**Overloads input and output operators as well as ==,<=,<,>,>=,+,-,*,/.  
**Allows for negative numbers.  Normalizes numbers (ex. 4/-8 becomes -1/2).
**Input: Rational numbers from user for test program.
**Output: Answers to numbers given from user for test program.
*/

#include <iostream>
#include <cstdlib> //for exit(1)
#include <cmath> //for absolute value
using namespace std;

class Rational
{
public:
	Rational (int n, int d); //constructor for rational number (numerator/denominator)
	Rational (int wholeNumber); //constructor for wholeNumber/1
	Rational (); //default constructor
	
	friend istream& operator >>(istream& inS, Rational& fraction);
	friend ostream& operator <<(ostream& outS, const Rational& fraction);
	
	friend bool operator ==(const Rational& fractA, const Rational& fractB);
	friend bool operator <(const Rational& fractA, const Rational& fractB);
	friend bool operator <=(const Rational& fractA, const Rational& fractB);
	friend bool operator >=(const Rational& fractA, const Rational& fractB);
	friend bool operator >(const Rational& fractA, const Rational& fractB);
	
	friend Rational operator +(const Rational& fractA, const Rational& fractB);
	friend Rational operator -(const Rational& fractA, const Rational& fractB);
	friend Rational operator *(const Rational& fractA, const Rational& fractB);
	friend Rational operator /(const Rational& fractA, const Rational& fractB);
	
	friend Rational simplify(Rational& fraction); //simplifies and normalizes fractions
	
private:
	int numer; //numerator
	int denom; //denominator
};

int main() 
{
	//tests constructors for wholeNumber and default constructor
	Rational whole(5);
	Rational def;
	cout << "wholeNumber test: " << whole << " default test: " << def << endl;
	
	//tests overloaded >> and << and simplify
	Rational userFraction;
	cout << "Please enter a rational number in the form <numerator>/<denominator>\n";
	cin >> userFraction;
	userFraction = simplify(userFraction);
	cout << "Your simplified fraction is " << userFraction << endl;
	
	//constructs and simplifies frac1 and frac2
	Rational frac1(1,2);
	frac1 = simplify(frac1);
	Rational frac2(3,4);
	frac2 = simplify(frac2);
	
	//tests overloaded boolean operators with simplify
	if (frac1 == frac2)
		cout << frac1 << " is equal to " << frac2 << endl;
	else
		cout << frac1 << " is not equal to " << frac2 << endl;
		
	if (frac1 >= frac2)
		cout << frac1 << " is greater than or equal to " << frac2 << endl;
	else
		cout << frac1 << " is less than " << frac2 << endl;
		
	if (frac1 > frac2)
		cout << frac1 << " is greater than " << frac2 << endl;
	else
		cout << frac1 << " is less than or equal to " << frac2 << endl;
		
	if (frac1 < frac2)
		cout << frac1 << " is less than " << frac2 << endl;
	else
		cout << frac1 << " is greater than or equal to " << frac2 << endl;	
	
	if (frac1 <= frac2)
		cout << frac1 << " is less than or equal to " << frac2 << endl;
	else
		cout << frac1 << " is greater than " << frac2 << endl;
	
	//tests for overloaded +,-,*,/	
	Rational sum; 
	sum = frac1 + frac2;
	cout << frac1 << " + " << frac2 << " = " << sum << endl;
	
	Rational diff;
	diff = frac1 - frac2;
	cout << frac1 << " - " << frac2 << " = " << diff << endl;
	
	Rational prod;
	prod = frac1 * frac2;
	cout << frac1 << " * " << frac2 << " = " << prod << endl;
	
	Rational quot;
	quot = frac1 / frac2;
	cout << frac1 << " / " << frac2 << " = " << quot << endl;
	
	return 0;
}

Rational::Rational(int n, int d) //fraction constructor
{
	if (d == 0)
	{
		cout << "ERROR. Denominator cannot be 0.\n";
		exit (1);
	}
	numer = n;
	denom = d;
}

Rational::Rational(int wholeNumber) : numer(wholeNumber), denom(1) //construct to whole number with denominator = 1
{ /*empty*/ }

Rational::Rational() : numer(0), denom(1) //default construction to 0/1
{ /*empty*/ }

istream& operator >>(istream& inS, Rational& fraction) //overload >>
{
	int top = 0;
	char slash;
	int bottom = 0;
	
	inS >> top;
	inS >> slash;
	if (slash != '/')
	{
		cout << "ERROR. Numbers must be entered numerator/denominator. Ex. 1/2.\n"
			 << "Whole numbers must be entered <whole number>/1. Ex. 8/1 for 8.\n";
		exit(1);
	}
	inS >> bottom;
	if (bottom == 0)
	{
		cout << "ERROR. Denominator cannot be 0.\n";
		exit (1);
	}
	
	fraction.numer = top;
	fraction.denom = bottom;
	
	return inS;
}

ostream& operator <<(ostream& outS, const Rational& fraction) //overload <<
{
	int top = 0;
	int bottom = 0;
	top = fraction.numer;
	bottom = fraction.denom;
	outS << top << "/" << bottom;
	return outS;
}

//below are the overloaded boolean operators
bool operator ==(const Rational& fractA, const Rational& fractB)
{
	if ((fractA.numer * fractB.denom) == (fractB.numer * fractA.denom))
		return true;
	else
		return false;
}

bool operator <(const Rational& fractA, const Rational& fractB)
{
	if ((fractA.numer * fractB.denom) < (fractB.numer * fractA.denom))
		return true;
	else
		return false;
}

bool operator <=(const Rational& fractA, const Rational& fractB)
{
	if ((fractA.numer * fractB.denom) <= (fractB.numer * fractA.denom))
		return true;
	else
		return false;
}

bool operator >=(const Rational& fractA, const Rational& fractB)
{
	if ((fractA.numer * fractB.denom) >= (fractB.numer * fractA.denom))
		return true;
	else
		return false;
}

bool operator >(const Rational& fractA, const Rational& fractB)
{
	if ((fractA.numer * fractB.denom) > (fractB.numer * fractA.denom))
		return true;
	else
		return false;
}

//below are the overloaded +,-,*,/ operators
Rational operator +(const Rational& fractA, const Rational& fractB)
{
	Rational sum;
	int top1 = 0;
	int top2 = 0;
	int bottom1 = 0;
	int bottom2 = 0;
	if (fractA.denom == fractB.denom)
	{
		sum.numer = fractA.numer + fractB.numer;
		sum.denom = fractA.denom; //denominators are the same
	}
	else
	{
		bottom1 = fractA.denom;
		bottom2 = fractB.denom;
		top1 = bottom2 * fractA.numer;
		top2 = bottom1 * fractB.numer;
		bottom2 = bottom1 * fractB.denom;
		sum.numer = top1 + top2;
		sum.denom = bottom2; //denominators are the same
	}
	
	return simplify(sum); //simplifies the sum and returns the simplified value
}

Rational operator -(const Rational& fractA, const Rational& fractB)
{
	Rational difference;
	int top1 = 0;
	int top2 = 0;
	int bottom1 = 0;
	int bottom2 = 0;
	if (fractA.denom == fractB.denom)
	{
		difference.numer = fractA.numer - fractB.numer;
		difference.denom = fractA.denom; //denominators are the same
	}
	else
	{
		bottom1 = fractA.denom;
		bottom2 = fractB.denom;
		top1 = bottom2 * fractA.numer;
		top2 = bottom1 * fractB.numer;
		bottom2 = bottom1 * fractB.denom;
		difference.numer = top1 - top2;
		difference.denom = bottom2; //denominators are the same
	}
	
	return simplify(difference); //simplifies and returns
}

Rational operator *(const Rational& fractA, const Rational& fractB)
{
	Rational product;
	product.numer = fractA.numer * fractB.numer;
	product.denom = fractA.denom * fractB.denom;
	return simplify(product); //simplifies and returns
}


Rational operator /(const Rational& fractA, const Rational& fractB)
{
	Rational quotient;
	quotient.numer = fractA.numer * fractB.denom;
	quotient.denom = fractA.denom * fractB.numer;
	return simplify(quotient); //simplifies and returns
}

Rational simplify(Rational& fraction) //function to simplify and normalize
{
	Rational simple;

	int n = fraction.numer; //set n to numerator
	int d = fraction.denom; //set d to denominator
	int gcd = 0; //greatest common divisor
	int t = 0; //temp
	
	//simplify
	do { //euclids algorithim to find gcd
		t = d;
		d = n % t;
		n = t;
	} while (d != 0);
	gcd = n;
	
	simple.numer = fraction.numer / gcd; //simplify using gcd
	simple.denom = fraction.denom / gcd;
	
	n = simple.numer; //set n to new simplified numerator
	d = simple.denom; //set d to new simplified denominator
	
	//normalize
	if (d < 0 && (n < 0)) // if both numer and denom are negative, makes both positive. ex. -3/-4 = 3/4
	{
		simple.numer = abs (n);
		simple.denom = abs (d);
	}
	else if (d < 0) // moves negative from denom to numer. ex. 3/-4 = -3/4
	{
		simple.denom = abs (d);
		simple.numer = 0 - n;
	}
	return simple; //normalized and simplified. value returned.
}
