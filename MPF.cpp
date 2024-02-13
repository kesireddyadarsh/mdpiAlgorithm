//
//  MPF.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/7/24.
//

#include "MPF.hpp"

void mpf(vector<individual_element>* p_ind_population,int number_of_objectives , int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this){
    
    int number_of_individuals = p_ind_population->size();
    int front_number_to_select = work_on_this.at(0).at(2);
    int mpf_front = 0;
    vector<int> fronts;
    for (int individual = 0; individual < p_ind_population->size(); individual++) {
        if (p_ind_population->at(individual).front_number == mpf_front) {
            fronts.push_back(individual);
        }
    }
    
    //Calculating entropy
    double entropy_h = 0.0;
    if (fronts.size() == 1) {
        entropy_h = 1.0;
    }else{
        entropy_h = 1/log(fronts.size());
    }
    
    //Calculating entropy of each objective
    vector<double> entropy_objectives;
    for (int objective = 0 ; objective < number_of_objectives; objective++) {
        //First summation of each objective
        double summation_of_fitness = 0.0;
        for (int individual = 0 ; individual < fronts.size(); individual++) {
            summation_of_fitness += p_ind_population->at(fronts.at(individual)).fitness_value.at(objective);
        }
        
        //Normalization of the fitness values
        for (int individual = 0 ; individual < fronts.size(); individual++) {
            p_ind_population->at(fronts.at(individual)).normalized_fitness_values_entropy.push_back(p_ind_population->at(fronts.at(individual)).fitness_value.at(objective)/summation_of_fitness);
        }
    }
    
    for (int main_loop_objective = 0 ; main_loop_objective < number_of_objectives; main_loop_objective++) {
        double summation = 0.0;
        for (int individual = 0 ; individual < fronts.size(); individual++) {
            double temp_natural_log = 0.0;
            if (p_ind_population->at(fronts.at(individual)).normalized_fitness_values_entropy.at(main_loop_objective) == 0) {
                temp_natural_log = 0.0;
            }else if (p_ind_population->at(fronts.at(individual)).normalized_fitness_values_entropy.at(main_loop_objective) <0){
                temp_natural_log = log(-p_ind_population->at(fronts.at(individual)).normalized_fitness_values_entropy.at(main_loop_objective));
            }else{
                temp_natural_log = log(p_ind_population->at(fronts.at(individual)).normalized_fitness_values_entropy.at(main_loop_objective));
            }
            
            summation += (p_ind_population->at(fronts.at(individual)).normalized_fitness_values_entropy.at(main_loop_objective)*temp_natural_log);
        }
        entropy_objectives.push_back(summation*(-entropy_h));
    }
    assert(entropy_objectives.size() == number_of_objectives);
    
    vector<double> degree_of_diversification;
    double summation_of_diversification = 0.0;
    for (int objective = 0 ; objective < entropy_objectives.size(); objective++) {
        double temp = entropy_objectives.at(objective) -1;
        degree_of_diversification.push_back( temp);
        summation_of_diversification += temp;
    }
    assert(degree_of_diversification.size() == number_of_objectives);
    
    for (int objective = 0 ; objective < number_of_objectives; objective++) {
        degree_of_diversification.at(objective) /= summation_of_diversification;
    }
    
    
    
    int best_index = 999999;
    double best_value = 99999999.99999;
    
    if (fronts.size() >= 2) {
        //double weights = 0.50;
        //cout<<weights<<endl;
        vector<double> ideal_best;
        vector<double> ideal_worst;
        vector<int> index_ideal_best;
        vector<int> index_ideal_worst;
        
        for (int objective = 0; objective < number_of_objectives; objective++) {
            double summation_objective = 0.0;
            for (int individual = 0 ; individual < fronts.size(); individual++) {
                summation_objective += (p_ind_population->at(fronts.at(individual)).fitness_value.at(objective)); //*p_ind_population->at(fronts.at(0).at(individual)).fitness_value.at(objective));
                p_ind_population->at(fronts.at(individual)).euclidean_best = 9999999.99999;
                p_ind_population->at(fronts.at(individual)).eculidean_worst = -9999999.99999;
            }
            //cout<<summation_objective<<endl;
            
            for (int individual = 0 ; individual < fronts.size(); individual++) {
                if (summation_objective == 0) {
                    summation_objective = 0.00001;
                }
                //cout<<summation_objective<<endl;
                if (summation_objective < 0) {
                    p_ind_population->at(fronts.at(individual)).normalized_fitness_values.push_back( (degree_of_diversification.at(objective) * (p_ind_population->at(fronts.at(individual)).fitness_value.at(objective)) / sqrt(-summation_objective)));
                }else{
                    p_ind_population->at(fronts.at(individual)).normalized_fitness_values.push_back( (degree_of_diversification.at(objective) * (p_ind_population->at(fronts.at(individual)).fitness_value.at(objective)) / sqrt(summation_objective)));
                }
            }
            
            double temp_ideal_best =999999999.99999;
            double temp_ideal_worst =  -9999999999.99999;
            int temp_index_ideal_best = 999999;
            int temp_index_ideal_worst = 999999;
            
            for (int individual = 0; individual < fronts.size(); individual++) {
                if (temp_ideal_best > p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(objective)) {
                    temp_ideal_best = p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(objective);
                    temp_index_ideal_best = individual;
                }
                
                if (temp_ideal_worst < p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(objective)) {
                    temp_ideal_worst = p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(objective);
                    temp_index_ideal_worst = individual;
                }
            }
            
            if (temp_ideal_best == temp_ideal_worst) {
                temp_index_ideal_best = rand()%fronts.size();
                temp_index_ideal_worst = rand()%fronts.size();
            }
            
            ideal_best.push_back(temp_ideal_best);
            ideal_worst.push_back(temp_ideal_worst);
            index_ideal_best.push_back(temp_index_ideal_best);
            index_ideal_worst.push_back(temp_index_ideal_worst);
        }
        
        if (fronts.size() != 2) {
            for (int individual = 0 ; individual < fronts.size(); individual++) {
                double temp_best_summation = 0.0;
                double temp_worst_summation = 0.0;
                for (int objective = 0 ; objective < number_of_objectives ; objective++) {
                    temp_best_summation += pow(p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(objective)-ideal_best.at(objective), 2);
                    temp_worst_summation += pow(p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(objective)-ideal_worst.at(objective), 2);
                }
                if (temp_best_summation == 0) {
                    temp_best_summation = 0.00001;
                }
                if (temp_worst_summation == 0) {
                    temp_worst_summation = 0.00001;
                }
                
                if (temp_best_summation < 0) {
                    p_ind_population->at(fronts.at(individual)).euclidean_best = sqrt(-temp_best_summation);
                }else{
                    p_ind_population->at(fronts.at(individual)).euclidean_best = sqrt(temp_best_summation);
                }
                
                if (temp_worst_summation < 0) {
                    p_ind_population->at(fronts.at(individual)).eculidean_worst = sqrt(-temp_worst_summation);
                }else{
                    p_ind_population->at(fronts.at(individual)).eculidean_worst = sqrt(temp_worst_summation);
                }
                //p_ind_population->at(fronts.at(0).at(individual)).euclidean_best = sqrt(temp_best_summation);
                //p_ind_population->at(fronts.at(0).at(individual)).eculidean_worst = sqrt(temp_worst_summation);
                p_ind_population->at(fronts.at(individual)).performance_score = p_ind_population->at(fronts.at(individual)).eculidean_worst/(p_ind_population->at(fronts.at(individual)).eculidean_worst+p_ind_population->at(fronts.at(individual)).euclidean_best);
            }
            
            for (int individual = 0 ; individual < fronts.size(); individual++) {
                if (best_value > p_ind_population->at(fronts.at(individual)).performance_score) {
                    best_value = p_ind_population->at(fronts.at(individual)).performance_score;
                    best_index = individual;
                }
            }
            if (best_index == 999999) {
                cout<<"Work here"<<endl;
            }
            
        }else{
            
            for (int individual = 0; individual < fronts.size(); individual++) {
                p_ind_population->at(fronts.at(individual)).summation_fitness_value = 0.0;
                for (int fit = 0; fit < p_ind_population->at(fronts.at(individual)).normalized_fitness_values.size(); fit++) {
                    p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(fit) = (p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(fit) * degree_of_diversification.at(fit));
                    p_ind_population->at(fronts.at(individual)).summation_fitness_value += p_ind_population->at(fronts.at(individual)).normalized_fitness_values.at(fit);
                }
            }
            if (p_ind_population->at(fronts.at(0)).summation_fitness_value < p_ind_population->at(fronts.at(1)).summation_fitness_value) {
                best_index = 0;
            }else{
                best_index = 1;
            }
            
        }
        
    }else{
        best_index = fronts.at(0);
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
    
//    for (int temp_fit = 0 ; temp_fit < temp_distance.size(); temp_fit++) {
//        for (int individual = 0; individual< fronts.size() ; individual++) {
//            if ((temp_distance.at(temp_fit) == p_ind_population->at(fronts.at(individual)).distance_to_hall_of_fame) && (!p_ind_population->at(fronts.at(individual)).good_for_next_generation)){
//                p_ind_population->at(fronts.at(individual)).good_for_next_generation = true;
//                break;
//            }
//        }
//    }
//    
//    for (int individual = 0 ; individual < fronts.size(); individual++) {
//        if (!p_ind_population->at(fronts.at(individual)).good_for_next_generation) {
//            p_ind_population->at(fronts.at(individual)).remove_me = true;
//        }
//    }
    
    
    
    
    
    for (int individual = 0; individual < p_ind_population->size(); individual++) {
        if (p_ind_population->at(individual).remove_me) {
            p_ind_population->erase(p_ind_population->begin()+individual);
            individual = -1;
        }
    }
    //cout<<teams->at(team_number).teamRover.at(rover).new_network.size()<<endl;
    //cout<<p_ind_population->size()<<endl;
    assert(p_ind_population->size() == (number_of_individuals/2));
        
}
