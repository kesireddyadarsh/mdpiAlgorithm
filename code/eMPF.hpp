//
//  eMPF.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/8/24.
//

#ifndef eMPF_hpp
#define eMPF_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <cmath>
#include <assert.h>
#include <algorithm>
#include <map>
#include <set>

#include "population.hpp"
#include "CommonMethods.hpp"
#include "TestScenario.hpp"

using namespace std;

vector<double> find_degree_of_diversification(vector<individual_element>* p_ind_population, vector<int> fronts, int number_of_objectives);
void empf(vector<individual_element>* p_ind_population,int number_of_objectives , int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this);


#endif /* eMPF_hpp */
