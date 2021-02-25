#pragma once

#include<iostream>
using std::cout; using std::endl;
using std::getline; using std::ostream;
using std::skipws;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<algorithm>
using std::find_if;
#include <sstream> 
using std::istringstream; using std::ostringstream;
#include <exception>
#include <iterator>
#include <regex>
#include "utility.h"


class Recipe{

public:
    //make everything public so in RecipeApp you have access to everything
    string name_of_recipe_;
    int servings_ = 0;
    vector<string> ingredients_; 
    string instructions_;
    
    //constructors
    Recipe()=default;
    Recipe(string, int);
    
    //methods
    void AddIngredient(const string &);
    void SetInstructions(const string &);
    string IngredientInOneServing(const string &);
    void ChangeServings(const int &);
    
    //<<operator
    friend ostream &operator<<(ostream&, const Recipe&);
};

//constructor
Recipe::Recipe(string name, int servings){
    name_of_recipe_ = name;
    servings_ = servings;
}

//AddIngredient method
void Recipe::AddIngredient(const string & ingredient){
    
    string fraction;
    istringstream iss(ingredient);
    ostringstream oss;
    
    //get fraction and reduce it
    iss >> fraction;
    string reduced_fraction = reduce_fraction(fraction);
    
    //get unit
    string unit;
    iss >> unit;
    
    //get the rest of line and add to oss and then to ingredients_
    string value;
    getline(iss, value);
    
    //remove leading
    //count how many spaces up until the first non space
    //https://codereview.stackexchange.com/questions/40124/trim-white-space-from-string
    int count = 0;
    for(auto letter : value){
        if(!(isspace(letter)))
            break;
        count += 1;
    }
    value = value.erase(0, count);
    
    //remove trailing
    //count how many spaces up until the first non space, starting from the back
    count = 0;
    for(auto i = value.rbegin(); i != value.rend(); ++i){
        if(!(isspace(*i)))
            break;
        count += 1;
    }
    value = value.erase((value.length() - count), count);

    oss << reduced_fraction <<' '<< unit << ' '<< value;
    ingredients_.push_back(oss.str());
    
}

//SetInstructions method
void Recipe::SetInstructions(const string & instructions){
    istringstream iss(instructions);
    string value;
    ostringstream oss;
    
    //iterate thorough each line
    while(getline(iss, value)){
        
        //skip empty spaces
        if (value == ""){
            continue;
        }
        
        //make sure there are no extra spaces by using an istream
        istringstream iss2(value);
        string word;
        string full_line;
        while(iss2 >> skipws >>word){
            full_line += word + ' ';
        }
        
        //http://www.cplusplus.com/forum/beginner/54314/
        //remove the last space
        full_line = full_line.substr(0, full_line.length() - 1);
        
        oss << full_line << endl;
    }
    instructions_ = oss.str();
}

//operator <<
//How it will output:
//"Recipe for: Apples
//Serves 3
//Ingredients: 
//1 unit Apples
//
//Instructions:
//Eat it
//"
ostream &operator<<(ostream& out, const Recipe& input){
    out << "Recipe for: " <<input.name_of_recipe_ << endl;
    out << "Serves " << input.servings_ << endl;
    out << "Ingredients:" << endl;
    for (string element:input.ingredients_){
        out << element << endl;
    }
    out << endl;
    out<< "Instructions:" << endl;
    out << input.instructions_ << endl;
    
    return out;
}

//IngredientInOneServing method
//returns out how much you need for one serving for a specific ingredient
string Recipe::IngredientInOneServing(const string & input){
    ostringstream oss;
    
    //go through ingredients_ vector
    for(string element : ingredients_){
        auto result = element.find(input);
        
        //find the ingreident 
        if (result != string::npos){
            istringstream iss(element);
            string fraction;
            iss >> fraction;
            
            //divide fractions by servings and reduce it
            string divided_fraction = divide_fraction(fraction, servings_);
            divided_fraction = reduce_fraction(divided_fraction);
            
            string unit;
            iss >> unit;
        
            oss << divided_fraction << ' ' << unit << ' ' << input;
            return oss.str();
        }
    }
    
    //when the ingreident isn't in recipe
    throw std::invalid_argument("Invalid");
}

//ChangeServings method
void Recipe::ChangeServings(const int & new_servings){
    
    //go through ingredients_vector
    for(string & element : ingredients_){
        istringstream iss(element);
        ostringstream oss;
        string fraction;
        string rest_of_line;
        
        //get the fraction
        iss >> fraction;
        getline(iss, rest_of_line);
        
        //get to just one serving
        string divided_fraction = divide_fraction(fraction, servings_);
        divided_fraction = reduce_fraction(divided_fraction);
        //mulitply it by new_servings
        divided_fraction = multiply_fraction(divided_fraction, new_servings);
        divided_fraction = reduce_fraction(divided_fraction);
        
        oss << divided_fraction << rest_of_line;
        element = oss.str();
    }
    
    //change servings to the new one
    servings_ = new_servings;
}






