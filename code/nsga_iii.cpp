//
//  nsga_iii.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/6/24.
//

#include "nsga_iii.hpp"



vector<ReferencePoint> generateReferencePoints(int divisions, int objectives) {
    vector<ReferencePoint> referencePoints;
    double step = 1.0 / divisions;
    
    for (int i = 0; i <= divisions; i++) {
        ReferencePoint rp;
        rp.position = {step * i, 1 - step * i};
        referencePoints.push_back(rp);
    }
    
    return referencePoints;
}

double calculatePerpendicularDistance(const individual_element& individual, const ReferencePoint& rp) {
    
    double distance = 0.0;
    
    // Assuming individual.fitness_value and rp.position are normalized and have the same dimensions
    for (size_t i = 0; i < individual.fitness_value.size(); ++i) {
        distance += pow(individual.fitness_value[i] - rp.position[i], 2);
    }
    
    return sqrt(distance);
}

void associateAndCalculateDistances(vector<individual_element>* p_ind_population, const vector<ReferencePoint>& referencePoints) {
    
    for (auto& individual : *p_ind_population) {
        double minDistance = numeric_limits<double>::max();
        int closestReferencePointIndex = -1;
        
        for (size_t i = 0; i < referencePoints.size(); ++i) {
            double distance = calculatePerpendicularDistance(individual, referencePoints[i]);
            if (distance < minDistance) {
                minDistance = distance;
                closestReferencePointIndex = i;
            }
        }
        
        
        individual.reference_line = closestReferencePointIndex; 
        individual.ranking_value = minDistance;
    }
}

void markForRemovalUsingNiching(vector<individual_element>* population, vector<int> fronts, int front_number, int num_to_remove) {
    map<int, vector<int>> refPointToIndividualsMap;

    for (int i = 0; i<fronts.size(); i++) {
        int refPointIndex = (*population)[fronts.at(i)].reference_line;
        refPointToIndividualsMap[refPointIndex].push_back(fronts.at(i));
    }

    for (auto& [refPointIndex, individuals]: refPointToIndividualsMap) {
        sort(individuals.begin(), individuals.end(), [&](int a, int b) {
            return (*population)[a].ranking_value > (*population)[b].ranking_value;
        });
    }
    
    int removed = 0;
        while (removed < num_to_remove) {
            bool removedThisRound = false;

            for (auto& [refPointIndex, individuals] : refPointToIndividualsMap) {
                if (!individuals.empty() && removed < num_to_remove) {
                    int individualIndex = individuals.back();
                    (*population)[individualIndex].remove_me = true;
                    individuals.pop_back(); // Remove from this list as it's now marked for removal
                    removed++;
                    removedThisRound = true;
                }
            }

            if (!removedThisRound) {
                break;
            }
        }
    
}

void nsga_iii(vector<individual_element>* p_ind_population,int number_of_objectives, int generation_number, bool negative_value_accepted, vector<vector<int>> work_on_this){
    
    int number_of_individuals = p_ind_population->size();
    int front_number_to_select = work_on_this.at(0).at(2);
    vector<int> fronts;
    for (int individual = 0 ; individual < work_on_this.at(1).size(); individual++) {
        fronts.push_back(work_on_this.at(1).at(individual));
    }
    
    int divisions = 4; // Example divisions along each objective axis
    int objectives = number_of_objectives; // Number of objectives
    
    vector<ReferencePoint> referencePoints = generateReferencePoints(divisions, objectives);
    associateAndCalculateDistances(p_ind_population, referencePoints);
    
    int num_to_remove = -work_on_this.at(0).at(1); // Number of individuals to mark for removal
    markForRemovalUsingNiching(p_ind_population, fronts, front_number_to_select, num_to_remove);
    
    select_remove_individuals(p_ind_population,  work_on_this.at(0).at(2));

    
}
