//
//  printToFile.hpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/4/24.
//

#ifndef printToFile_hpp
#define printToFile_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <vector>

#include "population.hpp"
#include "individual_element.hpp"
#include "TestScenario.hpp"
#include "CommonMethods.hpp"

void printValues(population pop,int simulation_run, int generation, int case_number, int case_to_study);

#endif /* printToFile_hpp */
