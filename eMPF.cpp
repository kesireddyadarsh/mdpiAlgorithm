//
//  eMPF.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/8/24.
//

#include "eMPF.hpp"


void empf(vector<individual_element>* p_ind_population,int number_of_objectives , int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this){
    
    bool constant_weight = true;
    int number_of_individuals = p_ind_population->size();
    int front_number_to_select = work_on_this.at(0).at(2);
    int mpf_front = work_on_this.at(0).at(2);
    vector<int> fronts;
    for (int individual = 0; individual < p_ind_population->size(); individual++) {
        if (p_ind_population->at(individual).front_number == mpf_front) {
            fronts.push_back(individual);
        }
    }
    vector<double> degree_of_diversification;
    
    if (constant_weight) {
        double equal_weight = 1.0/number_of_objectives;
        for (int objective = 0 ; objective < number_of_objectives; objective++) {
            degree_of_diversification.push_back(equal_weight);
        }
    }else{
        
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
            degree_of_diversification[objective] = entropy_objectives[objective] - 1;
            sum_of_diversification += degree_of_diversification[objective];
        }
        for (int objective = 0; objective < number_of_objectives; objective++) {
            degree_of_diversification[objective] /= sum_of_diversification;
        }
        
        // Your validation or further processing
        assert(entropy_objectives.size() == number_of_objectives);
        assert(degree_of_diversification.size() == number_of_objectives);
        
    }
    
    int best_index = -1;
    double best_value = std::numeric_limits<double>::max();
    
    if (fronts.size() >= 2) {
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
    }
    
    if (best_index != -1) {
        p_ind_population->at(best_index).hall_of_fame = true;
        cout << "Best Index: " << best_index << ", Hall of Fame: True" << endl;
    } else {
        cout << "No best index found." << endl;
    }
    
    p_ind_population->at(best_index).hall_of_fame = true;
    int index_of_hall_fame_number = best_index;
    
    
    //We have to apply HOF front_number_to_select
    //cout<<"This is the front number \t"<<front_number_to_select<<endl;
    //cout<<"This is the required number \t"<<required_number<<endl;
    
    //Fronts to remove
    for (int individual =0; individual < p_ind_population->size(); individual++) {
        if (p_ind_population->at(individual).front_number > front_number_to_select) {
            p_ind_population->at(individual).remove_me = true;
        }
    }
    
    fronts.clear();
    for (int individual = 0; individual < work_on_this.at(1).size(); individual++) {
        fronts.push_back(work_on_this.at(1).at(individual));
    }
    
    //Calculate the distance to HOF point to individual
    for (int individual = 0 ; individual < fronts.size(); individual++) {
        double temp_distance = 0.0;
        for (int objective = 0 ; objective < p_ind_population->at(fronts.at(individual)).overall_normalized_fitness_values.size(); objective++) {
            temp_distance += pow((p_ind_population->at(fronts.at(individual)).overall_normalized_fitness_values.at(objective)-p_ind_population->at(index_of_hall_fame_number).overall_normalized_fitness_values.at(objective)), 2);
            
        }
        temp_distance = sqrt(temp_distance);
        p_ind_population->at(fronts.at(individual)).distance_to_hall_of_fame = temp_distance;
    }
    
    //Sort them from low to high
    // cout<<required_number<<endl;
    //cout<<fronts.at(front_number_to_select).size()+required_number<<endl;
    
    int temp_required_values = (-work_on_this.at(0).at(1));
    
    //cout<<"This is for the break"<<endl;
    
    
    vector<double> temp_distance;
    for (int temp = 0 ; temp < fronts.size(); temp++) {
        temp_distance.push_back(p_ind_population->at(fronts.at(temp)).distance_to_hall_of_fame);
    }
    
    sort(temp_distance.begin(), temp_distance.end(),greater<double>());
    
    if (temp_distance.at(temp_distance.size()-1)) {
        temp_distance.pop_back();
    }
    
    for (int individual = 0; individual < temp_required_values; individual++) {
        for (int i = 0; i < fronts.size(); i++) {
            if (p_ind_population->at(fronts.at(i)).distance_to_hall_of_fame == temp_distance.at(individual)) {
                p_ind_population->at(fronts.at(i)).remove_me = true;
            }
        }
    }
    
    for (int individual = 0; individual < p_ind_population->size(); individual++) {
        if (p_ind_population->at(individual).remove_me) {
            p_ind_population->erase(p_ind_population->begin()+individual);
            individual = -1;
        }
    }
    assert(p_ind_population->size() == (number_of_individuals/2));
    
}
