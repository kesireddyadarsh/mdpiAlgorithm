//
//  TestScenario.cpp
//  codeAlgorithm
//
//  Created by adarsh kesireddy on 2/2/24.
//

#include "TestScenario.hpp"

extern const double PRECISION;
extern const bool negative_value_accepted;
const int search_area_case_5 = 10;

vector<double> limitation_values(int case_number){
    vector<double> finial_values;
    double temp_x,temp_y;
    
    switch (case_number) {
        case 0:{
            temp_x = fRand(0, 5);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            temp_y = fRand(0, 3);
            temp_y = (int)(temp_y * PRECISION)/PRECISION;
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            
            while (!check_constrains_vec(x_value, case_number)) {
                temp_x = fRand(0, 5);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                temp_y = fRand(0, 3);
                temp_y = (int)(temp_y * PRECISION)/PRECISION;
                x_value.at(0) = temp_x;
                x_value.at(1) = temp_y;
            }
            
            return x_value;
            break;
        }
            
        case 1:{
            temp_x = fRand(-20, 100);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            temp_y = fRand(-100, 20);
            temp_y = (int)(temp_y * PRECISION)/PRECISION;
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            
            while (!check_constrains_vec(x_value,case_number)) {
                temp_x = fRand(-20, 100);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                temp_y = fRand(-100, 20);
                temp_y = (int)(temp_y * PRECISION)/PRECISION;
                x_value.at(0) = temp_x;
                x_value.at(1) = temp_y;
            }
            
            return x_value;
            break;
        }
            
        case 2:{
            int n_value = 2;
            vector<double> values_x;
            for(int i=0;i<n_value;i++){
                temp_x = fRand(-4, 4);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                values_x.push_back(temp_x);
            }
            return values_x;
            break;
        }
            
        case 3:{
            temp_x = fRand(-7, 10);
            temp_y = fRand(-10, 4);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            temp_y = (int)(temp_y * PRECISION)/PRECISION;
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            
            while (!check_constrains_vec(x_value,case_number)) {
                temp_x = fRand(-7, 100);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                temp_y = fRand(-10, 4);
                temp_y = (int)(temp_y * PRECISION)/PRECISION;
                x_value.at(0) = temp_x;
                x_value.at(1) = temp_y;
            }
            
            return x_value;
            break;
        }
            
        case 4:{
            int i_value = 3;
            
            vector<double> x_values;
            for(int temp_var = 1; temp_var <= i_value; temp_var++){
                temp_x = fRand(-5, 5);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                x_values.push_back(temp_x);
            }
            
            return x_values;
            break;
        }
            
        case 5:{
            
            temp_x = fRand(-search_area_case_5, search_area_case_5);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            temp_y = fRand(1, 2);//No use of this value
            
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            
            while (!check_constrains_vec(x_value,case_number)) {
                temp_x = fRand(-search_area_case_5, search_area_case_5);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                x_value.at(0) = temp_x;
                x_value.at(1) = temp_y;
            }
            
            return x_value;
            break;
        }
            
        case 6:{
            temp_x = fRand(-5, 10);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            vector<double> x_value;
            x_value.push_back(temp_x);
            
            return x_value;
            
            break;
        }
            
        case 7:{
            temp_x = fRand(-3.14, 3.14);
            temp_y = fRand(-3.14, 3.14);
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            break;
        }
            
        case 8:{
            int i_value = 30;
            
            vector<double> x_values;
            for(int temp_value = 0;temp_value < i_value;temp_value++){
                temp_x = fRand(0, 1);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                x_values.push_back(temp_x);
            }
            return x_values;
            
            break;
        }
            
        case 9:{
            int i_value = 30;
            
            vector<double> x_values;
            for(int temp_value = 0; temp_value < i_value;temp_value++){
                temp_x = fRand(0, 1);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                x_values.push_back(temp_x);
            }
            return x_values;
            
            break;
        }
            
        case 10:{
            int i_value = 30;
            
            vector<double> x_values;
            for(int temp_value = 0; temp_value < i_value;temp_value++){
                temp_x = fRand(0, 1);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                x_values.push_back(temp_x);
            }
            
            return x_values;
            
            break;
        }
            
        case 11:{
            vector<double> x_values;
            temp_x = fRand(0, 1);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            x_values.push_back(temp_x);
            int i_value = 10;
            for(int temp_Value=1;temp_Value<=i_value;temp_Value++){
                temp_x = fRand(-5, 5);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                x_values.push_back(temp_x);
            }
            return x_values;
            break;
        }
            
        case 12:{
            int i_value = 10;
            
            vector<double> x_values;
            for(int temp_value=1;temp_value<=i_value;temp_value++){
                temp_x = fRand(0, 1);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                x_values.push_back(temp_x);
            }
            return x_values;
            break;
        }
            
        case 13:{
            vector<double> temp_x_values;
            double temp_1 = fRand(0, 10);
            double temp_2 = fRand(0, 10);
            double temp_6 = fRand(0, 10);
            double temp_3 = fRand(1, 5);
            double temp_5 = fRand(1, 5);
            double temp_4 = fRand(0, 6);
            temp_1 = (int)(temp_1 * PRECISION)/PRECISION;
            temp_2 = (int)(temp_2 * PRECISION)/PRECISION;
            temp_3 = (int)(temp_3 * PRECISION)/PRECISION;
            temp_4 = (int)(temp_4 * PRECISION)/PRECISION;
            temp_5 = (int)(temp_5 * PRECISION)/PRECISION;
            temp_6 = (int)(temp_6 * PRECISION)/PRECISION;
            temp_x_values.push_back(temp_1);
            temp_x_values.push_back(temp_2);
            temp_x_values.push_back(temp_3);
            temp_x_values.push_back(temp_4);
            temp_x_values.push_back(temp_5);
            temp_x_values.push_back(temp_6);
            
            
            while (!check_constrains_vec(temp_x_values, case_number)) {
                temp_x_values.clear();
                temp_1 = fRand(0, 10);
                temp_2 = fRand(0, 10);
                temp_6 = fRand(0, 10);
                temp_3 = fRand(1, 5);
                temp_5 = fRand(1, 5);
                temp_4 = fRand(0, 6);
                temp_1 = (int)(temp_1 * PRECISION)/PRECISION;
                temp_2 = (int)(temp_2 * PRECISION)/PRECISION;
                temp_3 = (int)(temp_3 * PRECISION)/PRECISION;
                temp_4 = (int)(temp_4 * PRECISION)/PRECISION;
                temp_5 = (int)(temp_5 * PRECISION)/PRECISION;
                temp_6 = (int)(temp_6 * PRECISION)/PRECISION;
                temp_x_values.push_back(temp_1);
                temp_x_values.push_back(temp_2);
                temp_x_values.push_back(temp_3);
                temp_x_values.push_back(temp_4);
                temp_x_values.push_back(temp_5);
                temp_x_values.push_back(temp_6);
            }
            return temp_x_values;
            break;
        }
            
        case 14:{
            temp_x = fRand(0, 100);
            temp_y = fRand(-100, 1);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            temp_y = (int)(temp_y * PRECISION)/PRECISION;
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            
            while (!check_constrains_vec(x_value,case_number)) {
                temp_x = fRand(-4, 4);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                temp_y = fRand(1, 10);
                temp_y = (int)(temp_y * PRECISION)/PRECISION;
                x_value.at(0) = temp_x;
                x_value.at(1) = temp_y;
            }
            return x_value;
            break;
        }
            
        case 15:{
            temp_x = fRand(0.1, 1);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            temp_y = fRand(0, 5);
            temp_y = (int)(temp_y * PRECISION)/PRECISION;
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            
            while (!check_constrains_vec(x_value,case_number)) {
                temp_x = fRand(0.1, 1);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                temp_y = fRand(0, 5);
                temp_y = (int)(temp_y * PRECISION)/PRECISION;
                x_value.at(0) = temp_x;
                x_value.at(1) = temp_y;
            }
            
            return x_value;
            break;
        }
            
        case 16:{
            
            temp_x = fRand(-3, 100);
            temp_x = (int)(temp_x * PRECISION)/PRECISION;
            temp_y = fRand(-100, 3);
            temp_y = (int)(temp_y * PRECISION)/PRECISION;
            vector<double> x_value;
            x_value.push_back(temp_x);
            x_value.push_back(temp_y);
            
            while (!check_constrains_vec(x_value,case_number)) {
                temp_x = fRand(-3, 100);
                temp_x = (int)(temp_x * PRECISION)/PRECISION;
                temp_y = fRand(-100, 3);
                temp_y = (int)(temp_y * PRECISION)/PRECISION;
                x_value.at(0) = temp_x;
                x_value.at(1) = temp_y;
            }
            
            return x_value;
            break;
        }
            
        default:
            exit(1);
            break;
    }
    
    finial_values.push_back(temp_x);
    finial_values.push_back(temp_y);
    
    return finial_values;
}

