/* The code opens the file "StatNum.txt", putting each line of the text file into a string, which is converted into an int. 
This is then stored in an array and statistics calculated using the sumIntegers function. These are then printed into the console. */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

/* Function that gets passed the int array and
calculates sum or sum mean difference depending
on the mean's value. */

float sumIntegers(int integers[], int size, float mean)
{
	float sum = 0;
	for (int i = 0; i < size; i++) // For loop goes through the array and calculates the sum or sum mean difference squared, depending on the mean's value passed to the function
	{
		if (mean != 0)
		{
			sum += pow((integers[i] - mean), 2); // If mean = 0, calculate sum mean difference
		}
		else
		{
			sum += integers[i]; // Calculates the sum
		}

	}
	return sum;
}

int main() {
	// Declaring variables
	int integers[100];
	int size = 0, dp;
	string number;

	ifstream myfile("StatNum.txt"); // Opens the file
	if (myfile.is_open()) // Check if the file is open
	{
		while (!myfile.eof()) // Repeats until at the end of file
		{
			getline(myfile, number);
			istringstream convert(number); // Gets a line and converts it to an int
			if (!(convert >> integers[size]))
				integers[size] = 0; // Checks the number has been correctly stored in the array, if not make 0
			size++; // Add 1 to size to find the total numbers of integers
		}
	}
	else
	{
		cout << "Error opening the file." << endl;
		return 1; // Checks to see if the file has opened correctly, if not, ends program
	}
	myfile.close();

	// Variables to calcuilate different statistics using the sumIntegers function

	int sum = sumIntegers(integers, size, 0); // Passes values to sumIntegers function to calculate the sum
	float mean = (float)sum / (float)size; // Calculates the mean 
	float sum_mean_difference = sumIntegers(integers, size, mean); // Calculates the sum mean difference squared using the sumIntegers functions
	float standard_deviation = sqrt((float)sum_mean_difference / ((float)size - 1)); // Calculates standard deviation

	// Gets the number of decimal places
	cout << "How many decimal places would you like the mean and standard deviation?" << endl;
	cin >> dp;
	cout << setprecision(dp) << fixed; // Sets the precision of the decimal places for any float values

	// Prints the statistics to the screen.
	cout << "The sum is: " << sum << endl;
	cout << "The average is: " << mean << endl;
	cout << "The standard deivation is: " << standard_deviation << endl;
	return 0;
}