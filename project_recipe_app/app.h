#pragma once

#include "recipe.h"
#include "utility.h"
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<map>
using std::map;
#include <sstream> 
using std::istringstream; using std::ostringstream;
#include <exception>

class RecipeApp{
private:
    //maps will ensure they'll be alphabetical
    map<string, Recipe> recipes_;
    map<string, string> in_pantry_;
    
public:
    //constructor
    RecipeApp()=default;
    
    //member functions
    void AddRecipe(const Recipe &);
    void AddIngredientToPantry(const string &);
    Recipe UseUpIngredient (const string &);
    
    //operator <<
    friend ostream &operator<<(ostream&, const RecipeApp&);
};

//AddRecipe method
void RecipeApp::AddRecipe(const Recipe & input){
    string name = input.name_of_recipe_;
    recipes_.insert(std::pair<string,Recipe>(name,input));
}

//AddIngredientToPantry method
void RecipeApp::AddIngredientToPantry(const string & input){
    istringstream iss(input);
    string fraction;
    string unit;
    string name;
    
    //get the name and add to map to ensure it's ordered alphabetically
    iss >> fraction;
    iss>> unit;
    iss >> name;
    in_pantry_.insert(std::pair<string,string>(name,input));
}

//operator <<
//How it will look:
//"Recipes in the app (ordered by name):
//INSERT RECIPES 
//
//Ingredients in pantry (ordered by name):
//INSERT INGREDEINTS 
//"
ostream &operator<<(ostream& out, const RecipeApp& input){
    out << "Recipes in the app (ordered by name):" <<endl;
    for(auto element : input.recipes_){
        Recipe the_recipe = element.second;
        out << the_recipe;
    }
    out << "Ingredients in pantry (ordered by name):" <<endl;
    for(auto other_element : input.in_pantry_){
        string the_pantry = other_element.second;
        out << the_pantry << endl;
    }
    
    return out;
}

//UseUpIngredient method
Recipe RecipeApp::UseUpIngredient (const string & input){
    istringstream iss(input);
    string number;
    string unit;
    string name;
    iss >> number; 
    iss >> unit >> name;
    number = reduce_fraction(number);
    
    //get through the recipes_
    for (auto element : recipes_){
        Recipe in_list = element.second;
        
        //go through ingredients in that recipe
        for(string ingredients : in_list.ingredients_){
            //find the ingredient
            auto result = ingredients.find(name);
            
            if (result != string::npos){
                istringstream iss2(ingredients);
                string fraction;
                iss2 >> fraction;
                
                //divide the fraction by servings to get one serving
                string divided_fraction = divide_fraction(fraction, in_list.servings_);
                divided_fraction = reduce_fraction(divided_fraction);
                //turn that number into a double
                double divsor = turn_fraction_to_double(divided_fraction);
                //and the number inputed into a double
                double new_number = turn_fraction_to_double(number);
                //the new servings are the new number and the divsor
                int new_servings = new_number / divsor;

                //change the recipe servings to have new servings
                in_list.ChangeServings(new_servings);
                
                return in_list;
            }
        }
    }
    
    //if the ingreident is no recipe
    throw std::invalid_argument("Invalid");
}







