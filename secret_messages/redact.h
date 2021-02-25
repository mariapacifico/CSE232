#ifndef REDACT_H
#define REDACT_H

#include<string>
using std::string;
#include<vector>
using std::vector;

//changes all characters to #
//if string == "hey there"
//output: "#########"
string redact_all_chars(const string &);
//changes all alphabet and numbers to ##
//if string == "hey there!"
//output: "### #####!"
string redact_alphabet_digits(const string &);
//all words inside of vector and string are changed to ##
//if vector<string> == {hey, pal, miss}
//and string == "hey there pal. I miss you"
//output: "### there ###. I #### you."
string redact_words(const string &, const vector<string> &);

#endif
