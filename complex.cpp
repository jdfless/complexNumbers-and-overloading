/*Jonathan Flessner		21-August-2013
**Description: A class for complex numbers including constructors, operators and member functions.
**Input: Can be given from user to define the complex number.  Can also be run without user input.
**Output: A test class showing functionality of all constructors, operators and member functions.
*/

#include <iostream>
#include <cstdlib> //for exit(1)
#include <cmath> //for pow, sqrt, atan2
//#include <complex> //for test comparisons
using namespace std;

class Complex
{
public:
	//constructors
	Complex (double r, double i);
	Complex (double realPart);
	Complex ();
	Complex (const Complex& copy); //copy constructor
	//overloaded operators
	friend istream& operator >>(istream& inS, Complex& comp);
	friend ostream& operator <<(ostream& outS, const Complex& comp);
	friend Complex operator +(const Complex& compA, const Complex& compB);
	friend Complex operator -(const Complex& compA, const Complex& compB);
	friend Complex operator *(const Complex& compA, const Complex& compB);
	friend Complex operator /(const Complex& compA, const Complex& compB);
	friend Complex operator -(const Complex& comp);
	//member functions
	friend double real(Complex& comp) { return comp.real; } //returns real part of complex (inline func)
	friend double imag(Complex& comp) { return comp.imaginary; } //returns imag part of complex (inline func)
	friend double abs(Complex& comp); //returns absolute value of complex
	friend double arg(Complex& comp); //returns phase angle of complex
	friend double norm(Complex& comp) { return pow((abs(comp)),2); } //returns norm of complex number (inline func)
	friend Complex conj(Complex& comp); //returns complex conjugate
	friend Complex polar(Complex& comp); //returns complex from polar components
	
private:
	double real;
	double imaginary;
};

int main() 
{
	Complex userComp;
	cout << "Please enter a complex number in the form <real>+<imaginary>i.\n";
	cin >> userComp; //lets user input the complex number to be tested
	
	//tests and displays results of the member functions
	double tR = real(userComp); //test with real function
	double tI = imag(userComp); //test with imag function
	cout << "Real part is " << tR << ". Imaginary part is " << tI << endl;
	double z = abs(userComp); //test with abs function
	cout << "The absolute value is " << z << endl;
	double pAngl = arg(userComp); //test with arg function
	cout << "The phase angle is " << pAngl << " radians\n";
	double nrm = norm(userComp); //test with norm function
	cout << "The norm value is " << nrm << endl;
	Complex cnj = conj(userComp); //test with conj function
	cout << "The conjugate is " << cnj << endl;
	Complex plr = polar(userComp); //test with polar function
	cout << "The complex whose magnitude is " << z << " and phase angle is " << pAngl << " is " << plr << endl;
	
	//this section tests the operator overloading of +,-(binary and unary), *, /, >>, and <<
	Complex comp1(3,5);
	Complex sum, prod, diff, quot, neg;
	sum = userComp + comp1;
	cout << userComp << " + " << comp1 << " = " << sum << endl; //shows + overload
	diff = userComp - comp1;
	cout << userComp << " - " << comp1 << " = " << diff << endl; //shows binary - overload
	prod = userComp * comp1;
	cout << userComp << " * " << comp1 << " = " << prod << endl; //shows * overload
	quot = userComp / comp1;
	cout << userComp << " / " << comp1 << " = " << quot << endl; //shows / overload
	neg = -userComp;
	cout << "Opposite of " << userComp << " is " << neg << endl; //shows unary - overload
	
	//tests one parameter, default and copy constructors
	Complex comp2(4), comp3, comp4(comp1); 
	cout << comp2 << endl;
	cout << comp3 << endl;
	cout << comp4 << endl; //should be equal to comp1
	
	

	return 0;
}

//two parameter constructor a + bi
Complex::Complex(double r, double i) : real(r), imaginary(i)
{ /* empty */ }
//one parameter constructor a+0i
Complex::Complex(double realPart) : real(realPart), imaginary(0)
{ /* empty */ }
//default constructor 0+0i
Complex::Complex() : real(0), imaginary(0)
{ /*empty */ }
//copy constructor (note: this should be identical to the compiler provided copy constructor)
Complex::Complex(const Complex& copy) : real(copy.real), imaginary(copy.imaginary)
{ /*empty */ } 

