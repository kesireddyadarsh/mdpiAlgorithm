//
//  CommonMethods.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/2/24.
//

#include "CommonMethods.hpp"

extern const double PRECISION;
extern const bool negative_value_accepted;

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return (fMin + (f * (fMax - fMin)));
}

// Function to convert a real number to a binary string
string realToBinaryString(double realNumber, int precision) {
    // Convert the double to a binary representation
    bitset<64> binary(*reinterpret_cast<unsigned long long*>(&realNumber));
    
    // Get the binary string as a substring of the desired precision
    std::string binaryString = binary.to_string();
    size_t decimalPosition = binaryString.find('.');
    if (decimalPosition != std::string::npos) {
        size_t fractionalBits = binaryString.size() - decimalPosition - 1;
        size_t fractionalPrecision = std::min(static_cast<size_t>(precision), fractionalBits);
        binaryString = binaryString.substr(0, decimalPosition + 1 + fractionalPrecision);
    }
    
    return binaryString;
}

// Function to convert a binary string to a real number
double binaryStringToReal(const std::string& binaryString) {
    // Parse the binary string into a bitset
    std::bitset<64> binary(binaryString);
    
    // Get the unsigned long long value of the bitset and reinterpret it as a double
    unsigned long long binaryValue = binary.to_ullong();
    double realNumber = *reinterpret_cast<double*>(&binaryValue);
    
    return realNumber;
}


void cal_normalized_fitness_values(vector<individual_element>* p_ind_population, int number_of_objectives){
    for (int objectives = 0; objectives < number_of_objectives; objectives++) {
        double highest_value = -9999999.999;
        double lowest_value = 99999999.999;
        for (int individual = 0 ; individual < p_ind_population->size(); individual++) {
            if (highest_value < p_ind_population->at(individual).fitnes_value.at(objectives)) {
                highest_value = p_ind_population->at(individual).fitnes_value.at(objectives);
            }
            if (lowest_value > p_ind_population->at(individual).fitnes_value.at(objectives)) {
                lowest_value = p_ind_population->at(individual).fitnes_value.at(objectives);
            }
        }
        
        if (lowest_value == highest_value) {
            cout<<"Both are same"<<endl;
        }
        
        for (int individual = 0; individual < p_ind_population->size(); individual++) {
            p_ind_population->at(individual).overall_normalized_fitness_values.push_back((p_ind_population->at(individual).fitnes_value.at(objectives) - lowest_value)/(lowest_value+highest_value));
        }
    }
    
    
}

// Function to generate five unique random numbers from a Gaussian distribution
vector<double> generateUniqueRandomNumbers(double mean, double std_dev, int count) {
    random_device rd;// Create a random device to seed the random number generator
    mt19937 gen(rd());// Create a random number generator using the Mersenne Twister algorithm
    normal_distribution<double> distribution(mean, std_dev);// Create a Gaussian distribution with the specified mean and standard deviation
    vector<double> uniqueNumbers;// Use a set to ensure uniqueness
    
    // Generate unique random numbers
    while (uniqueNumbers.size() < static_cast<std::size_t>(count)) {
        double randomNumber = distribution(gen);
        if (find(uniqueNumbers.begin(), uniqueNumbers.end(), randomNumber) == uniqueNumbers.end()) {
            uniqueNumbers.push_back((int)(randomNumber * PRECISION)/PRECISION);
        }
    }
    
    return uniqueNumbers;
}

void mutate(vector<individual_element>* p_ind_population,int individual,bool negative_value_accepted){
    
    bool representation_flag = true;
    
    if (representation_flag) {
        double mean = 0.0;
        double mutation_rate = 0.25;
        vector<double> randomNumbersMutation;
        randomNumbersMutation = generateUniqueRandomNumbers(mean, mutation_rate, p_ind_population->at(individual).all_x.size());
        for (int mutationNumber = 0 ; mutationNumber < p_ind_population->at(individual).all_x.size(); mutationNumber++) {
            p_ind_population->at(individual).all_x.at(mutationNumber) += randomNumbersMutation.at(mutationNumber);
        }
    }else{
        int mutation_probability = 32;
        for (int number = 0 ; number < p_ind_population->at(individual).all_x_binary.size(); number++) {
            for (int mutation_rate = 0 ; mutation_rate < mutation_probability; mutation_rate++) {
                int value_to_change = rand()%p_ind_population->at(individual).all_x_binary.at(number).size();
                if (p_ind_population->at(individual).all_x_binary.at(number).at(value_to_change) == '1') {
                    p_ind_population->at(individual).all_x_binary.at(number).replace(value_to_change, 1, "0");
                }else{
                    p_ind_population->at(individual).all_x_binary.at(number).replace(value_to_change, 1, "1");
                }
                
            }
        }
        
        p_ind_population->at(individual).all_x.clear();
        
        for (int number = 0; number < p_ind_population->at(individual).all_x_binary.size(); number++) {
            p_ind_population->at(individual).all_x.push_back( binaryStringToReal( p_ind_population->at(individual).all_x_binary.at(number) ) );
        }
    }
}


