//
//  MPF.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/7/24.
//

#ifndef MPF_hpp
#define MPF_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <cmath>
#include <assert.h>
#include <algorithm>
#include <map>

#include "population.hpp"
#include "CommonMethods.hpp"
#include "TestScenario.hpp"

using namespace std;

void mpf(vector<individual_element>* p_ind_population,int number_of_objectives , int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this);

#endif /* MPF_hpp */
