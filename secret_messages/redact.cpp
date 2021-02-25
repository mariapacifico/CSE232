#include "redact.h"
#include<string>
using std::string;
#include <algorithm>
using std::replace_if;
#include<vector>
using std::vector;
#include<iostream>
using std::cout;

string redact_all_chars(const string & input){
    //find the length of string
    //add '#' to final string length amount of times
    int length_of_input = input.length();
    string final_string;
    
    for(int i = 0; i < length_of_input; ++i){
        final_string += '#';
    }
    
    return final_string;
}

string redact_alphabet_digits(const string & input){
    //copy string and use replace_if to check if there is an alphabet or digit
    string change_input = input;
    replace_if(change_input.begin(), change_input.end(), [](char element){
        //lamda used to check element is digit or alpha
        if (isdigit(element))
            return true;
        else if (isalpha(element))
            return true;
        else
            return false;
    }, '#');
    
    return change_input;
    
}

string redact_words(const string & input, const vector<string> & words_to_replace){
    
    string change_input = input;
    for(string word : words_to_replace){
        //use a while loop to find word in the string and replace it with '#'
        //make a string with length of #
        size_t length_of_word = word.length();
        string total_pounds;
        for(size_t i = 0; i < length_of_word; ++i){
            total_pounds += '#';
        }
        
        size_t result = change_input.find(word);
        while (result != string::npos) {
            //http://www.cplusplus.com/reference/string/string/replace/
            change_input.replace(result, length_of_word, total_pounds);
            result = change_input.find(word, result+1);
        }
    }
    
    return change_input;
}





