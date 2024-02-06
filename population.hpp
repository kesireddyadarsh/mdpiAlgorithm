//
//  population.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/2/24.
//

#ifndef population_hpp
#define population_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "individual_element.hpp"

using namespace std;

class population{
public:
    vector<individual_element> ind_population;
    vector<individual_element>* p_ind_population = &ind_population;
};
#endif /* population_hpp */
