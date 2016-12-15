#include <iostream>
#include <string>
using namespace std;

int main()
{
	int unitsSent;    //declaration of variables used in the program
	string title;
	double basePrice;
	char quality;
	double royalty;

	cout << "Units sent: ";         //asking for user input
	cin >> unitsSent;

	cin.ignore(10000, '\n');

	cout << "Title : ";
	getline(cin, title);
    //solves the getline problem when reading for a string after an int
	cout << "Base price: ";
	cin >> basePrice;
	cout << "Premium item? (y/n): ";
	cin >> quality;

	cout.setf(ios::fixed);
	cout.precision(2);              //sets the final output to the right number of digits for currency

	cout << "---\n";

	if (unitsSent < 0) {                     // several tests for validity of user input
		cout << "The number of units sent must be nonnegative." << endl;
	}
	else if (title == "") {	
		cout << "You must enter a title." << endl;
	}
	else if (basePrice < 0) {
		cout << "The base price must be nonnegative." << endl;
	}
	else if (quality != 'y' && quality != 'n') {
		cout << "You must enter y or n." << endl;
	}
	else {                                       // nested loop calculating royalty if validity test has passed

		if (unitsSent >= 0 && unitsSent <= 400) {           // calculating for 400 units and below
			royalty = 0.09 * basePrice * unitsSent;
		}
		else if (unitsSent > 400 && unitsSent <= 1200){      // calculating for between 400 and 1200 units
			if (quality == 'y')   // different percentage for premium status
				royalty = (0.09 * basePrice * 400) + (0.16 * basePrice * (unitsSent - 400));
			else
				royalty = (0.09 * basePrice * 400) + (0.13 * basePrice * (unitsSent - 400));
		}
		else if (unitsSent > 1200) {       // calculating for over 1200 units
			if (quality == 'y')   // different percentage for premium status
				royalty = (0.09 * basePrice * 400) + (0.16 * basePrice * 800) + (0.14 * basePrice * (unitsSent - 1200));
			else
				royalty = (0.09 * basePrice * 400) + (0.13 * basePrice * 800) + (0.14 * basePrice * (unitsSent - 1200));
		}

		cout << title << " earned $" << royalty << " in royalties." << endl; //outputting result

	}

}