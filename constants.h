#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

const char one_word_actions[][50] = { "go","dance","look" }; //list of actions that need only one word after them (exemple "go" only needs a direction)
const char two_word_actions[][50] = { "take","get" }; //list of actions that need one or more words after them (exemple "take" can be used with only an
                                                      //item "take sword" or we can specify from where to take it "take sword from the ground"

const char two_word_actions_needed_word[][50] = {"from","from"}; //list of the words needed for the second part of the action to happen
                                                          //exemple : "take" needs the word "from" (Note: The word and the action need to have the
                                                          //same index in their respective array exemple("take" is index 0 and "from" is index 0)

const char exception_words[][50] = {"to","the","then","and","after","that"}; //list of exception words that are not needed by the parser to understand

const int one_word_array_size = 3; //number of elements in the one_word_actions array
const int two_word_array_size = 2; //number of elements in the two_word_actions array
const int exception_words_array_size = 6; //number of elements in the exception_words array

typedef struct words words;

struct words{

    char word[50];
    words* next_word;

};

typedef struct tokens tokens;

struct tokens{

	char words_association[5][50];
	int number_of_words;
	tokens* next_token;

};


#endif // CONSTANTS_H_INCLUDED