bool compare_two_index(vector<individual_element>* p_ind_population,int first_individual ,int second_individual){
    
    bool strictlyBetterInOneObjective = false;
    for (size_t objective = 0; objective < p_ind_population->at(first_individual).fitnes_value.size(); objective++) {
        if (p_ind_population->at(first_individual).fitnes_value.at(objective) < p_ind_population->at(second_individual).fitnes_value.at(objective)) {
            strictlyBetterInOneObjective = true;
        }else if(p_ind_population->at(first_individual).fitnes_value.at(objective) > p_ind_population->at(second_individual).fitnes_value.at(objective)){
            return false;
        }
    }
    
    return strictlyBetterInOneObjective;
    
}

void assign_front_number(vector<individual_element>* p_ind_population){
    //pushes all the dominating values
    vector<int> all_sizes;
    vector<vector <int> > fronts;
    
    //First create fronts
    int number_of_neurals = p_ind_population->size();
    for (int indivdual = 0 ; indivdual < p_ind_population->size(); indivdual++) {
        p_ind_population->at(indivdual).getting_dominated_by = 0;
        p_ind_population->at(indivdual).front_number = -9999;
        p_ind_population->at(indivdual).in_front = false;
        p_ind_population->at(indivdual).remove_me = false;
        p_ind_population->at(indivdual).crowding_distance = 0;
        for (int other_individual = 0 ; other_individual < p_ind_population->size(); other_individual++) {
            if(compare_two_index(p_ind_population,indivdual,other_individual)){
                p_ind_population->at(indivdual).dominating_them.push_back(other_individual);
            }else if (compare_two_index(p_ind_population,other_individual,indivdual)){
                p_ind_population->at(indivdual).getting_dominated_by++;
            }
        }
        
        if (p_ind_population->at(indivdual).getting_dominated_by == 0) {
            all_sizes.push_back(indivdual);
            p_ind_population->at(indivdual).in_front = true;
            p_ind_population->at(indivdual).front_number = 0;
        }
    }
    int totalAccounted = 0;
    if (all_sizes.size()!=0) {
        fronts.push_back(all_sizes);
        totalAccounted = all_sizes.size();
    }
    bool loop_breaking_flag = true;
    if (totalAccounted == p_ind_population->size()) {
        loop_breaking_flag = false;
    }
    while (loop_breaking_flag) {
        all_sizes.clear();
        for (int individual = 0; individual < p_ind_population->size(); individual++) {
            if (!p_ind_population->at(individual).in_front) {
                p_ind_population->at(individual).getting_dominated_by = 0;
                p_ind_population->at(individual).front_number = -9999;
                p_ind_population->at(individual).in_front = false;
                p_ind_population->at(individual).remove_me = false;
                p_ind_population->at(individual).crowding_distance = 0;
                p_ind_population->at(individual).dominating_them.clear();
                
                for (int other_individual = 0 ; other_individual < p_ind_population->size(); other_individual++) {
                    if (!p_ind_population->at(other_individual).in_front && other_individual != individual) {
                        if(compare_two_index(p_ind_population,individual,other_individual)){
                            p_ind_population->at(individual).dominating_them.push_back(other_individual);
                        }else if (compare_two_index(p_ind_population,other_individual,individual)){
                            p_ind_population->at(individual).getting_dominated_by++;
                        }
                    }
                }
                
                if (p_ind_population->at(individual).getting_dominated_by == 0) {
                    all_sizes.push_back(individual);
                    p_ind_population->at(individual).in_front = true;
                    p_ind_population->at(individual).front_number = fronts.size();
                    totalAccounted++;
                }
            }
        }
        
        fronts.push_back(all_sizes);
        all_sizes.clear();
        if (totalAccounted == p_ind_population->size()) {
            loop_breaking_flag = false;
        }
    }
    
    for (int index = 0 ; index < p_ind_population->size(); index++) {
        assert(p_ind_population->at(index).front_number != -9999);
        assert(p_ind_population->at(index).in_front);
    }
    
}
