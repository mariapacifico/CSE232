/*Project 2: Genetics
Functions that take a DNA sequence and convert it to an amino acids and coexist with the header file bio.h and main.cpp
*/

#include <iostream>
using std::cout;
#include <string>
using std::string;
#include<vector>
using std::vector;
#include <algorithm>

#include "bio.h"

bool IsValidDNASequence(const string &input){
/*    iterate through string and check to see if all letters are 
     'A', 'T', 'C', or 'G'. Otherwise, return false*/
    for (char letter:input){
        if ((letter != 'A') && (letter != 'T') && (letter != 'C') && 
        (letter != 'G')){
            return false;
        }
    }
    return true;
}

void GetReverseComplementSequence(const std::string & input,  std::string * const output){
/*    iterate through input in reverse and then add to new string
    the complimentary base. This new_string will be output*/
    string new_string;
    for (auto index = input.rbegin(); index != input.rend(); ++index){
        if (*index == 'A')
            new_string.push_back('T');
        else if (*index == 'T')
            new_string.push_back('A');
        else if (*index == 'C')
            new_string.push_back('G');
        else if (*index == 'G')
            new_string.push_back('C');
        else if (*index == 'U')
            new_string.push_back('A');
    }
    *output = new_string;
}

std::string GetRNATranscript(const std::string & input){
    string get_reverse;
    /*Call for the RNA */
    GetReverseComplementSequence(input, &get_reverse);
    
    /*change the 'T' to 'U'*/
    int index = 0;
    for (char letter : get_reverse){
        if (letter == 'T'){
            get_reverse[index] = 'U';
        }
        index += 1;
    }
    
    return get_reverse;
}

std::vector<std::vector<std::string>> GetReadingFramesAsCodons(const std::string & input){
    
    string original = GetRNATranscript(input);
    string anti_parallel = GetRNATranscript(original);
    std::vector<std::vector<std::string>> output;
    
    /* For the original string, add three characters to
    a vector and then add to the final output vector*/
    int count = 0;
    while(count < 3){
        /* The size of the vector is length is the original strings lengths divided by 3*/
        int size_of_vector = (original.length() - count)/ 3;
        vector<string> original_all(size_of_vector);
        /*have to move the starting point every iteration*/
        int index = 0 + count;
        for(auto &x : original_all){
            x = original.substr(index, 3);
            index += 3;
        }
        output.push_back(original_all);
        count += 1;
    }
    
    /*Do the same thing to the anti_paralle string*/
    int count_anti = 0;
    
    while(count_anti < 3){
        int size_of_vector = (original.length() - count_anti)/ 3;
        vector<string> anti_parallel_all(size_of_vector);
        int index = 0 + count_anti;
        
        for (auto &x : anti_parallel_all){
            x = anti_parallel.substr(index, 3);
            index += 3;
        }
        output.push_back(anti_parallel_all);
        count_anti += 1;
    }
   
    return output;
}

std::string Translate(const std::vector<std::string> & codon_sequence){
    
    string amino_acids_string;
    /* Vectors of the corressponing codons and amino acids*/
    vector<string> all_codons = {"GCU", "GCC", "GCA", "GCG", "CGU", "CGC", "CGA", "CGG", "AGA", "AGG", "AAU", "AAC", "GAU", "GAC", "UGU", "UGC", "CAA", "CAG", "GAA", "GAG", "GGU", "GGC", "GGA", "GGG", "CAU", "CAC", "AUU", "AUC", "AUA", "UUA", "UUG", "CUU", "CUC", "CUA", "CUG", "AAA", "AAG", "AUG", "UUU", "UUC", "CCU", "CCC", "CCA", "CCG", "UCU", "UCC", "UCA", "UCG", "AGU", "AGC", "ACU", "ACC", "ACA", "ACG", "UGG", "UAU", "UAC", "GUU", "GUC", "GUA", "GUG", "UAG", "UGA", "UAA"};
    
    vector<string> all_amino_acids = {"A", "A", "A", "A", "R", "R", "R", "R", "R", "R", "N", "N", "D", "D", "C", "C", "Q", "Q", "E", "E", "G", "G", "G", "G", "H", "H", "I", "I", "I", "L", "L", "L", "L", "L", "L", "K", "K", "M", "F", "F", "P", "P", "P", "P", "S", "S", "S", "S", "S", "S", "T", "T", "T", "T", "W", "Y", "Y", "V", "V", "V", "V", "*", "*", "*"};


    for (auto codon : codon_sequence){
        /*Sources used for this code to understand how to find where in a vector an element is:
            Piazza post @786 
            https://thispointer.com/c-how-to-find-an-element-in-vector-and-get-its-index/*/
        /*find the position of the codon */
        auto position_of_codon = find(all_codons.begin(), all_codons.end(), codon);
        /*find distance in the all_codons vector*/
        auto distance_of_codon = std::distance(all_codons.begin(), position_of_codon);
        /*add the amino amino acid to the string using the index of the all_amino_acids vector */
        amino_acids_string += all_amino_acids[distance_of_codon];
    }
    
    return amino_acids_string;
}

std::string GetLongestOpenReadingFrame(const std::string & DNA_sequence){
    
    string longest_frame;
    string possible_option;
    std::vector<std::vector<std::string>> total_codon_sequence = GetReadingFramesAsCodons(DNA_sequence);
    
    /* go through each vector and use the translate function to get the amino acids */
   for (auto vector_of_codons : total_codon_sequence){
       
       string codon_string = Translate(vector_of_codons);
       size_t where_m_is = codon_string.find('M');
       size_t where_stop_is = codon_string.find('*');
       
       /* find m and *, check to see that the positon of '*' is greater than m. There may be multiple strings with m and '*' */
       while (where_m_is != std::string::npos){
        
           while (where_stop_is != std::string::npos){
              /* create the possible string*/
               if (where_stop_is>where_m_is){
                    possible_option = codon_string.substr(where_m_is, where_stop_is - where_m_is + 1);
                    /* check to see if length is greater than the possible returned string */
                    if (possible_option.length() > longest_frame.length()){
                        longest_frame = possible_option;
                    }
                    
                    /*find the next m or '*' */
                    where_stop_is = codon_string.find('*', where_stop_is + 1);
                    break;
                }
                where_stop_is = codon_string.find('*', where_stop_is + 1);
           }
           where_m_is = codon_string.find('M', where_m_is + 1);
       }
   }
    return longest_frame;
}