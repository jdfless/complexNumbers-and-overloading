/*Jonathan Flessner		20-Aug-13
**Description: Savitch problem 8.7 pg 366.  Define class PrimeNumber. Set default prime number to 1 and then also add another constructor
**to allow the user to set the prime number.  Overload unary operators ++ and -- to have them find the next largest/smallest primes. 
**Include a test program to prove functionality.
**Input: User can input a prime number to start at.
**Output: The next largest and smallest prime numbers using overloaded unary operators ++ and --.
*/

#include <iostream>
#include <cmath> //for sqrt
using namespace std;

class PrimeNumber
{
public:
	PrimeNumber (int prime); //constructor for prime number
	PrimeNumber (); //default constructor
	int getNum (); //accessor to get value of num
	const PrimeNumber operator ++(int); //overload unary ++ postfix
	const PrimeNumber operator --(int); //overload unary -- postfix
	const PrimeNumber operator ++(); //overload unary ++ prefix
	const PrimeNumber operator --(); //overload unary -- prefix
	
private:
	int number;
	bool isPrime (int number); //checks if number is prime
};

PrimeNumber::PrimeNumber(int prime) : number(prime) { /*empty*/ } //constructor to let user define prime number

PrimeNumber::PrimeNumber() : number(2) { /*empty*/ } //define default constructor to 2 (lowest prime number)

int PrimeNumber::getNum() //accesses number
{
	return number;
}

bool PrimeNumber::isPrime (int number) //logic to find if it is prime
{
	if (number == 1){ //1 is not prime by definition
		return false; 
		}
	if (number > 2 && (number % 2 == 0)){ //nothing divided by 2 is prime except 2
		return false; 
		}
	for (int i = 2; i < number - 1; i++) { //handles rest of non prime cases
		if( number % i == 0 ) { //using modulo to check for remainder
		return false; //not prime
		}
	}	
	return true; //number is prime
}

const PrimeNumber PrimeNumber::operator ++(int postFix) //postfix
{
	int nextPrime = number;
	do
	{
		nextPrime++;
	} while (!isPrime(nextPrime));
	
	return PrimeNumber(nextPrime);
}

const PrimeNumber PrimeNumber::operator --(int postFix) //postfix
{
	int prevPrime = number;
	do
	{
		prevPrime--;
		if (prevPrime <= 2)
		{
			return PrimeNumber(2);
		}
	} while (!isPrime(prevPrime));
	
	return PrimeNumber(prevPrime);
}

const PrimeNumber PrimeNumber::operator ++() //prefix
{
	do
	{
		number++;
	} while (!isPrime(number));
	
	return PrimeNumber(number);
}

const PrimeNumber PrimeNumber::operator --() //prefix
{
	do
	{
		number--;
		if (number <= 2)
		{
			return PrimeNumber(2);
		}
	} while (!isPrime(number));
	
	return PrimeNumber(number);
}

int main() 
{
	cout << "Below are all prime numbers less than 1000.\n";	
	PrimeNumber prime; //default constructor sets to 2 (smallest prime number)
	int c = 0; //loop counter
	for (int i = 0; i < 168; i++) //prints all prime numbers under 1000 using overloaded ++
	{
		cout << prime.getNum() << " ";
		PrimeNumber temp = prime++;
		prime = temp;
		temp = 0; //resets temp variable
		c++; //increases loop counter
		if ((c % 14) == 0)
			cout << endl; //endl every 14 loop iterations
	}
	
	float input = 0;
	cout << "\nNow, please enter a number. I will show you the primes above and below it!\n";
	cin >> input;
	input = static_cast<int>(floor(input + .5)); //decimals are rounded and casted to an int. this fixed a looping issue with decimals less than 3
	if (input <= 2)
	{
		do
		{
			cout << "The number must be greater than 2, which is the smallest prime number.\n";
			cout << "Now, please enter a number. I will show you the primes above and below it!\n";
			cin >> input; 
		} while (input <= 2);
	}
	PrimeNumber userPrime(input); //sets user input to userPrime
	PrimeNumber larger = userPrime++;
	PrimeNumber smaller = userPrime--;
	cout << "The next largest prime is " << larger.getNum() << endl; //prints next largest prime
	cout << "The next smallest prime is " << smaller.getNum() << endl; //prints next smallest prime
	
	return 0;
}