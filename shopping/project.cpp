#include <iostream>
using std::cin; using std::cout; 
using std::endl;
#include<string>
using std::string;
#include <sstream> 
using std::ostringstream; using std::istringstream;
#include<utility>
using std::pair; using std::make_pair;
#include<map>
using std::map;
#include<vector>
using std::vector;
#include<algorithm>
using std::for_each;
#include <iomanip>


//this function returns a map that displays the store and the location
//{store, location}
map<string, string> store_and_location(const string &full_line){
    //final return
    map<string, string> return_store_and_location;
    
    istringstream iss(full_line);
    string line_reading;
    //skip first line
    std::getline(iss, line_reading);
    vector<string> vector_of_lines;
    
    //get each line, enter into vector up until there is an empty string
    //once there is a space, make a pair of location and store, put into map
    //clear vector and repeat
    while(getline(iss, line_reading)){
        
        if(line_reading != "")
            vector_of_lines.push_back(line_reading);
            
        else{
            return_store_and_location.insert(make_pair(vector_of_lines[0],vector_of_lines[1]));
            vector_of_lines.clear();
        }
    }
    
    return return_store_and_location;
}

//this function creates a master map
//{store, {item, {quanitity, price}}}
map<string, vector<pair<string, vector<double>>>> store_and_items(const string& full_line){
    
    //this is what is returned
    map<string, vector<pair<string, vector<double>>>> return_store_and_items;
    
    istringstream iss(full_line);
    string line_reading;
    //skip first line
    std::getline(iss, line_reading);
    vector<string> vector_of_lines;
    
    while(getline(iss, line_reading)){
        //lines that are empty mean that there is a new store
        if(line_reading != "")
            vector_of_lines.push_back(line_reading);
        
        else{
            
            string store_name = vector_of_lines[0];
            pair<string, vector<double>> items_and_price;
            vector<pair<string, vector<double>>>add_to_return;
            
            //go through the vector that was created and add to the return map
            std::for_each (vector_of_lines.begin() + 2, vector_of_lines.end(), 
            [&](const string& each_element){
                string item;
                string number;
                string cost;
                vector<double> number_cost;
                
                //split at comma
                int comma = each_element.find(',');
                item = each_element.substr(0, comma);
                
                //there are 2 commas in each line
                int second_comma = each_element.find(',', comma +1);
                number = each_element.substr((comma+1), (second_comma-item.length() - 1));
                cost = each_element.substr(second_comma + 2);
                
                //turn into doubles
                number_cost.push_back(stod(number));
                number_cost.push_back(stod(cost));
                
                pair<string,vector<double>> add_to_vector = {item, number_cost};
                
                add_to_return.push_back(add_to_vector);
                });
            
            return_store_and_items[store_name] = add_to_return;
            
            //clear the vector for the next store
            vector_of_lines.clear();
            }
        }
    
    return return_store_and_items;
}

//this function creates a vector of the stores in the order they were inputted
vector<string> stores_in_order(const string & full_line){
    vector<string> return_store;
    
    istringstream iss(full_line);
    string line_reading;
    //skip first line
    std::getline(iss, line_reading);
    vector<string> vector_of_lines;
    
    while(getline(iss, line_reading)){
        
        if(line_reading != "")
            vector_of_lines.push_back(line_reading);
            
        else{
            //only get the stores
            return_store.push_back(vector_of_lines[0]);
            vector_of_lines.clear();
        }
    }
    
    return return_store;
}

//this function returns a map of how many of each item is available
//{item, quanitity}
map<string, int> number_of_items(map<string,vector<pair<string,
vector<double>>>> number_and_cost_in_store, 
const vector<string>  &store_names){
    
    map<string, int> return_number_of_items;
    
    for(string stores : store_names){
        //get the vector for each store name
        vector<pair<string, vector<double>>> whats_in_store = 
        number_and_cost_in_store[stores];
        //new_pair.second = vector<double> and the 0 index is quanitity
        //new_pair.first = item
        std::for_each(whats_in_store.begin(), whats_in_store.end(), [&return_number_of_items](pair<string, vector<double>> new_pair){
            vector<double> items_and_price = new_pair.second;
            return_number_of_items[new_pair.first] += items_and_price[0];
        });
    }
    
    return return_number_of_items;
}


