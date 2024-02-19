//
//  nsga_ii.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/5/24.
//

#include "nsga_ii.hpp"

/*
 1. "fronts" have all the indexes of the individual elements which we need to perform NSGA- II
 2. First initialize crowding distance for all individals in the front
 3. For each objective:
    a. sort from high to low
    b. Assign Infinity to the boundary values
    c. Calculate the boundary distance for rest of the individuals
 4. Mark and remove all the rest of elements
 5. "work_on_this" has two set
    a. Index 0,0 -- 1 should perform algorithm; 0,1 -- number of elements to be removed; 0,2 -- the front number which we need to perform the algorithm
    b. Index 1 -- this contains all the index of individuals which are in the front and algorithm needs to applied on them.
 */


void nsga_ii(vector<individual_element>* p_ind_population, int number_of_objectives, int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this){
    
    int number_of_individuals = p_ind_population->size();
    int front_number_to_select = work_on_this.at(0).at(2);
    vector<int> fronts;
    for (int individual = 0 ; individual < work_on_this.at(1).size(); individual++) {
        fronts.push_back(work_on_this.at(1).at(individual));
    }
    
    // Initialize crowding distance for all individuals in the front
    for (int idx : fronts) {
        p_ind_population->at(idx).crowding_distance = 0.0;
    }
    
    // For each objective
    for (int objective = 0; objective < number_of_objectives; ++objective) {
        // Sort individuals in the front based on the current objective
        sort(fronts.begin(), fronts.end(), [&](const int& a, const int& b) {
            return p_ind_population->at(a).fitness_value[objective] < p_ind_population->at(b).fitness_value[objective];
        });
        
        // Assign infinite crowding distance to boundary individuals
        p_ind_population->at(fronts.front()).crowding_distance = std::numeric_limits<double>::infinity();
        p_ind_population->at(fronts.back()).crowding_distance = std::numeric_limits<double>::infinity();
        
        // Calculate crowding distance for each individual (except boundaries)
        for (size_t i = 1; i < fronts.size() - 1; ++i) {
            double prev_fitness = p_ind_population->at(fronts[i - 1]).fitness_value[objective];
            double next_fitness = p_ind_population->at(fronts[i + 1]).fitness_value[objective];
            double distance = p_ind_population->at(fronts[i]).crowding_distance;
            distance += next_fitness - prev_fitness;
            p_ind_population->at(fronts[i]).crowding_distance = distance;
        }
    }
    
    sort(fronts.begin(), fronts.end(), [&](const int& a, const int& b) {
        return p_ind_population->at(a).crowding_distance < p_ind_population->at(b).crowding_distance;
    });
    
    int numberOfIndividualsToRemove = -work_on_this.at(0).at(1); // Number of individuals to remove
    
    
    // Mark individuals for removal
    // Note: This assumes that the number of individuals to remove does not exceed the size of the front
    if(numberOfIndividualsToRemove > fronts.size()) {
        numberOfIndividualsToRemove = fronts.size(); // Ensure we do not exceed the number of available individuals
    }
    for (int i = 0; i < numberOfIndividualsToRemove; ++i) {
        p_ind_population->at(fronts[i]).remove_me = true;
    }
    
    select_remove_individuals(p_ind_population, work_on_this.at(0).at(2));
    
    
}



