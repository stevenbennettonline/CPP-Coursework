/* My code calculates the expected values for k, using intial guesses of EA and A in the function expected_calculated. This is passed to chi_squared function,
along with observed k values, to calculate the chi_squared. I have used functions so the calculations can be easily replicated throughout the main function. 
The code aims to minimise chi squared values by calculating the next chi squared value and comparing it to the first one. This is done for EA and then A to 
find the optimum value. The incremenet of change is then halved untill it is below a certain threshold, at which time the loop ends. */

#include <stdio.h>     
#include <iostream>     
#include <cmath>        
#include <string>       
#include <sstream>      
#include <fstream>  
// Define include functions

using namespace std;
    

float chi_squared(float observed[], float expected[]) // This function takes the input of two arrays, observed values and expected values, and calculates chi-squared 
{
    float chi_squared = 0; 
    for(int i = 0; i < 8; i++) // Use for loop for a sum for all expected values
    {
        chi_squared += (pow((observed[i]-expected[i]), 2)/ expected[i]);
    }
    return chi_squared;
}

float* expected_calculated(int T[], float ea, float a, float* expected_k) // This function outputs a pointer to array expected_calculated. This function calculates expected k values for the chi squared calculations using guessed values of EA and A.
{

    for(int i = 0; i < 8; i++) // For loop iterates through the array and changes array values to expected k values
    {
        expected_k[i] = a*exp(-(ea*1e3)/(8.3145*T[i]));
        cout << expected_k[i];
    }
    return expected_k;
}


int main() 
{
    float* expected_k = (float*)malloc(32); // Frees up memory for the array of expected values
    int T[8] = { 700, 730, 760, 790, 810, 840, 910, 1000 };
    float observed_k[8] = {0.011, 0.035, 0.105, 0.343, 0.789, 2.17, 20.0, 145}; // Declares arrays, observed k and T
    float ea = 0; 
    float a = 0;
    float change_ea = 10;
    float change_a = 0.1e12;
    float chi_squared_min = 0;
    float a_min = 0;
    float ea_min = 0;
    // Declare all the variables the section above 
    
    cout << "Please enter your starting guess of EA? " << endl;
    cin >> ea;
    cout << "Please enter your starting guess of A? (in e12)" << endl;
    cin >> a;
    
    a*=1e12;
    while(change_ea > 1)
    {
        float chi_squared_1 = chi_squared(expected_calculated(T, ea, a, expected_k), observed_k);
        float chi_squared_2 = chi_squared(expected_calculated(T, ea + change_ea, a, expected_k), observed_k); // For the given EA and A values, this passes them into the function to calculate expected k and then to calculate Chi Squared
        cout << chi_squared_2 << endl;
        if(chi_squared_1 > chi_squared_2) // Checks if Chi Squared for the higher EA value is lower 
        {
            ea += change_ea; // If it is lower, change EA to the new value
            ea_min = ea; // Change the minimum EA value
            chi_squared_min = chi_squared_2; // Change the minimum Chi Squared value
        }
        else
        {

            change_ea /= 2; // If Chi Squared is bigger, change the increment for EA 

            while(change_a > 0.1e11) // Now optimise the A value
            {
                float chi_squared_1 = chi_squared(expected_calculated(T, ea, a, expected_k), observed_k);
                float chi_squared_2 = chi_squared(expected_calculated(T, ea, a + change_a, expected_k), observed_k); // Checks for the optimal A value

                if (chi_squared_1 > chi_squared_2) // Checks the next Chi Squared value for the next A incremen
                {
                    a += change_a; // If it is lower, change the A value
                    a_min = a;  // Change minimum A value
                    chi_squared_min = chi_squared_2; // Change the minimum value of Chi Squared
                }
                else // If it isn't, change the increment of A and try again 
                {
                    change_a /= 2;
                    
                }
            }
        }
    }
    free(expected_k);

    //Output variables
    cout << "The minimum Chi Squared value is: " << chi_squared_min << endl;
    cout << "This is for the EA value: " << ea_min <<" kJ mol^-1" << endl;
    cout << "This is for the A value: " << a_min << " L mol^-1 s^-1" << endl;
    return 0;
}