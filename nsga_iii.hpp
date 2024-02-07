//
//  nsga_iii.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/6/24.
//

#ifndef nsga_iii_hpp
#define nsga_iii_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <map>

#include "CommonMethods.hpp"
#include "population.hpp"
#include "TestScenario.hpp"

using namespace std;

// Placeholder for individual and reference point structures
struct ReferencePoint {
    vector<double> position;
};


vector<ReferencePoint> generateReferencePoints(int divisions, int objectives);
double calculatePerpendicularDistance(const individual_element& individual, const ReferencePoint& rp);
void markForRemovalUsingNiching(vector<individual_element>* population,  vector<int> fronts, int front_number, int num_to_remove);
void associateAndCalculateDistances(vector<individual_element>* p_ind_population, const vector<ReferencePoint>& referencePoints);
void nsga_iii(vector<individual_element>* p_ind_population,int number_of_objectives, int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this);

#endif /* nsga_iii_hpp */
