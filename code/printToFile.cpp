//
//  printToFile.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/4/24.
//

#include "printToFile.hpp"

void printValues(population pop,int simulation_run, int generation, int case_number,int case_to_study){
    char buf[1024]; // Ensure this buffer is large enough for your path
    const char* directory;

    if (case_to_study == 4) {
        directory = "empf";
    } else if (case_to_study == 3) {
        directory = "mpf";
    } else if (case_to_study == 1) {
        directory = "nsgaii";
    } else {
        directory = "nsgaiii"; // Default or any other case_number
    }

    
    try {
        ofstream reward_file;
        char buf_2[0x100];
        
        snprintf(buf_2, sizeof(buf_2), "/Users/adarshkesireddy/Downloads/Simulation_1/Case_%d/%d/%s/rewards_%d.txt",case_number, simulation_run, directory, generation);
//        snprintf(buf_2, sizeof(buf_2), "/Users/adarshkesireddy/Downloads/Analysis/rewards_%d.txt",generation);
//          snprintf(buf_2, sizeof(buf_2), "/Users/adarshkesireddy/Downloads/sample_simulation/rewards_%d.txt", generation);
//          snprintf(buf_2, sizeof(buf_2), "/home/akesireddy/Downloads/sample_simulation/rewards_%d.txt", generation);
//       snprintf(buf_2, sizeof(buf_2), "C:\\Users\\akesireddy\\Downloads\\Data_points\\rewards_%d.txt", generation);
        reward_file.open(buf_2);
        reward_file.exceptions(std::ifstream::failbit);
        for (int team_number = 0 ; team_number < pop.ind_population.size(); team_number++) {
            for (int si = 0 ; si < pop.ind_population.at(team_number).fitness_value.size(); si++) {
                reward_file<<pop.ind_population.at(team_number).fitness_value.at(si)<<"\t";
            }
            reward_file<<"\n";
        }
        reward_file.close();
    }
    catch (std::ios_base::failure& fail) {
        ofstream error_file;
        error_file.open("error.txt");
        error_file<<fail.what()<<"\n";
        error_file.close();
        cout<<fail.what()<<endl;
        //exit(1);
    }

    try {
        ofstream numbers_file;
        char buf_3[0x100];
//        snprintf(buf_3, sizeof(buf_3), "/Users/adarshkesireddy/Downloads/Analysis/numbers_%d.txt",generation);
        snprintf(buf_3, sizeof(buf_3), "/Users/adarshkesireddy/Downloads/Simulation_1/Case_%d/%d/%s/numbers_%d.txt",case_number, simulation_run, directory, generation);
//          snprintf(buf, sizeof(buf), "/Users/adarshkesireddy/Downloads/sample_simulation/numbers_%d.txt", generation);
//       snprintf(buf, sizeof(buf), "C:\\Users\\akesireddy\\Downloads\\Data_points\\numbers_%d.txt", generation);
        numbers_file.open(buf_3);
        numbers_file.exceptions(std::ifstream::failbit);
        for (int team_number = 0 ; team_number < pop.ind_population.size(); team_number++) {
            for(int x_value=0; x_value<(pop.ind_population.at(team_number).all_x.size()); x_value++){
                numbers_file<<pop.ind_population.at(team_number).all_x.at(x_value)<<"\t";
            }
            numbers_file<<"\n";
        }
        numbers_file.close();
    }
    catch (std::ios_base::failure& fail) {
        ofstream error_file;
        error_file.open("error.txt");
        error_file<<fail.what()<<"\n";
        error_file.close();
        cout<<fail.what()<<endl;
        //exit(1);
    }
    
}
