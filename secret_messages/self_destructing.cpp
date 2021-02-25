#include "self_destructing.h"
#include "redact.h"

#include<iostream>
using std::cout; using std::endl; 
using std::istream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include <algorithm>
using std::copy; using std::for_each;
#include <stdexcept>
using std::invalid_argument; using std::out_of_range;
#include <iterator>
using std::back_inserter;
#include <iomanip>
using std::setw; using std::setfill;
#include<sstream>
using std::stringstream;

//two param constructor
SelfDestructingMessage::SelfDestructingMessage(vector<string> input_vector, long input_long){
    messages = input_vector;
    number_of_allowed_views = input_long;
}

//size method
int SelfDestructingMessage::size(){
    int return_size = messages.size();
    return return_size;
}

//get_redacted method
vector<string> SelfDestructingMessage::get_redacted(){
    
    vector<string> return_vector;
    copy(messages.begin(), messages.end(), back_inserter(return_vector));
    for(string &element : return_vector){
        element = redact_alphabet_digits(element);
    }
    
    return return_vector;
}

//number_of_views_remaining method
int SelfDestructingMessage::number_of_views_remaining(int message_index){
    
    int count = 0;
    string index = std::to_string(message_index);
    
    //count how many times index is in all_indexes
    auto result = all_indexes.find(index);
    while(result != string::npos){
        count += 1;
        result = all_indexes.find(index, result+1);
    }
    
    return (number_of_allowed_views - count);
}

//operator []
const string& SelfDestructingMessage::operator[](size_t index){
    if((messages.size() <= index) || (index < 0)){
        throw out_of_range("Not a valid index");
    }
    int number_of_views = number_of_views_remaining(index);
    
    if(number_of_views == 0){
        throw invalid_argument("No more views");
    }
    
    all_indexes += std::to_string(index);
    
    return messages[index];
    
}

//operator <<
//declared as a friend function
ostream& operator<<(ostream& os, const SelfDestructingMessage& input){
    
    for(size_t i = 0; i < (input.messages.size()); ++i){
         string redox_message = redact_alphabet_digits(input.messages[i]);
         int count = 0;
        
        //count how many times index is in all_indexes
        string index = std::to_string(i);
        auto result = input.all_indexes.find(index);
        while(result != string::npos){
            count += 1;
            result = input.all_indexes.find(index, result+1);
        }
         
         int number_of_views = (input.number_of_allowed_views - count);
         os << setfill('0') << setw(2) << number_of_views << ": " << redox_message << endl;
    }
    return os;
}

//copy constructor
SelfDestructingMessage::SelfDestructingMessage(SelfDestructingMessage & input){
    messages = input.messages;
    number_of_allowed_views = input.number_of_allowed_views;
    all_indexes = input.all_indexes;
    
    input.all_indexes.clear();
    input.number_of_allowed_views = 0;
}

//Assignment
SelfDestructingMessage& SelfDestructingMessage::operator=(SelfDestructingMessage& input){
    
    messages = input.messages;
    number_of_allowed_views = input.number_of_allowed_views;
    all_indexes = input.all_indexes;
    
    //to ensure the number_of_allowed_views is 0
    input.all_indexes.clear();
    input.number_of_allowed_views = 0;
    
    return *this;
}

//operator >>
//declare as friend function
istream& operator>> (istream &in, SelfDestructingMessage &input){
    
    string new_message;
    std::getline(in, new_message);
    input.messages.push_back(new_message);
    
    return in;
}

//add_array_of_lines method
void SelfDestructingMessage::add_array_of_lines(string* array, long size){
    
    for(long i = 0; i < size; ++i){
        messages.push_back(*(array + i));
    }
}