istream& operator >>(istream& inS, Complex& comp) //overload >>
{
	double real = 0;
	char p;
	double imag = 0;
	char i;
	
	//complex number in must be written a+bi with no spacing. if b is negative, the sign will go after the +.
	inS >> real;
	inS >> p;
	if (p != '+') //throws error if not proper formatting
	{
		cout << "ERROR. Complex numbers must be entered <real>+<imaginary>i. Ex. 2+3i\n"
			 << "Note there are no spaces between the numbers and the signs.\n"
			 << "Negative imaginary values need still be entered with the + sign. Ex. 2+-3i\n";
		exit(1);
	}
	inS >> imag;
	inS >> i;
	if (i != 'i') //throws error if not proper formatting
	{
		cout << "ERROR. Complex numbers must be entered <real>+<imaginary>i. Ex. 3+2i\n"
			 << "Note there are no spaces between the numbers and the signs.\n";
		exit(1);
	}
	
	comp.real = real;
	comp.imaginary = imag;
	
	return inS;
}

ostream& operator <<(ostream& outS, const Complex& comp) //overload <<
{
	double real = 0;
	double imag = 0;
	real = comp.real;
	imag = comp.imaginary;
	if (imag < 0)
		outS << real << "-" << -imag << "i"; //changes output from 3+-2i to 3-2i.
	else
		outS << real << "+" << imag << "i";
	return outS;
}

Complex operator +(const Complex& compA, const Complex& compB) //overload +
{
	Complex sum;
	sum.real = compA.real + compB.real;
	sum.imaginary = compA.imaginary + compB.imaginary;
	return sum;
}

Complex operator -(const Complex& compA, const Complex& compB) //overload binary -
{
	Complex diff;
	diff.real = compA.real - compB.real;
	diff.imaginary = compA.imaginary - compB.imaginary;
	return diff;
}

Complex operator *(const Complex& compA, const Complex& compB) //overload *
{
	Complex prod; //uses formula (a+bi)*(c+di) == (ac - bd)+(cd+bc)i
	prod.real = ((compA.real*compB.real) - (compA.imaginary*compB.imaginary));
	prod.imaginary = ((compA.real*compB.imaginary) + (compA.imaginary*compB.real));
	return prod;
}

Complex operator /(const Complex& compA, const Complex& compB) //overload /
{
	Complex quot; //uses formula a+bi/c+di == ((ac+bd)/(c^2+d^2)) + ((bc-ad)/(c^2+d^2))i
	quot.real = (((compA.real*compB.real) + (compA.imaginary*compB.imaginary)) / ((pow(compB.real,2)) + pow(compB.imaginary,2)));
	quot.imaginary = (((compA.imaginary*compB.real) - (compA.real*compB.imaginary)) / ((pow(compB.real,2)) + pow(compB.imaginary,2)));
	return quot;
}

Complex operator -(const Complex& comp) //overloads unary - operator.
{
	Complex neg;
	neg.real = -comp.real;
	neg.imaginary = -comp.imaginary;
	return neg;
}

double abs(Complex& comp) //finds absolute value (or modulus or magnitude) with formula z = sqrt(a^2 + b^2) for a+bi
{
	double z;
	double sum;
	sum = pow(comp.real, 2) + pow(comp.imaginary, 2);
	z = sqrt(sum);
	return z;
}

double arg(Complex& comp) //finds the phase angle using formula where arctan(b,a) = phase angle in radians for a+bi
{
	double pAngl = atan2(comp.imaginary, comp.real);
	return pAngl;
}

Complex conj(Complex& comp) //returns the conjugate of a complex number.  gives opposite of imaginary value.
{
	Complex conjugate;
	conjugate.real = comp.real;
	conjugate.imaginary = -comp.imaginary;
	return conjugate;
}

Complex polar(Complex& comp) //returns complex number from polar components rho (magnitude) and theta (phase angle)
							 //real = rho * cos(theta); imaginary = rho * sin(theta);
{
	Complex plr;
	plr.real = abs(comp) * cos(arg(comp));
	plr.imaginary = abs(comp) * sin(arg(comp));
	return plr;
}