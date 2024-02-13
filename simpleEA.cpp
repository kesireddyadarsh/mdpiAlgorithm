//
//  simpleEA.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/4/24.
//

#include "simpleEA.hpp"



void simple_ea(vector<individual_element>* p_ind_population){
    
    int number_of_neurals = p_ind_population->size();
    
    for (int individual = 0 ; individual < p_ind_population->size(); individual++) {
        p_ind_population->at(individual).summation_fitness_value = 0.0;
        for (int fit_loop = 0 ; fit_loop < p_ind_population->at(individual).fitness_value.size(); fit_loop++) {
            p_ind_population->at(individual).summation_fitness_value += p_ind_population->at(individual).fitness_value.at(fit_loop);
        }
    }
    
    for (int elimination = 0 ; elimination < (number_of_neurals/2); elimination++) {
        int rand_1 = rand()%p_ind_population->size();
        int rand_2 = rand()%p_ind_population->size();
        while (rand_1 == rand_2) {
            rand_1 = rand()%p_ind_population->size();
            rand_2 = rand()%p_ind_population->size();
        }
        
        if (p_ind_population->at(rand_1).summation_fitness_value < p_ind_population->at(rand_2).summation_fitness_value) {
            p_ind_population->erase(p_ind_population->begin()+rand_2);
        }else{
            p_ind_population->erase(p_ind_population->begin()+rand_1);
        }
    }
    assert(p_ind_population->size() == (number_of_neurals/2));

}


