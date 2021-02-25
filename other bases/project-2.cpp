/*Project 1 CSE 232
Convert numbers to different bases (1-10)
and do math with them.
3 functions: 1 to convert to decimal (base 10), 2 
to convert decimal to another base, 3 to do math
operations
Then use main to cin and cout*/

#include<iostream>
using std::cout; using std::cin;
using std::endl;
#include <math.h>

int convert_other_base_to_decimal(int value, int base) {
    int ones_place;
    int power = 0;
    int final_value = 0;
    
    //get the last value, multiply by base with a power starting at 0, loop until no more values
    while(value > 0){
        ones_place = value % 10;
        final_value += (ones_place * pow(base,power));
        power += 1;
        value = value / 10;
    }
    return final_value;
}

int convert_decimal_to_other_base(int value, int base) {
    int mulitply_by_ten;
    int power = 0;
    int final_value = 0;
    
    //get the last value, mulitply it by 10 starting at 0, then divide value by base, loop until no more values
    while(value > 0){
        mulitply_by_ten = value % base;
        final_value += (mulitply_by_ten * (pow(10,power)));
        power += 1;
        value = value / base;
    }
    return final_value;
}

int math_in_other_base(int other_base_a, int other_base_b, int base, char math_operator) {
    //convert to decimal
    int base_a_decimal = convert_other_base_to_decimal(other_base_a, base);
    int base_b_decimal = convert_other_base_to_decimal(other_base_b, base);
    
    int result;
    
    //find which operation asked and then preform operation
    if (math_operator == '+'){
        result = base_a_decimal + base_b_decimal;
    }
    else if (math_operator == '-'){
        result = base_a_decimal - base_b_decimal;
    }
    else if (math_operator == '/'){
        result = base_a_decimal / base_b_decimal;
    }
    else if(math_operator == '%'){
        result = base_a_decimal % base_b_decimal;
    }
    else if (math_operator == '*'){
        result = base_a_decimal * base_b_decimal;
    }
    
    //convert result into original base
    return convert_decimal_to_other_base(result, base);
}

int main() {
    int num_1, num_2, base;
    char math_operator;
    
    cin >> num_1 >> num_2 >> base >> math_operator;
    //output math_in_other_base results
    cout << math_in_other_base(num_1, num_2, base, math_operator) << endl;
}