bool check_constrains_vec(vector<double> x_value_vec, int case_number){
    if (x_value_vec.size() == 0) {
        return false;
    }
    
    for (int  i = 0; i < x_value_vec.size(); i++) {
        if (isnan(x_value_vec.at(i)))
            return false;
    }
    
    
    switch (case_number) {
            
        case 0:
        {
            if (x_value_vec.at(0) < 0 || x_value_vec.at(0) > 5) {
                return false;
            }
            if (x_value_vec.at(1) < 0 || x_value_vec.at(1) > 3) {
                return false;
            }
            double check_x_1 = ((x_value_vec.at(0)-5)*(x_value_vec.at(0)-5));
            double check_y_1 = x_value_vec.at(1)*x_value_vec.at(1);
            
            double check_x_2 = ((x_value_vec.at(0)-8)*(x_value_vec.at(1)-8));
            double check_y_2 = ((x_value_vec.at(1)+3)*(x_value_vec.at(1)+3));
            
            if ((check_x_1+check_y_1)>25) {
                return false;
            }
            if ((check_x_2+check_y_2)<7.7) {
                return false;
            }
            break;
        }
            
        case 1:
        {
            if ( x_value_vec.at(0) < -20) {
                return false;
            }
            if (x_value_vec.at(1) > 20) {
                return false;
            }
            if (((x_value_vec.at(0)*x_value_vec.at(0))+(x_value_vec.at(1)*x_value_vec.at(1)))>225) {
                return false;
            }
            if ((x_value_vec.at(0)-(3*x_value_vec.at(1))+10)>0) {
                return false;
            }
            break;
        }
        
        case 2:
        {
            for (int index = 0 ; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index) < -4 || x_value_vec.at(index) > 4) {
                    return false;
                }

            }
            break;
        }
            
        case 3:
        {
            
            if ((6.5 - (x_value_vec.at(0)/6) - x_value_vec.at(1)) < 0) {
                return false;
            }
            if ((7.5 - (0.5*x_value_vec.at(0)) - x_value_vec.at(1)) < 0) {
                return false;
            }
            if ((30 - (5*x_value_vec.at(0)) - x_value_vec.at(1)) < 0) {
                return false;
            }
            break;
        }
            
        case 4:
        {
            for (int index = 0; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index)<0 && x_value_vec.at(index)<-5) {
                    return false;
                }
                if (x_value_vec.at(index)>5) {
                    return false;
                }
            }
            break;
        }
        case 5:
        {
            if (x_value_vec.at(0) > search_area_case_5 || x_value_vec.at(0) < -search_area_case_5) {
                return false;
            }
            break;
        }
            
        case 6:
        {
            if (x_value_vec.at(0) > 10 || x_value_vec.at(0) < -5) {
                return false;
            }

            break;
        }
        
        case 7:
        {
            for (int index = 0; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index) > 3.14 || x_value_vec.at(index) < -3.14) {
                    return false;
                }
            }

            break;
        }
            
        case 8:
        {
            for (int index = 0 ; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index) < 0 || x_value_vec.at(index) > 1) {
                    return false;
                }
            }
            break;
        }
            
        case 9:
        {
            for (int index = 0 ; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index) < 0 || x_value_vec.at(index) > 1) {
                    return false;
                }
            }
            break;
        }
            
        case 10:
        {
            for (int index = 0 ; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index) < 0 || x_value_vec.at(index) > 1) {
                    return false;
                }
            }
            break;
        }
            
        case 11:
        {
            if (x_value_vec.at(0) < 0 ||x_value_vec.at(0) > 1) {
                return false;
            }
            
            for (int index = 1 ; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index) > 5 || x_value_vec.at(index) < -5 ) {
                    return false;
                }
            }
            
            break;
        }
            
        case 12:
        {
            for (int index = 0 ; index < x_value_vec.size(); index++) {
                if (x_value_vec.at(index) < 0 || x_value_vec.at(index) > 1) {
                    return false;
                }
            }
            break;
        }
            
        case 13:
        {
            if (x_value_vec.at(0) > 10 || x_value_vec.at(0) < 0) {
                return false;
            }
            if (x_value_vec.at(1) > 10 || x_value_vec.at(1) < 0) {
                return false;
            }
            if (x_value_vec.at(5) > 10 || x_value_vec.at(5) < 0) {
                return false;
            }
            
            if (x_value_vec.at(4) > 5 || x_value_vec.at(4) < 1) {
                return false;
            }
            if (x_value_vec.at(2) > 5 || x_value_vec.at(2) < 1) {
                return false;
            }
            
            if (x_value_vec.at(3) > 6 || x_value_vec.at(3) < 0) {
                return false;
            }
            
            if((x_value_vec.at(0) + x_value_vec.at(1) - 2)<0){
                return false;
            }
            if ((6 - x_value_vec.at(0) - x_value_vec.at(1)) < 0) {
                return false;
            }
            if ((2 - x_value_vec.at(1) + x_value_vec.at(0)) < 0) {
                return false;
            }
            if ((2 - x_value_vec.at(0) + (3*x_value_vec.at(1))) < 0) {
                return false;
            }
            if ((4 - pow(x_value_vec.at(2)-3, 2) - x_value_vec.at(3)) < 0) {
                return false;
            }
            if ((pow(x_value_vec.at(4) -3, 2) + x_value_vec.at(5) - 4) < 0) {
                return  false;
            }
            break;
        }
            
        case 14:
        {
            if (x_value_vec.at(0) < 0 ) {
                return false;
            }
            if (x_value_vec.at(1) > 1) {
                return false;
            }
            double temp = (x_value_vec.at(0)/(1+x_value_vec.at(1)));
            double temp_1 = (1+x_value_vec.at(1))*exp(-temp);
            double temp_2 = 0.858*exp(-0.541*x_value_vec.at(0));
            double temp_3 = 0.728*exp(-0.295*x_value_vec.at(0));
            if ((temp_1/temp_2) <1) {
                return false;
            }
            if ((temp_1/temp_3) <1) {
                return false;
            }
            
            break;
        }
            
        case 15:
        {
            if (x_value_vec.at(0) < 0.1 || x_value_vec.at(0) >1) {
                return false;
            }
            if (x_value_vec.at(1) < 0 || x_value_vec.at(1) > 5 ) {
                return false;
            }
            
            if (x_value_vec.at(1)+(9*x_value_vec.at(0))<6) {
                return false;
            }
            if (-x_value_vec.at(1)+(9*x_value_vec.at(0))<1) {
                return false;
            }
            
            break;
        }
           
        case 16:
        {
            if (x_value_vec.at(0) < -3) {
                return false;
            }
            
            if (x_value_vec.at(1) > 3) {
                return false;
            }
            break;
        }
        
            
        default:
            break;
    }
    return true;
}


