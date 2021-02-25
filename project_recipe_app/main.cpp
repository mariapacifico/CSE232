#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

#include "app.h"
#include "recipe.h"
#include "utility.h"

using std::cout, std::endl; 

int WhichLineDifferent(const std::string& expected, const std::string& result) {
  std::istringstream iss_expected(expected);
  std::istringstream iss_result(result);

  for (int i = 0;; ++i) {
    std::string line_expected;
    std::string line_result;
    std::getline(iss_expected, line_expected, '\n');
    std::getline(iss_result, line_result, '\n');
    if (!iss_expected.good() || !iss_result.good()) {
      if (iss_expected.good() || iss_result.good()) {
        std::cout << "One of the texts has less lines than the other."
                  << std::endl;
        if (iss_expected.good()) {
          std::cout << "Expected is longer" << std::endl;
          std::cout << "With this line: \"" << line_expected << "\""
                    << std::endl;
        } else {
          std::cout << "Result is longer" << std::endl;
          std::cout << "With this line: \"" << line_result << "\"" << std::endl;
        }
        return i;
      }
      break;
    }
    if (line_expected != line_result) {
      std::cout << "This line from expected: \"" << line_expected << "\""
                << std::endl;
      std::cout << "Doesn't match this line from result: \"" << line_result
                << "\"" << std::endl;
      return i;
    }
  }
  return -1;
}

//g++ -std=c++17 -Wall -Werror main.cpp

int main() {
/*    RecipeApp ra;
  Recipe simple_pop("Simple Popcorn", 1);
  simple_pop.AddIngredient("1/4 cup unpopped popcorn");
  simple_pop.AddIngredient("1/4 teaspoon vegetable oil");
  simple_pop.AddIngredient("1/4 teaspoon salt");
  simple_pop.SetInstructions(R"***(Pop it!)***");

  Recipe apples("An Apple", 3);
  apples.AddIngredient("1-5/6 unit apple");
  apples.SetInstructions(R"***(Grab it!)***");

  ra.AddRecipe(simple_pop);
  ra.AddRecipe(apples);
  ra.AddIngredientToPantry("2 cup unpopped popcorn");
  ra.AddIngredientToPantry("4-7/8 unit apple");
  cout << ra << endl;

  Recipe r = ra.UseUpIngredient("1/2 cup unpopped popcorn");
  cout << "Using up apples" << endl;
  cout << r;*/
RecipeApp ra;
Recipe simple_pop("Simple Popcorn", 8);
simple_pop.AddIngredient("1/4 cup unpopped popcorn");
simple_pop.AddIngredient("  6-7/3 teaspoon vegetable oil");
simple_pop.AddIngredient("1/4 teaspoon salt");
simple_pop.SetInstructions(R"***(Pop it!)***");
	
Recipe apples("An Apple", 3);
apples.AddIngredient("2-1/16 unit apple");
apples.SetInstructions(R"***(Grab it!)***");
	
Recipe apple_pie("Apple Pie", 7);
apple_pie.AddIngredient("1 pound flour");
apple_pie.AddIngredient("3-1/2 teaspoon salt");
apple_pie.AddIngredient("3 unit apple");
apple_pie.SetInstructions(R"***(Bake it!)***");
	
ra.AddRecipe(simple_pop);
ra.AddRecipe(apples);
ra.AddRecipe(apple_pie);
	ra.AddIngredientToPantry("2 cup unpopped popcorn");
ra.AddIngredientToPantry("2 teaspoon salt");
ra.AddIngredientToPantry("4-7/8 unit apple");

std::ostringstream oss;

Recipe consume_apples = ra.UseUpIngredient("4 unit apple");
std::cout << consume_apples;
oss << consume_apples;

consume_apples.ChangeServings(82);
std::cout << consume_apples;
oss << consume_apples;
	
std::string amount_apples = consume_apples.IngredientInOneServing("apple");
std::cout << amount_apples << std::endl;
oss << amount_apples << std::endl;
	
//ASSERT_THROW(consume_apples.IngredientInOneServing("Apples"), std::invalid_argument);
	
/*	Recipe consume_salt = ra.UseUpIngredient("2 teaspoon salt");
	std::cout << consume_salt;
	oss << consume_salt;
	
	Recipe consume_popcorn = ra.UseUpIngredient("1/8 cup unpopped popcorn");
51	std::cout << consume_popcorn;
52	oss << consume_popcorn;
53	
54	std::string expected = R"***(Recipe for: An Apple
55	Serves 5
56	Ingredients:
57	3-7/16 unit apple
58	
59	Instructions:
60	Grab it!
61	
62	Recipe for: An Apple
63	Serves 82
64	Ingredients:
65	56-3/8 unit apple
66	
67	Instructions:
68	Grab it!
69	
70	11/16 unit apple
71	Recipe for: Apple Pie
72	Serves 4
73	Ingredients:
74	4/7 pound flour
75	2 teaspoon salt
76	1-5/7 unit apple
77	
78	Instructions:
79	Bake it!
80	
81	Recipe for: Simple Popcorn
82	Serves 4
83	Ingredients:
84	1/8 cup unpopped popcorn
85	4-1/6 teaspoon vegetable oil
86	1/8 teaspoon salt
87	
88	Instructions:
89	Pop it!
90	
91	)***";
92	ASSERT_EQ(expected, oss.str());
93	ASSERT_THROW(ra.UseUpIngredient("1/2 cup sugar");, std::invalid_argument);
94	
95	std::ostringstream oss2;
96	std::cout << "Post Use Up RecipeApp" << std::endl;
97	oss2 << "Post Use Up RecipeApp" << std::endl;
98	
99	std::cout << ra;
100	oss2 << ra;
101	
102	std::string expected2 = R"***(Post Use Up RecipeApp
103	Recipes in the app (ordered by name):
104	Recipe for: An Apple
105	Serves 3
106	Ingredients:
107	2-1/16 unit apple
108	
109	Instructions:
110	Grab it!
111	
112	Recipe for: Apple Pie
113	Serves 7
114	Ingredients:
115	1 pound flour
116	3-1/2 teaspoon salt
117	3 unit apple
118	
119	Instructions:
120	Bake it!
121	
122	Recipe for: Simple Popcorn
123	Serves 8
124	Ingredients:
125	1/4 cup unpopped popcorn
126	8-1/3 teaspoon vegetable oil
127	1/4 teaspoon salt
128	
129	Instructions:
130	Pop it!
131	
132	Ingredients in pantry (ordered by name):
133	4-7/8 unit apple
134	2 teaspoon salt
135	2 cup unpopped popcorn
136	)***";
137	ASSERT_EQ(expected2, oss2.str());
138	*/

  //cout << ra;
  
  //cout << std::setprecision(5) << turn_fraction_to_double("3-1/4") << endl;
  //std::cout << "Start" << std::endl;
  /*Recipe r("Microwave Popcorn", 3);
  r.AddIngredient("1/2 cup unpopped popcorn");
  r.AddIngredient("1 teaspoon vegetable oil");
  r.AddIngredient("1/2 teaspoon salt");
  r.SetInstructions(
      R"***(In a cup or small bowl, mix together the unpopped popcorn and oil. 
  Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt. 
    Fold the top of the bag over twice to seal in the ingredients. 

  Cook in the microwave at full power for 2 1/2 to 3 minutes, 
   or until you hear pauses of about 2 seconds between pops. 

  Carefully open the bag to avoid steam, and pour into a serving bowl. 
  From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/
  )***");

  std::cout << r << std::endl;

  std::ostringstream oss;
  oss << r;*/
/*  std::string expected = R"***(Recipe for: Microwave Popcorn
Serves 3
Ingredients:
1/2 cup unpopped popcorn
1 teaspoon vegetable oil
1/2 teaspoon salt

Instructions:
In a cup or small bowl, mix together the unpopped popcorn and oil.
Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt.
Fold the top of the bag over twice to seal in the ingredients.
Cook in the microwave at full power for 2 1/2 to 3 minutes,
or until you hear pauses of about 2 seconds between pops.
Carefully open the bag to avoid steam, and pour into a serving bowl.
From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/

)***";

  std::cout << expected << std::endl;

  WhichLineDifferent(oss.str(), expected);
  assert(oss.str() == expected);*/

/*  cout << r.IngredientInOneServing("unpopped popcorn") << endl;

  cout << "Changing servings to 6" << endl;
  r.ChangeServings(6);

  std::cout << r << std::endl;

  std::cout << "End" << std::endl;*/

}

