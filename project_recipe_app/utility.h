#pragma once

// If you have any classes or functions that you don't want to put in recipe.h or app.h, put them here.
#include "recipe.h"
#include <sstream> 
using std::istringstream; using std::ostringstream;
#include<string>
using std::string;
#include<iostream>
using std::cout; 

//This function reduces fractions
string reduce_fraction(const string & fraction){
    ostringstream oss;
    int numerator;
    int denominator;
    int full_number = 0;
    char c;
    istringstream iss(fraction);
    auto find_fraction = fraction.find('/');
    
    //check to see if it's a fraction
    if (find_fraction != string::npos){
        auto find_full_num = fraction.find('-');
        //if there is a full number
        if(find_full_num != string::npos){
            iss >> full_number;
            iss.get(c);
        }
        iss >> numerator;
        iss.get(c);
        iss >> denominator;
    }
    //just a full number
    else
        return fraction;
    
    //just a full number
    if (numerator % denominator == 0){
        full_number += numerator / denominator;
        oss << full_number;
        return oss.str();
    }
    
    //get the full number
    int divide = numerator/denominator;
    full_number += divide;
    numerator -= (divide * denominator);
    
    //reducing:
    //http://www.cplusplus.com/forum/general/74688/
    for (int i = denominator * numerator; i > 1; i--) {  if ((denominator % i == 0) && (numerator % i == 0)) {  
            denominator /= i;  
            numerator /= i;  
        }     
    }
        
    //return to oss
    if(full_number != 0){
        oss << full_number << '-';
    }
    oss << numerator << '/' << denominator;
    
    return oss.str();
}

//this function divides fractions
string divide_fraction(string fraction, int divisor){
    ostringstream oss;
    int numerator;
    int denominator;
    int full_number = 0;
    char c;
    istringstream iss(fraction);
    auto find_fraction = fraction.find('/');
    
    if (divisor == 1){
        return fraction;
    }
    
    //check to see if it's already a fraction
    if (find_fraction != string::npos){
        auto find_full_num = fraction.find('-');
        //if there is a full number
        if(find_full_num != string::npos){
            iss >> full_number;
            iss.get(c);
        }
        iss >> numerator;
        iss.get(c);
        iss >> denominator;
        
        if(full_number != 0){
            numerator += (full_number * denominator);
        }
        
        //multiply divisor by denominator
        denominator *= divisor;
        oss << numerator << '/' << denominator;
    }
    
    else{
        oss << fraction << '/' << divisor;
    }
    
    return oss.str();
}

//this function multiplys fraction
string multiply_fraction(string fraction, int multiple){
    ostringstream oss;
    int numerator;
    int denominator;
    int full_number = 0;
    char c;
    istringstream iss(fraction);
    auto find_fraction = fraction.find('/');
    
    if (multiple == 1){
        return fraction;
    }
    
    if (find_fraction != string::npos){
        auto find_full_num = fraction.find('-');
        
        if(find_full_num != string::npos){
            iss >> full_number;
            iss.get(c);
        }
        
        iss >> numerator;
        iss.get(c);
        iss >> denominator;
        
        if(full_number != 0){
            numerator += (full_number * denominator);
        }
        
        //multiply numerator by multiple
        numerator *= multiple;
        oss << numerator << '/' << denominator;
    }
    
    else{
        iss >> full_number;
        full_number *= multiple;
        oss << full_number;
    }
    
    return oss.str();
}

//This function takes a string of a fraction and returns that double
double turn_fraction_to_double(string fraction){
    
    double return_num = 0;
    ostringstream oss;
    int numerator;
    double denominator;
    int full_number = 0;
    char c;
    istringstream iss(fraction);
    auto find_fraction = fraction.find('/');
    
    if(find_fraction != string::npos){
        auto find_full_num = fraction.find('-');
        if(find_full_num != string::npos){
            iss >> full_number;
            iss.get(c);
        }
        iss >> numerator;
        iss.get(c);
        iss >> denominator;
        
        numerator += (denominator * full_number);
        return_num = numerator / denominator;
    }
    
    else{
        iss >> return_num;
    }
    
    return return_num;
    
}

