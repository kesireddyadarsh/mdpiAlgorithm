//
//  TestScenario.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/2/24.
//

#ifndef TestScenario_hpp
#define TestScenario_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>


#include "CommonMethods.hpp"
#include "population.hpp"

using namespace std;

bool check_constrains_vec(vector<double> x_value_vec, int case_number);
vector<double> limitation_values(int case_number);
void exe_function(vector<individual_element>* p_ind_population, int individual, int case_number);


#endif /* TestScenario_hpp */