/*int main_recipe_app() {
  RecipeApp ra;
  Recipe simple_pop("Simple Popcorn", 1);
  simple_pop.AddIngredient("1/4 cup unpopped popcorn");
  simple_pop.AddIngredient("1/4 teaspoon vegetable oil");
  simple_pop.AddIngredient("1/4 teaspoon salt");
  simple_pop.SetInstructions(R"***(Pop it!)***");

  Recipe apples("An Apple", 3);
  apples.AddIngredient("1-5/6 unit apple");
  apples.SetInstructions(R"***(Grab it!)***");

  ra.AddRecipe(simple_pop);
  ra.AddRecipe(apples);
  ra.AddIngredientToPantry("2 cup unpopped popcorn");
  ra.AddIngredientToPantry("4-7/8 unit apple");
  cout << ra << endl;

  Recipe r = ra.UseUpIngredient("10 unit apple");
  cout << "Using up apples" << endl;
  cout << r;

  cout << ra;
  return 0;
}*/

/*int main_recipe() {
  std::cout << "Start" << std::endl;
  Recipe r("Microwave Popcorn", 3);
  r.AddIngredient("1/2 cup unpopped popcorn");
  r.AddIngredient("1 teaspoon vegetable oil");
  r.AddIngredient("1/2 teaspoon salt");
  r.SetInstructions(
      R"***(In a cup or small bowl, mix together the unpopped popcorn and oil. 
  Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt. 
    Fold the top of the bag over twice to seal in the ingredients. 

  Cook in the microwave at full power for 2 1/2 to 3 minutes, 
   or until you hear pauses of about 2 seconds between pops. 

  Carefully open the bag to avoid steam, and pour into a serving bowl. 
  From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/
  )***");

  std::cout << r << std::endl;

  std::ostringstream oss;
  oss << r;
  std::string expected = R"***(Recipe for: Microwave Popcorn
Serves 3
Ingredients:
1/2 cup unpopped popcorn
1 teaspoon vegetable oil
1/2 teaspoon salt

Instructions:
In a cup or small bowl, mix together the unpopped popcorn and oil.
Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt.
Fold the top of the bag over twice to seal in the ingredients.
Cook in the microwave at full power for 2 1/2 to 3 minutes,
or until you hear pauses of about 2 seconds between pops.
Carefully open the bag to avoid steam, and pour into a serving bowl.
From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/

)***";

  std::cout << expected << std::endl;

  WhichLineDifferent(oss.str(), expected);
  assert(oss.str() == expected);

  cout << r.IngredientInOneServing("unpopped popcorn") << endl;

  cout << "Changing servings to 6" << endl;
  r.ChangeServings(6);

  std::cout << r << std::endl;

  std::cout << "End" << std::endl;*/
  //return 0;
  
//}