void exe_function(vector<individual_element>* p_ind_population, int individual, int case_number){
    
    switch (case_number) {
        case 0:{
            p_ind_population->at(individual).fitness_value.push_back( (4 * p_ind_population->at(individual).all_x.at(0) * p_ind_population->at(individual).all_x.at(0)) + ( 4 * p_ind_population->at(individual).all_x.at(1) * p_ind_population->at(individual).all_x.at(1)) );
            p_ind_population->at(individual).fitness_value.push_back( ((p_ind_population->at(individual).all_x.at(0) - 5)* (p_ind_population->at(individual).all_x.at(0) - 5))  + ((p_ind_population->at(individual).all_x.at(1) - 5) *(p_ind_population->at(individual).all_x.at(1) - 5)));
            break;
        }
            
        case 1:{
            
            p_ind_population->at(individual).fitness_value.push_back( 2 + ((p_ind_population->at(individual).all_x.at(0) - 2) * (p_ind_population->at(individual).all_x.at(0) - 2)) + ((p_ind_population->at(individual).all_x.at(1) - 1) * (p_ind_population->at(individual).all_x.at(1) - 1)) );
            
            p_ind_population->at(individual).fitness_value.push_back((9*p_ind_population->at(individual).all_x.at(0)) - (((p_ind_population->at(individual).all_x.at(1) -1) * (p_ind_population->at(individual).all_x.at(1) -1))) );
            
            break;
        }
            
        case 2:{
            
            double summation_1 = 0.0;
            for(int i = 0; i < p_ind_population->at(individual).all_x.size(); i++){
                summation_1 += ((p_ind_population->at(individual).all_x.at(i) - (1/sqrt(p_ind_population->at(individual).all_x.size()))) * (p_ind_population->at(individual).all_x.at(i) - (1/sqrt(p_ind_population->at(individual).all_x.size()))));
            }
            
            double summation_2 = 0.0;
            for(int i = 0; i < p_ind_population->at(individual).all_x.size(); i++){
                summation_2 += ((p_ind_population->at(individual).all_x.at(i) + (1/sqrt(p_ind_population->at(individual).all_x.size()))) * (p_ind_population->at(individual).all_x.at(i) + (1/sqrt(p_ind_population->at(individual).all_x.size()))));
            }
            
            p_ind_population->at(individual).fitness_value.push_back(1-exp(-(summation_1)));
            p_ind_population->at(individual).fitness_value.push_back(1-exp(-(summation_2)));
            
            break;
        }
            
        case 3:{
            
            p_ind_population->at(individual).fitness_value.push_back( (p_ind_population->at(individual).all_x.at(0) * p_ind_population->at(individual).all_x.at(0)) - p_ind_population->at(individual).all_x.at(1) );
            
            p_ind_population->at(individual).fitness_value.push_back( (-0.5 * p_ind_population->at(individual).all_x.at(0)) - p_ind_population->at(individual).all_x.at(1) - 1);
            
            break;
        }
            
        case 4:{
            
            //This is first part
            
            double summation = 0.0;
            for(int temp = 0; temp < p_ind_population->at(individual).all_x.size() - 1; temp++){
                summation += -10 * exp( -0.2 * sqrt( pow( p_ind_population->at(individual).all_x.at(temp),2) + pow(p_ind_population->at(individual).all_x.at(temp+1),2) ) );
            }
            
            p_ind_population->at(individual).fitness_value.push_back(summation);
            
            //This is second part
            summation = 0.0;
            for(int temp_var = 0;temp_var < p_ind_population->at(individual).all_x.size(); temp_var++){
                summation += ( pow(abs(p_ind_population->at(individual).all_x.at(temp_var)),0.8) + (5 * (sin((pow((p_ind_population->at(individual).all_x.at(temp_var)),3)) *3.14159/180))));
            }
            
            p_ind_population->at(individual).fitness_value.push_back(summation);
            
            break;
        }
            
        case 5:{
            
            p_ind_population->at(individual).fitness_value.push_back( p_ind_population->at(individual).all_x.at(0) * p_ind_population->at(individual).all_x.at(0));
            
            p_ind_population->at(individual).fitness_value.push_back(pow((p_ind_population->at(individual).all_x.at(0) - 2), 2));
            break;
        }
            
        case 6:{
            
            if (p_ind_population->at(individual).all_x.at(0) <= 1)
            {
                p_ind_population->at(individual).fitness_value.push_back(-p_ind_population->at(individual).all_x.at(0));
            }
            else if ((1 < p_ind_population->at(individual).all_x.at(0))||(p_ind_population->at(individual).all_x.at(0) <= 3))
            {
                p_ind_population->at(individual).fitness_value.push_back(p_ind_population->at(individual).all_x.at(0) - 2);
            }
            else if ((3 < p_ind_population->at(individual).all_x.at(0))||(p_ind_population->at(individual).all_x.at(0) <= 4))
            {
                p_ind_population->at(individual).fitness_value.push_back(4 - p_ind_population->at(individual).all_x.at(0));
            }
            else if (p_ind_population->at(individual).all_x.at(0) > 4)
            {
                p_ind_population->at(individual).fitness_value.push_back(p_ind_population->at(individual).all_x.at(0) - 4);
            }
            
            p_ind_population->at(individual).fitness_value.push_back(pow((p_ind_population->at(individual).all_x.at(0) - 5), 2));
            
            break;
        }
            
        case 7:{
            double a_1 = ((0.5*sin(1)) - (2*cos(1)) + (sin(2)) - (1.5*cos(2)));
            double a_2 = ((1.5*sin(1)) - (cos(1)) + (2*sin(2)) - (0.5*cos(2)));
            double b_1 = ((0.5*sin(p_ind_population->at(individual).all_x.at(0))) - (2*cos(p_ind_population->at(individual).all_x.at(0))) + (sin(p_ind_population->at(individual).all_x.at(1))) - ( 1.5 *cos(p_ind_population->at(individual).all_x.at(1))));
            double b_2 = ((1.5*sin(p_ind_population->at(individual).all_x.at(0))) - (cos(p_ind_population->at(individual).all_x.at(0))) + (2*sin(p_ind_population->at(individual).all_x.at(1))) - (0.5*cos(p_ind_population->at(individual).all_x.at(1))));
            double f_1_x = 1+ pow(a_1-b_1,2)+ pow(a_2-b_2,2);
            double f_2_x = pow(p_ind_population->at(individual).all_x.at(0)+3,2)+pow(p_ind_population->at(individual).all_x.at(1)+1,2);
            p_ind_population->at(individual).fitness_value.push_back(f_1_x);
            p_ind_population->at(individual).fitness_value.push_back(f_2_x);
            break;
        }
            
        case 8:{
            double summation_g_x = 0;
            for (int i = 1; i <= p_ind_population->at(individual).all_x.size()-1; i++) {
                summation_g_x += (p_ind_population->at(individual).all_x.at(i));
            }
            summation_g_x = 1 + (9.0/(p_ind_population->at(individual).all_x.size()-1))*summation_g_x;
            double h_function = 1- sqrt(p_ind_population->at(individual).all_x.at(0)/summation_g_x);
            double f_2_x = summation_g_x*h_function;
            p_ind_population->at(individual).fitness_value.push_back(p_ind_population->at(individual).all_x.at(0));
            p_ind_population->at(individual).fitness_value.push_back(f_2_x);
            
            break;
        }
            
        case 9:{
            double summation_g_x = 0;
            for (int i = 1; i <= p_ind_population->at(individual).all_x.size()-1; i++) {
                summation_g_x += p_ind_population->at(individual).all_x.at(i);
            }
            summation_g_x = 1 +(9.0/(p_ind_population->at(individual).all_x.size() - 1))*summation_g_x;
            
            double h_function = 1- pow((p_ind_population->at(individual).all_x.at(0)/summation_g_x),2);
            
            double f_2_x = summation_g_x*h_function;
            p_ind_population->at(individual).fitness_value.push_back(p_ind_population->at(individual).all_x.at(0));
            p_ind_population->at(individual).fitness_value.push_back(f_2_x);
            break;
        }
            
        case 10:{
            double summation_g_x = 0;
            for (int i=1; i<p_ind_population->at(individual).all_x.size(); i++) {
                summation_g_x += p_ind_population->at(individual).all_x.at(i);
            }
            
            summation_g_x = 1 +(9.0/(p_ind_population->at(individual).all_x.size() - 1))*summation_g_x;
            
            p_ind_population->at(individual).fitness_value.push_back(p_ind_population->at(individual).all_x.at(0));
            double h_function = 1- sqrt(p_ind_population->at(individual).all_x.at(0)/summation_g_x) - ((p_ind_population->at(individual).all_x.at(0)/summation_g_x)*sin(10*PI*p_ind_population->at(individual).all_x.at(0)));
            double f_2_x = summation_g_x*h_function;
            p_ind_population->at(individual).fitness_value.push_back(f_2_x);
            break;
        }
            
        case 11:{
            
            double summation_g_x = 0;
            for (int i = 1; i < p_ind_population->at(individual).all_x.size(); i++) {
                summation_g_x += (pow(p_ind_population->at(individual).all_x.at(i), 2) - 10 * cos(4 * PI * p_ind_population->at(individual).all_x.at(i)));
            }
            // Correct initialization based on ZDT4 definition
            summation_g_x = 1 + 10 * (p_ind_population->at(individual).all_x.size() - 1) + summation_g_x;
            double f_1_x = p_ind_population->at(individual).all_x.at(0);
            double h_function = 1- sqrt(f_1_x/summation_g_x);
            double f_2_x = summation_g_x*h_function;
            p_ind_population->at(individual).fitness_value.push_back(f_1_x);
            p_ind_population->at(individual).fitness_value.push_back(f_2_x);
            break;
        }
            
        case 12:{
            double f_1_x = 1 - (exp(-4* p_ind_population->at(individual).all_x.at(0))) * (pow(sin(6*PI*p_ind_population->at(individual).all_x.at(0)),6));
            double summation_g_x = 0;
            for (int i=1; i< p_ind_population->at(individual).all_x.size(); i++) {
                summation_g_x += p_ind_population->at(individual).all_x.at(i);
            }
            summation_g_x = 1 + (9.0 *pow(summation_g_x/(p_ind_population->at(individual).all_x.size()-1),0.25));
            double h_function = 1- pow( f_1_x / summation_g_x,2);
            double f_2_x = summation_g_x*h_function;
            p_ind_population->at(individual).fitness_value.push_back(f_1_x);
            p_ind_population->at(individual).fitness_value.push_back(f_2_x);
            break;
        }
            
        case 13:{
            double temp_1 = -25*pow(p_ind_population->at(individual).all_x.at(0)-2, 2);
            double temp_2 = pow(p_ind_population->at(individual).all_x.at(1)-2, 2);
            double temp_3 = pow(p_ind_population->at(individual).all_x.at(2) -1, 2);
            double temp_4 = pow(p_ind_population->at(individual).all_x.at(3) -4, 2);
            double temp_5 = pow(p_ind_population->at(individual).all_x.at(4) -1, 2);
            p_ind_population->at(individual).fitness_value.push_back( temp_1 - temp_2 - temp_3 - temp_4 - temp_5);
            double temp_summation = 0.0;
            for(int i=0;i<p_ind_population->at(individual).all_x.size();i++){
                temp_summation += pow(p_ind_population->at(individual).all_x.at(i), 2);
            }
            p_ind_population->at(individual).fitness_value.push_back( temp_summation);
            break;
        }
            
        case 14:{
            p_ind_population->at(individual).fitness_value.push_back(p_ind_population->at(individual).all_x.at(0));
            
            double temp = (p_ind_population->at(individual).all_x.at(0)/(1+p_ind_population->at(individual).all_x.at(1)));
            double f_2_x = (1+p_ind_population->at(individual).all_x.at(1))*exp(-temp);
            p_ind_population->at(individual).fitness_value.push_back(f_2_x);
            
            break;
        }
            
        case 15:{
            p_ind_population->at(individual).fitness_value.push_back(p_ind_population->at(individual).all_x.at(0));
            p_ind_population->at(individual).fitness_value.push_back((p_ind_population->at(individual).all_x.at(1) + 1)/p_ind_population->at(individual).all_x.at(0));
            break;
        }
            
        case 16:{
            double summation_x_y = pow(p_ind_population->at(individual).all_x.at(0), 2) + pow(p_ind_population->at(individual).all_x.at(1), 2);
            p_ind_population->at(individual).fitness_value.push_back(0.5*summation_x_y + sin(summation_x_y));
            double numerator_1 = pow(((3*p_ind_population->at(individual).all_x.at(0))-(2*p_ind_population->at(individual).all_x.at(1))+4),2);
            double numerator_2 = pow((p_ind_population->at(individual).all_x.at(0) - p_ind_population->at(individual).all_x.at(1) +1), 2);
            p_ind_population->at(individual).fitness_value.push_back((numerator_1/8)+(numerator_2/27)+15);
            p_ind_population->at(individual).fitness_value.push_back((1/(summation_x_y+1))-(1.1*exp(-summation_x_y)));
        }
            
    }
}