//this function returns a function that shows the store and vector<double> that hold the quanitity and price
//{store, {quanitity, price}}
map<string, vector<double>> which_stores_have_item(map<string, vector<pair<string, vector<double>>>> master_map, const string & item){
    
    map<string, vector<double>> return_which_stores_have_item;
    
    //go through the master map and put in map respecitvely 
    for(auto itr = master_map.begin(); itr != master_map.end(); ++itr){
        string store = itr -> first;
        auto items_vector = itr -> second;
        
        for(auto itr2 = items_vector.begin(); itr2 != items_vector.end(); ++itr2){
            string item_in_store = itr2 -> first;
            if ( item_in_store== item){
             return_which_stores_have_item[store] = itr2 -> second;
            }
        }
        
    }
    
    return return_which_stores_have_item;
}

//this function returns the final string that you cout to show how much you have to shop
string final_output(map<string, vector<double>> & which_stores_have_item, double &quanitity, map<string, string> store_and_location){
    
    ostringstream return_string;
    ostringstream add_to_return;
    double total_price = 0;
    //see which stores already been shopped at
    vector<string> stores_already_used;
    
    while((quanitity > 0)){
        //eventually will be the best places to go, based on price
        string store;
        string store_location;
        //make a huge number at first
        double best_price = 10000000;
        double number_in_stores;
        
        for(auto itr = which_stores_have_item.begin(); itr != which_stores_have_item.end(); ++itr){
            string store_in_loop = itr -> first;
            
            //https://stackoverflow.com/questions/6277646/in-c-check-if-stdvectorstring-contains-a-certain-value
            //see if store has already been stores_already_used
            if (std::find(stores_already_used.begin(), stores_already_used.end(), store_in_loop) != stores_already_used.end()){
                continue;
            }
            
            //find where the store is located
            string location_in_loop = store_and_location[store_in_loop];
            vector<double> quanitity_and_price = itr -> second;
            
            //find the smallest price
            if(quanitity_and_price[1] < best_price){
                best_price = quanitity_and_price[1];
                store = store_in_loop;
                store_location = location_in_loop;
                
                //figure out how much price should be multiplied by
                if(quanitity_and_price[0] <= quanitity){
                    number_in_stores = quanitity_and_price[0];
                }
                else
                    number_in_stores = quanitity;
            }
        }
        
        //add to total price and subtract from quantity
        total_price += number_in_stores * best_price;
        quanitity -= number_in_stores;
        stores_already_used.push_back(store);
        
        //add to ostringstream
        add_to_return << "Order " << number_in_stores << " from " << store << " in " << store_location << endl;
        
        //when there are no more stores available
        if(stores_already_used.size()== which_stores_have_item.size()){
            break;
        }
    }
    
    return_string << "Total price: $" <<std::fixed<< std::setprecision(2) << total_price << endl;
    return_string << add_to_return.str() << endl;
    
    return return_string.str();
}

//this function finds the total price at every store, depending on qunanitity
//almost the same as final_output, but returns double
double total_price(const map<string, vector<double>> & which_stores_have_item, double &quanitity){
    
    double total_price = 0;
    //see which stores already been shopped at
    vector<string> stores_already_used;
    
    while((quanitity > 0)){
        //initialize, later the best will be assigned
        string store;
        double best_price = 10000000;
        double number_in_stores;
        
        for(auto itr = which_stores_have_item.begin(); itr != which_stores_have_item.end(); ++itr){
            string store_in_loop = itr -> first;
            
            //https://stackoverflow.com/questions/6277646/in-c-check-if-stdvectorstring-contains-a-certain-value
            //see if store has already been stores_already_used
            if (std::find(stores_already_used.begin(), stores_already_used.end(), store_in_loop) != stores_already_used.end()){
                continue;
            }
            
            //find where the store is located
            vector<double> quanitity_and_price = itr -> second;
            
            //find the smallest price
            if(quanitity_and_price[1] < best_price){
                best_price = quanitity_and_price[1];
                store = store_in_loop;
                
                //figure out how much price should be multiplied by
                if(quanitity_and_price[0] <= quanitity){
                    number_in_stores = quanitity_and_price[0];
                }
                else
                    number_in_stores = quanitity;
            }
        }
        
        //add to total price and subtract from quantity
        total_price += number_in_stores * best_price;
        quanitity -= number_in_stores;
        stores_already_used.push_back(store);
        
        //when there are no more stores available
        if(stores_already_used.size()== which_stores_have_item.size()){
            break;
        }
    }
    
    return total_price;
}


