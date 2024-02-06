//
//  nsga_ii.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/5/24.
//

#ifndef nsga_ii_hpp
#define nsga_ii_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <math.h>

#include "population.hpp"
#include "TestScenario.hpp"
#include "CommonMethods.hpp"

using namespace std;


void nsga_ii(vector<individual_element>* p_ind_population,int number_of_objectives, int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this);


#endif /* nsga_ii_hpp */
