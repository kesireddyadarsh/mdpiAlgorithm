//
//  eMPF.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/8/24.
//

#include "eMPF.hpp"

vector<double> find_degree_of_diversification(vector<individual_element>* p_ind_population, vector<int> fronts, int number_of_objectives){
    
    vector<double> degree_of_diversification_internal;
    double constant_h = (fronts.size() == 1) ? 1.0 : 1.0 / log(fronts.size());
    vector<double> entropy_objectives(number_of_objectives, 0.0);
    
    // Assuming Individual structure and fitness_value are defined correctly
    for (int objective = 0; objective < number_of_objectives; objective++) {
        double min_fitness = numeric_limits<double>::max();
        double sum_positive_shifted_fitness = 0.0;
        
        // Find minimum fitness value for the objective to shift all values to positive
        for (int individual : fronts) {
            double fitness = p_ind_population->at(individual).fitness_value[objective];
            min_fitness = min(min_fitness, fitness);
        }
        double shift_value = (min_fitness < 0) ? abs(min_fitness) + 1 : 0;
        
        // Calculate shifted sum for normalization
        for (int individual : fronts) {
            double shifted_fitness = p_ind_population->at(individual).fitness_value[objective] + shift_value;
            sum_positive_shifted_fitness += shifted_fitness;
        }
        
        // Calculate normalized values and entropy for each objective
        vector<double> normalized_fitness(fronts.size(), 0.0);
        for (int i = 0; i < fronts.size(); i++) {
            int individual = fronts[i];
            normalized_fitness[i] = (p_ind_population->at(individual).fitness_value[objective] + shift_value) / sum_positive_shifted_fitness;
            
            // Avoid log(0) by ensuring there's a minimal positive value
            if (normalized_fitness[i] > 0) {
                entropy_objectives[objective] -= normalized_fitness[i] * log(normalized_fitness[i]);
            }
        }
        entropy_objectives[objective] *= constant_h;
    }
    
    // Calculate degree of diversification
    double sum_of_diversification = 0.0;
    for (int objective = 0; objective < number_of_objectives; objective++) {
        degree_of_diversification_internal.push_back(entropy_objectives[objective] - 1);
        sum_of_diversification += degree_of_diversification_internal[objective];
    }
    for (int objective = 0; objective < number_of_objectives; objective++) {
        degree_of_diversification_internal[objective] /= sum_of_diversification;
    }
    
    // Your validation or further processing
    assert(entropy_objectives.size() == number_of_objectives);
    assert(degree_of_diversification_internal.size() == number_of_objectives);
    
    return degree_of_diversification_internal;
}


