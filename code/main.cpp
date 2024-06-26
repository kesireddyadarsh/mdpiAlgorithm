//
//  main.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/2/24.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <set>

#include "individual_element.hpp"
#include "population.hpp"
#include "CommonMethods.hpp"
#include "TestScenario.hpp"
#include "printToFile.hpp"
#include "simpleEA.hpp"
#include "nsga_ii.hpp"
#include "nsga_iii.hpp"
#include "MPF.hpp"
#include "eMPF.hpp"

using namespace std;


extern const double PRECISION = 100000.0;
extern const bool negative_value_accepted = true;


int main(int argc, const char * argv[]) {
    unsigned int seed = time(0) + clock() + getpid();
    srand(seed);
    
    for (int simulation_run = 0; simulation_run < 30; simulation_run++) {
        population pop;
        int number_of_population = 100;
        int case_number = 21;//This is objective number
        int number_of_objectives = 2;
        int case_to_study = 4;
        
        for (int generation = 0 ; generation < 1000; generation++) {
            if (generation == 0 ) {
                for (int individual = 0; individual < number_of_population; individual++) {
                    individual_element element;
                    pop.ind_population.push_back(element);
                    vector<double> temp_x_values = limitation_values(case_number);
                    
                    for(int i = 0; i< temp_x_values.size();i++){
                        pop.ind_population.at(individual).all_x.push_back(temp_x_values.at(i));
                    }
                    pop.ind_population.at(individual).remove_me = false;
                    
                    exe_function( pop.p_ind_population, individual, case_number);
                    
                }
            }else{
                
                for (int individual = 0; individual < number_of_population; individual++) {
                    pop.ind_population.at(individual).remove_me = false;
                    pop.ind_population.at(individual).fitness_value.clear();
                    pop.ind_population.at(individual).normalized_fitness_values.clear();
                    pop.ind_population.at(individual).overall_normalized_fitness_values.clear();
                    pop.ind_population.at(individual).crowding_distance = 0.0;
                    pop.ind_population.at(individual).distance_to_hall_of_fame = std::numeric_limits<double>::max();
                    pop.ind_population.at(individual).hall_of_fame = false;
                    exe_function( pop.p_ind_population, individual, case_number);
                    
                }
            }
            
            printValues(pop, simulation_run, generation, case_number, case_to_study);
            cal_normalized_fitness_values(pop.p_ind_population, number_of_objectives);
            vector<vector<int>> hold_values_for_algorithm = assign_front_number(pop.p_ind_population);
            
            if (hold_values_for_algorithm.at(0).at(0) == 0) {
                for (int individual = 0 ; individual < pop.ind_population.size(); individual++) {
                    if (pop.ind_population.at(individual).front_number > hold_values_for_algorithm.at(0).at(2)) {
                        pop.ind_population.at(individual).remove_me = true;
                    }
                }
                
                for (int individual = 0 ; individual < pop.ind_population.size(); individual++) {
                    if (pop.ind_population.at(individual).remove_me) {
                        pop.ind_population.erase(pop.ind_population.begin() + individual);
                        individual = -1;
                    }
                }
            }else{
                
                switch (case_to_study) {
                    case 0:
                    {
                        simple_ea(pop.p_ind_population);
                        break;
                    }
                        
                    case 1:
                    {
                        nsga_ii(pop.p_ind_population,number_of_objectives, generation, negative_value_accepted, hold_values_for_algorithm);
                        break;
                    }
                        
                    case 2:
                    {
                        nsga_iii(pop.p_ind_population, number_of_objectives, generation, negative_value_accepted,hold_values_for_algorithm);
                        break;
                    }
                        
                    case 3:
                    {
                        mpf(pop.p_ind_population, number_of_objectives, generation, negative_value_accepted, hold_values_for_algorithm);
                        break;
                    }
                        
                    case 4:
                    {
                        if (hold_values_for_algorithm.at(1).size() <= 3) {
                            set<int> used_numbers;
                            for (int individual = 0 ; individual< -hold_values_for_algorithm.at(0).at(1); individual++) {
                                int random_number = rand()%hold_values_for_algorithm.at(1).size();
                                while (used_numbers.find(random_number) != used_numbers.end()) { // Check if the number is already used
                                        random_number = rand() % hold_values_for_algorithm.at(1).size(); // Generate a new number if the previous one was used
                                    }
                                    used_numbers.insert(random_number);
                                pop.ind_population.at(hold_values_for_algorithm.at(1).at(random_number)).remove_me = true;
                            }
                            for (int individual = 0 ; individual < pop.ind_population.size(); individual++) {
                                if (pop.ind_population.at(individual).front_number > hold_values_for_algorithm.at(0).at(2)) {
                                    pop.ind_population.at(individual).remove_me = true;
                                }
                            }
                            
                            for (int individual = 0 ; individual < pop.ind_population.size(); individual++) {
                                if (pop.ind_population.at(individual).remove_me) {
                                    pop.ind_population.erase(pop.ind_population.begin() + individual);
                                    individual = -1;
                                }
                            }
                        }else{
                            empf(pop.p_ind_population, number_of_objectives, generation, negative_value_accepted, hold_values_for_algorithm);
                        }
                        break;
                    }
                        
                        
                    default:
                        break;
                }
            }
            
            
            
            assert(pop.ind_population.size() == (number_of_population/2));
            
            for (unsigned int neural = pop.ind_population.size()  ; neural < (number_of_population); neural++) {
                int rand_1 = (rand()%(number_of_population/2));
                pop.ind_population.push_back(pop.ind_population.at(rand_1));
                unsigned int last_value = pop.ind_population.size() - 1;
                mutate(pop.p_ind_population,last_value,negative_value_accepted);
                int loop_counter = 0;
                while (!check_constrains_vec(pop.ind_population.at(last_value).all_x, case_number)){
                    mutate(pop.p_ind_population,last_value,negative_value_accepted);
                    loop_counter++;
                    if (loop_counter == 100) {
                        pop.ind_population.at(last_value).all_x.clear();
                        vector<double> temp_x_values = limitation_values(case_number);
                        for(int i = 0; i< temp_x_values.size();i++){
                            pop.ind_population.at(last_value).all_x.push_back(temp_x_values.at(i));
                        }
                    }
                }
            }
            
            
            assert(pop.ind_population.size() == (number_of_population));
        }
        
        
    }
    
   
    return 0;
}