int main(){
    //Get number of stores, first line
    int number_of_stores;
    cin >> number_of_stores;
    
    //To get full input, use get line and continue until there are two line of empty space 
    string input;
    ostringstream full_input;
    int count_white_space = 0;
    
    //input EVERYTHING
    while(getline(cin,input)){
        if (input == ""){
            count_white_space += 1;
            if (count_white_space == 2)
                break;
        }
        else
            count_white_space = 0;
        full_input << input <<endl;
    }
    
    //split to after grocery list
    size_t where_to_split = full_input.str().find("items on my shopping list:");
    string second_full_input = full_input.str().substr(where_to_split);
    
    //Correct output:
    
    cout << "Store Related Information (ordered by in-file order):" << endl;
    cout << "There are " << number_of_stores << " store(s)." << endl;
    
    
    ostringstream distinct_items;
    vector<string> stores_order = stores_in_order(full_input.str());
    
    //use the store_and_items function to get distinct items
    map<string, vector<pair<string, vector<double>>>> number_and_cost_in_store = store_and_items(full_input.str());
    
    //iterate through stores_order, to ensure the correct order
    for(string stores: stores_order){
        vector<pair<string, vector<double>>> whats_in_store = number_and_cost_in_store[stores];
        distinct_items << stores << " has " << whats_in_store.size() << " distinct items." << endl;
    }
    
    cout << distinct_items.str() << endl;
    
    cout << "Item Related Information (ordered alphabetically):" << endl;
    
    ostringstream items_alphabetically;
    
    //maps automatically are alphabetical
    map<string, int> return_number_of_items = number_of_items(number_and_cost_in_store, stores_order);
    
    //size displays how many items there are
    cout << "There are " << return_number_of_items.size() << " distinct item(s) available for purchase." << endl;
    
    //iterate through map to display how many of each item is available
    for(auto itr = return_number_of_items.begin(); itr!= return_number_of_items.end(); ++itr){
        items_alphabetically << "There are " << itr -> second << " " << itr->first <<"(s)." <<endl;
    }
    
    cout << items_alphabetically.str() << endl;
   
    //output shopping:
    cout << "Shopping:" << endl;
    
    //going to need for final_output function
    map<string, string> returned_store_and_location = store_and_location(full_input.str());
    
    //use second_full_input, that was splitted earlier from full_input
    istringstream iss2(second_full_input);
    string line_of_list;
    
    //get rid of first line
    getline(iss2, line_of_list);
    ostringstream shopping_output;
    
    double final_price = 0;
    
    while(getline(iss2, line_of_list)){
        if(line_of_list == "")
            break;
        //get quanitity and item
        istringstream iss2(line_of_list);
        double quanitity;
        string item;
        
        iss2 >> quanitity;
        //quanitity2 will be needed for total_price
        double quanitity2 = quanitity;
        
        getline(iss2, item);
        //get rid of space in front of item
        item = item.substr(1);
        
        //need for final_price, total_price and the size will tell how many stores are available
        map<string, vector<double>> which_stores = which_stores_have_item(number_and_cost_in_store, item);
        
        shopping_output << "Trying to order " << quanitity << " " << item <<"(s)." << endl;
        shopping_output << which_stores.size() << " store(s) sell " << item << "." << endl;
        
        //add total_price return to final price
        final_price += total_price(which_stores, quanitity2);
        
        
        string add_to_shopping_output = final_output(which_stores, quanitity, returned_store_and_location);
        
        shopping_output << add_to_shopping_output << endl;
        
    }
    
    cout << shopping_output.str() << endl;
    cout << "Be sure to bring $" << std::fixed << std::setprecision(2) << final_price << " when you leave for the stores." << endl;
}