void empf(vector<individual_element>* p_ind_population,int number_of_objectives , int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this){
    
    //This is for debugging frontnumbers
    vector<vector<int>> debug_fronts;
    vector<int> temp_fronts;
    for (int value = 0; value < 100; value++) {
        for (int individual = 0; individual < p_ind_population->size(); individual++) {
            if (p_ind_population->at(individual).front_number == value) {
                temp_fronts.push_back(p_ind_population->at(individual).front_number);
            }
        }
        debug_fronts.push_back(temp_fronts);
    }
    
    int number_of_individuals = p_ind_population->size();
    int front_number_to_select = work_on_this.at(0).at(2);
    int mpf_front = work_on_this.at(0).at(2);
    int number_to_remove = -work_on_this.at(0).at(1); //remove to next generation
    int value_holder = work_on_this.at(1).size() - number_to_remove; //number to next generation
    vector<int> fronts;
    for (int individual = 0; individual < p_ind_population->size(); individual++) {
        if (p_ind_population->at(individual).front_number == mpf_front) {
            fronts.push_back(individual);
        }
    }
    std::vector<int> min_fitness_indexes(number_of_objectives, -1); // Initialize with invalid index
    
    // Iterate over objectives
    for (int objective = 0; objective < number_of_objectives; ++objective) {
        
        double min_fitness = std::numeric_limits<double>::max();
        for (int index : fronts) {
            if (p_ind_population->at(index).fitness_value[objective] < min_fitness) {
                min_fitness = p_ind_population->at(index).fitness_value[objective];
                min_fitness_indexes[objective] = index;
            }
        }
    }
    std::sort(min_fitness_indexes.begin(), min_fitness_indexes.end());
    auto last = std::unique(min_fitness_indexes.begin(), min_fitness_indexes.end());
    min_fitness_indexes.erase(last, min_fitness_indexes.end());
    
    // Remove the indexes stored in min_fitness_indexes from fronts
    for (int index : min_fitness_indexes) {
        fronts.erase(std::remove(fronts.begin(), fronts.end(), index), fronts.end());
    }
    
    vector<double> degree_of_diversification = find_degree_of_diversification(p_ind_population, fronts, number_of_objectives);
//    vector<double> degree_of_diversification;
//    double we = 1.0/number_of_objectives;
//    for (int i_t = 0; i_t < number_of_objectives; i_t++) {
//        degree_of_diversification.push_back(we);
//    }
    
    int best_index = -1;
    double best_value = std::numeric_limits<double>::max();
    
    vector<double> ideal_best(number_of_objectives, std::numeric_limits<double>::lowest());
    vector<double> ideal_worst(number_of_objectives, std::numeric_limits<double>::max());
    
    // Calculate normalized values based on degree_of_diversification and fitness values
    for (int individual : fronts) {
        for (int objective = 0; objective < number_of_objectives; objective++) {
            double normalized_value = degree_of_diversification[objective] * p_ind_population->at(individual).fitness_value[objective];
            p_ind_population->at(individual).normalized_fitness_values.push_back(normalized_value);
            
            // Update ideal best and worst
            ideal_best[objective] = max(ideal_best[objective], normalized_value);
            ideal_worst[objective] = min(ideal_worst[objective], normalized_value);
        }
    }
    
    // Calculate Euclidean distances and performance score
    for (int individual : fronts) {
        double euclidean_best = 0.0;
        double euclidean_worst = 0.0;
        for (int objective = 0; objective < number_of_objectives; objective++) {
            euclidean_best += pow(p_ind_population->at(individual).normalized_fitness_values[objective] - ideal_best[objective], 2);
            euclidean_worst += pow(p_ind_population->at(individual).normalized_fitness_values[objective] - ideal_worst[objective], 2);
        }
        p_ind_population->at(individual).euclidean_best = sqrt(euclidean_best);
        p_ind_population->at(individual).eculidean_worst = sqrt(euclidean_worst);
        
        // Calculate performance score
        p_ind_population->at(individual).performance_score = p_ind_population->at(individual).eculidean_worst / (p_ind_population->at(individual).eculidean_worst + p_ind_population->at(individual).euclidean_best);
        
        // Update best alternative
        if (best_value > p_ind_population->at(individual).performance_score) {
            best_value = p_ind_population->at(individual).performance_score;
            best_index = individual;
        }
    }
    
    
    if (best_index != -1) {
        p_ind_population->at(best_index).hall_of_fame = true;
        cout << "Best Index: " << best_index << ", Hall of Fame: True" << endl;
    } else {
        cout << "No best index found." << endl;
    }
    
    p_ind_population->at(best_index).hall_of_fame = true;
    int index_of_hall_fame_number = best_index;
    
    
    //Calculate the distance to HOF point to individual
    for (int individual = 0 ; individual < fronts.size(); individual++) {
        double temp_distance = 0.0;
        for (int objective = 0 ; objective < p_ind_population->at(fronts.at(individual)).overall_normalized_fitness_values.size(); objective++) {
            temp_distance += pow((p_ind_population->at(fronts.at(individual)).overall_normalized_fitness_values.at(objective)-p_ind_population->at(index_of_hall_fame_number).overall_normalized_fitness_values.at(objective)), 2);
            
        }
        temp_distance = sqrt(temp_distance);
        p_ind_population->at(fronts.at(individual)).distance_to_hall_of_fame = temp_distance;
    }
    
    for (int temp = 0; temp < min_fitness_indexes.size(); temp++) {
        fronts.push_back(min_fitness_indexes.at(temp));
        p_ind_population->at(min_fitness_indexes.at(temp)).distance_to_hall_of_fame = 0.0;
    }
    
    std::sort(fronts.begin(), fronts.end(), [&](const int& a, const int& b) {
        return p_ind_population->at(a).distance_to_hall_of_fame < p_ind_population->at(b).distance_to_hall_of_fame;
    });
    
    //First set everthing to remove.
    int loopcounter = fronts.size()-1;
    while (number_to_remove > 0) {
        p_ind_population->at(fronts.at(loopcounter)).remove_me = true;
        number_to_remove--;
        loopcounter--;
    }
    
    select_remove_individuals(p_ind_population, work_on_this.at(0).at(2));
    
}
