#include <iostream>
#include "TimeInterval.h"

using namespace std;

/**
 * \brief Divides one time interval by another
 *
 * Given two TimeInterval objects -- a numerator and a denominator -- computes 
 * the quotient (as a long integer) and the remainder (as another TimeInterval)
 * when numerator is divided by denominator.
 *
 */
void divide(const TimeInterval &numerator,
            const TimeInterval &denominator,
            long &quotient,
            TimeInterval &remainder)
{
        long index = 0;

        TimeInterval zero;
        TimeInterval numerator_temp = numerator;

	quotient = 0;

        //
	// Can't divide by zero
	//
        if (denominator == zero) {
            quotient = -1;
            cout << "Can't divide by zero." << endl;
            return ;
        }
	//
	//  Quick check to return an answer of 0
        //
        if (numerator == zero) {
	    quotient = 0;
            remainder = zero;
            return ; 
        }
	//
	//  Quick check to return an answer of 1
        //
        if (numerator==denominator) {
	    quotient = 1;
            remainder = zero;
            return ;
        }
	//
	// Check to make sure the answer is going to be an integer.
        //
        if (numerator<denominator) {
            quotient = -1;
            remainder = zero;
            cout << "Quotient is not an integer." << endl;
            return ;
        }
                           
	// A faster simple algorithm...
        // Using squares to quickly find an approximate quotient.
        // Need to keep a running sum of the quotients as we approach the solution.
	//
        remainder=numerator_temp;
        while (remainder >= denominator || remainder < zero)
        {
            index = 0;
	    while (remainder >= zero) {
		index++;
		remainder = numerator_temp - (index*index)*denominator;
  	    }
            // Want the index before remainder went negative.
            index--;
            // Keep a running sum of the quotient.
            quotient += index*index;
            //  Calculate remainder for the corrected index.
            remainder = numerator_temp - (index*index)*denominator;
            //  Set a temp numerator to the remainder for the next while loop.
            numerator_temp = remainder;
        }


	//
	// Are there edge cases that aren't handled by the simple algorithm?
	// There's a slight possiblity that the quotient will overflow.
        // Can't have a time interval of more than 9,223,372,036,854,775,807 days.
        // Time interval can't be negative.

	//
	// Are there algorithms that can arrive at the answer much more efficiently?
        // One way to speed this algorithm up would be to move to divide into the TimeInterval class.
        // Then convert the time intervals to seconds.  By doing the math operations on seconds, repeated
        // calls to normalization are avoided.
        // Other alogorithms:  Newton–Raphson, Goldschmidt division, Binomial theorem, and I'm sure there's others
        // 
	//
}



int main(int argc, char **argv)
{
	TimeInterval numerator;
	TimeInterval denominator;
	TimeInterval remainder;
	long quotient;

	//
	// Add tests here to verify the correctness of your implementation
	// of interval division
	//

	numerator.setInterval(500, 0, 0);    // 500 days
	denominator.setInterval(0, 0, 200000);    // 0.2 seconds
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;

	numerator.setInterval(1, 0, 0);    // 1 day
	denominator.setInterval(0, 17280, 0);    // .2 days
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;

	numerator.setInterval(1, 0, 0);    // 1 day
	denominator.setInterval(0, 777, 0);    // 777 seconds
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;

	numerator.setInterval(0, 10, 0);    // 10 days
	denominator.setInterval(0, 0, 200000);    // 0.2 seconds
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;


	numerator.setInterval(0, 10, 0);    // 10 days
	denominator.setInterval(0, 10, 0);    // 10 seconds
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;

	numerator.setInterval(0, 10, 0);    // 10 days
	denominator.setInterval(0, 0, 0);    // 0 seconds
        // Try divide by zero
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;

	numerator.setInterval(0, 10, 0);    // 10 days
	denominator.setInterval(0, 20, 0);    // 20 seconds
        // Try divide where quotient is a fraction.
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;

	numerator.setInterval(30, 0, 0);    // 30 days
	denominator.setInterval(0, 92, 0);    // 92 seconds
	divide(numerator, denominator, quotient, remainder);
	cout << denominator << " divides " << numerator << " " << quotient << " times with a remainder of " << remainder << endl << endl;


	return 0;
}
