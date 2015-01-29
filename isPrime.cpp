//program written by OSU prof Joseph Jess. Debugged, edited and enhanced for practice by Jonathan Flessner

#include <iostream>
#include <cmath> //for sqrt
#define PROMPT "Please enter a whole number: "
#define NOT_PRIME "The number is not a prime number. "
#define PRIME "The number is a prime number. "
using std::cout;
using std::cin;
int main(){
	int i = 2; /* loop counter */
	int number = 0; /* number provided by user */
	cout << PROMPT; /* prompt user */
	cin >> number; /* wait for user input */
	
	if (number == 1){ //1 is not prime by definition
		cout << NOT_PRIME;
		return 0; //exit if not prime
		}
	if (number > 2 && (number % 2 == 0)){ //nothing divided by 2 is prime except 2
		cout << NOT_PRIME;
		return 0; //exit if not prime
		}

	for( i; i < sqrt(number); i++) { //handles rest of non prime cases
		if( number % i == 0 ) { ///using modulo to check for remainder
		cout << NOT_PRIME << number; /* not prime */
		return 0; /* exit program */
		}
	}
		
	cout << PRIME << number; //if passes all the checks then it is prime
	return 0; /* exit program */
}