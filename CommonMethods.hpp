//
//  CommonMethods.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/2/24.
//

#ifndef CommonMethods_hpp
#define CommonMethods_hpp

#include <stdio.h>
#include <string>
#include <bitset>
#include <random>
#include <assert.h>

#include "individual_element.hpp"
#include "population.hpp"

using namespace std;

#define PI 3.14159265

double fRand(double fMin, double fMax);
string realToBinaryString(double realNumber, int precision = 10);
double binaryStringToReal(const string& binaryString);
void cal_normalized_fitness_values(vector<individual_element>* p_ind_population, int number_of_objectives);
void mutate(vector<individual_element>* p_ind_population,int individual,bool negative_value_accepted);
bool compare_two_index(vector<individual_element>* p_ind_population,int individual ,int other_individual);
vector<double> generateUniqueRandomNumbers(double mean, double std_dev, int count);
void assign_front_number(vector<individual_element>* p_ind_population);

#endif /* CommonMethods_hpp */
