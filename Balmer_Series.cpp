




/* Code gets number of protons and neutrons from the user. Calculates the reduced mass and Rydberg constant by passing these values to their respective functions. The Balmer series is then calculated for the atom 
and the first three lowest energy transitions of positronium, using the same functions that originally used for calculating the Balmer series. The Lande g-factor is then generated, getting user input for quantum number values*/



#include <stdio.h>     
#include <iostream>     
#include <cmath>        
#include <string>       
#include <sstream>      
#include <fstream>  
#include <iomanip> 

using namespace std;

// Function that calculates the reduced mass using inputs for the mass of the hydrogen-like atom
double reducedMass(float mass)
{
	double reducedMass = (9.109e-31*(mass*1.6605e-27)/(9.109e-31 + (mass*1.6605e-27)));
	return reducedMass;
}

// Calculates the Rydberg constant, taking the reduced mass as input. 
double rydbergConstant(double reducedMass)
{
	double rydbergConstant;
	rydbergConstant = (reducedMass/9.109e-31)*109737;
	return rydbergConstant;
}

// Function that calculates the difference energy of the transitions, taking Rcalc as input. 
float sigma_calculations(int n1, int n2, double rcalc)
{
	float sigma = -rcalc*((1/pow(n2,2)) - (1/pow(n1,2)));
	return sigma;
}


int main() {

	// Declaring variables
	int neutrons;
	int protons; 
	double rydberg_constant;
	// Provides the user with the names for the first 6 hydrogen-like atoms. 
	string atom_name[6] = {"H", "He+", "Li2+", "Be3+", "B4+", "C5+" };

	// Gets input from the user of number of protons and neutrons
	cout << "How many neutrons in the hydrogen-like atom?" << endl;
	cin >>	neutrons;
	cout << "How many protons in hydrogen-like atom?" << endl;
	cin >> protons;

	// Calculates the Rydberg constant, by calling the functions for reduced mass and Rydberg constant
	rydberg_constant = rydbergConstant(reducedMass(protons + neutrons));

	// If and else statements that output the name of the hydrogen-like atom.
	if(protons < 6 && protons > 0) {
		cout << "\nThe Rydberg Constant for " << atom_name[protons - 1] << " is " << rydberg_constant << "cm^-1.\n" << endl;
	}
	else if(protons <= 0) {
		cout << "Please enter a valid number of protons." << endl;
		return 1;
	}
	else {
		cout << "\nThe Rydberg Constant is " << rydberg_constant << "cm^-1.\n" << endl;
	}

	// Balmer Series calculations using for loop and the Rydberg constant
	cout << "The first five lines of the Balmer series are: " << endl;
	for(int i = 3; i < 8; i++)
	{	
		float balmer_num = sigma_calculations(2, i, rydberg_constant);
		cout << i << " --> 2 : " << balmer_num << " cm^-1 --- " << setprecision(3) << 6.626e-34*2.998e8*balmer_num*1e2 << " J --- " << (6.626e-34*2.998e8*balmer_num*1e2)/1.602e-19 << " eV." << setprecision(6) << endl;

	}


	// Positronium calculations that use the Rydberg constant function and a for loop to calculate the 3 lowest energy transitions.
	cout << "\nThe three lowest energy lines for the Positronium are: " << endl;
	double poistronium_mass = 0.000548756; 
	cout << reducedMass(poistronium_mass) << endl;
	rydberg_constant = rydbergConstant(reducedMass(poistronium_mass));

	for(int i = 1; i < 4; i++)
	{		
		float balmer_num = sigma_calculations(i, i+1, rydberg_constant);
		cout << i << " --> " << i + 1 << ": " << balmer_num << " cm^-1 --- " << setprecision(3) << 6.626e-34*2.998e8*balmer_num*1e2 << " J --- " << (6.626e-34*2.998e8*balmer_num*1e2)/1.602e-19 << " eV." << setprecision(6) << endl;
	}


	// Calculating Lande g-factor
	// Declaring variables
	int j;
	int s;
	int l;
	cout << "\nEnter value of j: " << endl;
	cin >> j;
	cout << "Enter value of s: " << endl;
	cin >> s;
	cout << "Enter value of l: " << endl;
	cin >> l;

	// Equation that calculates Lande g-factor.
	float g = (3*j*(j+1)+s*(s+1)-l*(l+1))/(2*j*(j+1));

	cout << "The Lande g-factor is: " << g << endl;

	return 0;

}