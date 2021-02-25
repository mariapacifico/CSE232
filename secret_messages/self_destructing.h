#ifndef SELF_DESTRUCTING_H
#define SELF_DESTRUCTING_H

#include<iostream>
using std::ostream; using std::istream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <ios>
#include<sstream>
using std::stringstream;

//Has a vector of messages and each index can only be viewed a certain amount of time, initalized with number_of_allowed_views
//all_indexes keeps track of which indexes have already been viewed
class SelfDestructingMessage {
private:
    vector<string> messages;
    long number_of_allowed_views = 0;
    string all_indexes;
public:
    //constructors
    SelfDestructingMessage()=default;
    SelfDestructingMessage(vector<string>, long);
    
    //copy constructor 
    //number_of_allowed_views = 0 for the original SelfDestructingMessage 
    //everything else is transferred to the new SelfDestructingMessage
    SelfDestructingMessage(SelfDestructingMessage &);
    
    //operator[]
    //returns the message at the specific index
    //throws an out_of_range when index isn't valid 
    //throws an invaid_argument error when there are no more views remaining 
    //if it is valid, the number of views allowed will go down by one
    const string & operator[](size_t);
    
    //operator <<
    //https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019
    friend ostream& operator<<(ostream&, const SelfDestructingMessage&);
    
    //operator >>
    //https://www.learncpp.com/cpp-tutorial/93-overloading-the-io-operators/
    //is number of views = 0 and the message it "hi there" output looks like: 
    //00: ## ####
    friend istream& operator>> (istream &in, SelfDestructingMessage &input);
    
    //operator =
    //same concept as the copy constructor
    SelfDestructingMessage& operator=(SelfDestructingMessage&); 
    
    //Methods:
    //returns an int of how many messages there are
    int size(); 
    
    //all_indexes keeps track of indexes that are successful and counts how many times the number is in the string and subratct from number_of_allowed_views
    //returns the number of views remaining
    int number_of_views_remaining(int);
    
    //iterates through messages and copys into a new vector
    //each message goes through redact_alphabet_digits
    //number of views is not affected
    vector<string> get_redacted();
    
    //enters a string array and the size of the array with a long
    //add each string in array to messages
    void add_array_of_lines(string *, long); 
};

//overloaded operators 
ostream& operator<<(ostream& os, const SelfDestructingMessage& input);
istream& operator>>(istream &in, SelfDestructingMessage &);

#endif
