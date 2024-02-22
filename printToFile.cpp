//
//  printToFile.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/4/24.
//

#include "printToFile.hpp"

void printValues(population pop,int generation){
    try {
        ofstream reward_file;
        char buf_2[0x100];
//          snprintf(buf_2, sizeof(buf_2), "/Users/adarshkesireddy/Downloads/Simulation_1/Case_0/0/empf/rewards_%d.txt", generation);
          snprintf(buf_2, sizeof(buf_2), "/Users/adarshkesireddy/Downloads/sample_simulation/rewards_%d.txt", generation);
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
        char buf[0x100];
//          snprintf(buf, sizeof(buf), "/Users/adarshkesireddy/Downloads/Data/Case_14/nsgaii/numbers_%d.txt", generation);
          snprintf(buf, sizeof(buf), "/Users/adarshkesireddy/Downloads/sample_simulation/numbers_%d.txt", generation);
//       snprintf(buf, sizeof(buf), "C:\\Users\\akesireddy\\Downloads\\Data_points\\numbers_%d.txt", generation);
        numbers_file.open(buf);
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
