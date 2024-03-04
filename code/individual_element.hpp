//
//  individual_element.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/2/24.
//

#ifndef individual_element_hpp
#define individual_element_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class individual_element{
public:
    vector<double> all_x;
    vector<bool> all_x_sign_value;
    bool negative_values_accepted;
    int number_i;
    vector<string> all_x_binary;
    vector<double> fitness_value;
    vector<double> normalized_fitness_values;  //This is used for topsis
    vector<double> normalized_fitness_values_entropy; // This is used for entropy
    vector<double> overall_normalized_fitness_values; // This is used for overall
    int getting_dominated_by;
    int front_number;
    bool in_front;
    bool remove_me;
    double crowding_distance;
    vector<int> dominating_them;
    double summation_fitness_value;
    int rank;
    bool hall_of_fame;
    double distance_to_hall_of_fame;
    bool good_for_next_generation;
    double euclidean_best;
    double eculidean_worst;
    double performance_score;
    int reference_line;
    double ranking_value;
};


#endif /* individual_element_hpp */
