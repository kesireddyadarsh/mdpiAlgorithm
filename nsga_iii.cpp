//
//  nsga_iii.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/6/24.
//

#include "nsga_iii.hpp"



// Function to generate reference points (simplified for 2D case)
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

// Function to calculate perpendicular distance (simplified)
double calculatePerpendicularDistance(const individual_element& individual, const ReferencePoint& rp) {
    
    double distance = 0.0;
    
    // Assuming individual.fitness_value and rp.position are normalized and have the same dimensions
    for (size_t i = 0; i < individual.fitness_value.size(); ++i) {
        distance += pow(individual.fitness_value[i] - rp.position[i], 2);
    }
    
    return sqrt(distance);
}

// Main function to associate individuals with reference points and calculate distances
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
        
        // Here, you would store the minDistance and/or the closestReferencePointIndex with the individual
        // For example:
        individual.reference_line = closestReferencePointIndex; // Assign reference point index
        individual.ranking_value = minDistance; // Store distance (or however you wish to use it)
    }
}

void markForRemovalUsingNiching(vector<individual_element>* population, vector<int> fronts, int front_number, int num_to_remove) {
    map<int, vector<int>> refPointToIndividualsMap;

    // Step 1: Associate individuals with reference points
    for (int i = 0; i<fronts.size(); i++) {
        int refPointIndex = (*population)[fronts.at(i)].reference_line;
        refPointToIndividualsMap[refPointIndex].push_back(fronts.at(i));
    }

    // Step 2: For each reference point, sort associated individuals by their distance (or other criteria)
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
                    // Mark the least preferable individual (farthest from reference point) for removal
                    int individualIndex = individuals.back();
                    (*population)[individualIndex].remove_me = true;
                    individuals.pop_back(); // Remove from this list as it's now marked for removal
                    removed++;
                    removedThisRound = true;
                }
            }

            // If no individuals were removed in this iteration, break to avoid infinite loop
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
    
    for (int individual  = 0; individual < p_ind_population->size(); individual++) {
        if (p_ind_population->at(individual).front_number > work_on_this.at(0).at(2)) {
            p_ind_population->at(individual).remove_me = true;
        }
    }
    
    // Remove marked individuals in reverse order to avoid indexing issues
    for (int individual = p_ind_population->size() - 1; individual >= 0; --individual) {
        if (p_ind_population->at(individual).remove_me) {
            p_ind_population->erase(p_ind_population->begin() + individual);
        }
    }
    
    // Assert to ensure the expected number of individuals are removed
    assert(p_ind_population->size() == (number_of_individuals/2));

    
}
