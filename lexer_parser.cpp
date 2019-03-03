/*********************************************************


    Parser and Lexer By Salim Regragui
    Code free to use in free and commercial use :)

*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char one_word_actions[][50] = { "go","dance","look" }; //list of actions that need only one word after them
const char two_word_actions[][50] = { "take","get" }; //list of actions that need one or more words after them

const char two_word_actions_needed_word[][50] = {"from","from"}; //list of the words needed for the second part of the action to happen
                                                          //exemple : "take" needs the word "from" (Note: The word and the action need to have the
                                                          //same index in their respective array exemple("take" is index 0 and "from" is index 0)

const char exception_words[][50] = {"to","the","then","and"}; //list of exception words

const int one_word_array_size = 3; //number of elements in the one_word_actions array
const int two_word_array_size = 2; //number of elements in the two_word_actions array
const int exception_words_array_size = 4; //number of elements in the exception_words array

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

int search_type(words* word){ //function that determines if an action needs 1 word after it or more

	for(int i=0;i<one_word_array_size;i++){

		if(strcmp(word->word,one_word_actions[i]) == 0)
			return 1;

	}

	for(int j=0;j<two_word_array_size;j++){

		if(strcmp(word->word,two_word_actions[j]) == 0)
			return 2;

	}

	return 0;

}

int check_if_exception_word(words* word){ //function that checks if a word is an exception and therefore needs to be removed

	for(int i=0;i<exception_words_array_size;i++){

		if(strcmp(word->word,exception_words[i]) == 0)
			return 1;

	}

	return 0;

}

const char* get_needed_word(words* word){ //function that gets the word needed for the second part of a two_words action to work

    int index = 0;

    for(int j=0;j<two_word_array_size;j++){

		if(strcmp(word->word,two_word_actions[j]) == 0){
			index = j;
			break;
		}

	}

	return two_word_actions_needed_word[index];

}

char* remove_spaces(char phrase[300]){ //removing the spaces from the beginning of the phrase

    int index, i, j;

    index = 0;

    /* Find last index of whitespace character */
    while(phrase[index] == ' ' || phrase[index] == '\t' || phrase[index] == '\n')
    {
        index++;
    }


    if(index != 0)
    {
        /* Shift all trailing characters to its left */
        i = 0;
        while(phrase[i + index] != '\0')
        {
            phrase[i] = phrase[i + index];
            i++;
        }
        phrase[i] = '\0'; // Make sure that string is NULL terminated
    }

    return phrase;

}

words* remove_exception_words(words* first_word){ //function that remove words that are not necessary for the parser

	words* t = first_word;
	int is_exception;

	is_exception = check_if_exception_word(first_word);

	while(is_exception == 1){//if the exception word is in the first word

		first_word = t->next_word; //crush value of the first word
		t = first_word;
		is_exception = check_if_exception_word(first_word);

	}


	while(t->next_word != NULL){ //if the next word is not null

		is_exception = check_if_exception_word(t->next_word);

		if(is_exception == 1){ //if the next word is equal to an exception

			t->next_word = t->next_word->next_word; //we crush the next word's value by the word after it (exp: "go to left" => "go left")

		}else
			t = t->next_word; //if not we just continue the words

	}

	return first_word;

}

tokens* make_tokens(tokens* first_token,words* first_word){ //function that joins words that make sence together

	words* t = first_word;
	tokens* current_token = first_token;

	int word_type = 0;
	int one_action_at_least = 0; //checks if the phrase entered by the user contains at least one action.

	while(t != NULL){ //while the current word is not null

		word_type = search_type(t); //we determine in wich action array the word is or if it's in none

		if(word_type == 1){ //if the current word is an action that needs only one parameter

            one_action_at_least++; //the phrase contains an action

			if(t->next_word != NULL){ //if there is something to do with this action

				strcpy(current_token->words_association[0],t->word); //we copy the word in the current token

				if(t->next_word != NULL)
					strcpy(current_token->words_association[1],t->next_word->word);//we copy the word after it in the token because go
		 		current_token->number_of_words = 2;		  					   //has only one word needed to function

				tokens* new_token; //We create a new token for the next association of words

				if(t->next_word->next_word != NULL){ //if the word after the association is not null

					new_token = (tokens*)malloc(sizeof(tokens)); //we create a new token
					new_token->next_token = NULL;

					current_token->next_token = new_token; //we set the current tokens next token to the new token
					current_token = new_token; // and then we set the current token to the new token

					t = t = t->next_word;

				}else{ // if the word after the association is null exp(we have "go left" after this association is nothing so
					  //we set the pointer of new_token to null

					current_token->next_token = NULL; //we set the current tokens next token to NULL as it is the last word in the phrase

					return first_token; //we return the first token


				}

			}else{ // if the user didn"t enter something to do with an action exp("go" with nothing else)

				strcpy(first_token->words_association[0],"");
				strcpy(first_token->words_association[0],"Error");
				first_token->next_token = NULL;

				return first_token;

			}
		}else if(word_type == 2){//if the current word is an action that needs one or more parameters

		    one_action_at_least++; //the phrase contains an action

			strcpy(current_token->words_association[0],t->word); //we copy the word in the current token

			char needed_word[50] = "";
			strcpy(needed_word,get_needed_word(t)); //the word needed for the second part of the action to happen

			if(t->next_word != NULL){
				strcpy(current_token->words_association[1],t->next_word->word);//we copy the word after it in the token because go
	 			current_token->number_of_words = 2;		  					   //has only one word needed to function

	 		}else{ // if the user didn't enter something to do with an action exp("go" with nothing else)

				strcpy(first_token->words_association[0],"");
				strcpy(first_token->words_association[0],"Error");
				first_token->next_token = NULL;

				return first_token;

			}

			if(t->next_word->next_word != NULL){ //if there is a word after the item to pick (exp take sword from ground)

				if(strcmp(t->next_word->next_word->word,needed_word) == 0){ //if there is a word that specifies the second portion of the action


					if(t->next_word->next_word->next_word != NULL){

							tokens* new_token; //We create a new token for the next association of words

							strcpy(current_token->words_association[2],t->next_word->next_word->word);
							strcpy(current_token->words_association[3],t->next_word->next_word->next_word->word);
							current_token->number_of_words = 4;

							if(t->next_word->next_word->next_word->next_word != NULL){ //if the word after the association is not null

								new_token = (tokens*)malloc(sizeof(tokens)); //we create a new token
								new_token->next_token = NULL;

								current_token->next_token = new_token; //we set the current tokens next token to the new token
								current_token = new_token; // and then we set the current token to the new token

								t = t->next_word;

							}else{ // if the word after the association is null exemple(we have "take sword from ground" after
								  //this association there is no word so we set the pointer of next_token to null
								current_token->next_token = NULL; //we set the current tokens next token to NULL as it is the last word in the phrase

								return first_token; //we return the first token

							}


					}else{ //if the user specified the needed word but without something after it exp("take sword from" with nothing else)

						current_token->next_token = NULL; //we set the current tokens next token to NULL as it is the last word in the phrase

						return first_token; //we return the first token

					}
			}else{ //if the word after the association (two_word_action/object) is not the needed word
				tokens* new_token; //We create a new token for the next association of words

				if(t->next_word->next_word->next_word != NULL){//there is something after what we do

					new_token = (tokens*)malloc(sizeof(tokens)); //we create a new token
					new_token->next_token = NULL;

					t = t->next_word;

				}else{

					new_token = NULL;
					t = t->next_word;

				}

				current_token->next_token = new_token; //we set the current tokens next token to the new token
				current_token = new_token; // and then we set the current token to the new token

			}

			}else{ //if there is no word after the item to pick

				current_token->next_token = NULL; //we set the current tokens next token to NULL as it is the last word in the phrase

				return first_token; //we return the first token

			}


		}else{

			t = t->next_word;

		}

	}

	if(one_action_at_least > 0) //if the phrase contained at least one action
        return first_token; //we return the first token of our list

    else{ //if the user typed some gibberish without a single action

        printf("%s  |",current_token->words_association[0]);
        strcpy(first_token->words_association[0],"I don't understand");
        first_token->next_token = NULL;

        return first_token;

    }

}

void clean_words(words* first_word){ //function that optimises our application by clearing the memory from the used words

	words* t = first_word;

	while(t != NULL){

		free(t); //Release the memory used
		t = t->next_word;

	}

}

tokens* lexer(char phrase[300]){

    strcpy(phrase,remove_spaces(phrase));

    if(strcmp(phrase,"") == 0){ //if the user didn't type anything

        tokens* first_token = (tokens*)malloc(sizeof(tokens)); //we set our first token
        strcpy(first_token->words_association[0],"Empty");
        first_token->next_token = NULL;

        return first_token;

    }

	int i=0;
    words* first_word = (words*)malloc(sizeof(words));
    first_word->next_word = NULL;

    words* current_word = first_word; //this is a pointer that goes from the first word to the last

	char words_stocked[20][50];

    char* token = strtok(phrase," "); //gets the first word of the phrase before the delimiter


	while(token != NULL){ //while there a re still words

		strcpy(words_stocked[i],token); //copy the content of the token into the
		token = strtok(NULL," "); //gets the next word of the phrase before the delimiter
		i++; //increment the words_stocked counter

	}

    for(int j =0;j<i;j++){

    	if(j == 0) //if we are in the first word
    		strcpy(first_word->word , words_stocked[j]);
    	else{

    		words* new_word = (words*)malloc(sizeof(words)); //create a new word
	    	new_word->next_word = NULL;

	    	current_word->next_word = new_word; //we set the pointer of the current word's next to the new word
	    	strcpy(new_word->word,words_stocked[j]); //we copy from words stocked to the new element
	    	current_word = new_word;

		}

	}

	first_word = remove_exception_words(first_word); //we remove that words that are not needed by the parser

	tokens* first_token = (tokens*)malloc(sizeof(tokens)); //we set our first token
	first_token->next_token = NULL;
	first_token = make_tokens(first_token,first_word); //we transform our words into tokens

	clean_words(first_word); //remove the words typed from the memory

	tokens* k = first_token;

	int d=0;
	int action_counter = 1;

    printf("\n\nLIST OF ACTIONS THAT THE LEXER FOUND :\n");
	while(k != NULL){
		printf("\n\tAction %d : \" ",action_counter);

		if(strcmp(first_token->words_association[0],"I don't understand") == 0 || strcmp(first_token->words_association[0],"Error") == 0 ||
            strcmp(first_token->words_association[0],"Empty") == 0){ //if the user typed some gibberish that the parser don't understand

            printf("%s \"\n",first_token->words_association[0]);
            k = k->next_token;
            break;

		}else{ //if there is atleast one action in the phrase

            while(d < k->number_of_words){

                printf("%s ",k->words_association[d]);
                d++;
            }
            k = k->next_token;
            printf("\"\n");
            d=0;

		}

		action_counter++; //add's one to the actions found in the phrase

	}

    return first_token; //returns the first word of the list

}

void parser(tokens* first_token){

	tokens* t = first_token;
	int first = 0;

	if(strcmp(t->words_association[0],"Error") == 0){ //if there is an error in one of the actions

		printf("\t- You need to specify something to do with the action !\n");

	 }else if(strcmp(t->words_association[0],"Empty") == 0){ //if there is an error in one of the actions

        printf("\t- You need to put some actions in order for me to help you !\n");

	 }else if(strcmp(t->words_association[0],"I don't understand") == 0){ //if the parser didn't understand what the user wants to do

        printf("\t- I'm sorry but i don't understand what you're trying to do !\n");

	 }else{

		while(t != NULL){

			if(strcmp(t->words_association[0],"go") == 0){ //if the word is go

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna go to the ");
				else
					printf("\t- Then go to the ");

				printf("%s",t->words_association[1]);
				printf(".\n ");

			}else if(strcmp(t->words_association[0],"take") == 0 && t->number_of_words == 2){ //if the action is take without a from

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna take the ");
				else
					printf("\t- Then take the ");

				printf("%s",t->words_association[1]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"take") == 0 && t->number_of_words == 4){ //if the action is take with from

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna take the ");
				else
					printf("\t- Then take the ");

				printf("%s",t->words_association[1]);
				printf(" from the ");
				printf("%s",t->words_association[3]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"get") == 0 && t->number_of_words == 2){ //if the action is get without a from

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna get the ");
				else
					printf("\t- Then get the ");

				printf("%s",t->words_association[1]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"get") == 0 && t->number_of_words == 4){ //if the action is get with from

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna get the ");
				else
					printf("\t- Then get the ");

				printf("%s",t->words_association[1]);
				printf(" from the ");
				printf("%s",t->words_association[3]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"dance") == 0){ //if the action is dance

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna dance the ");
				else
					printf("\t- Then dance the ");

				printf("%s",t->words_association[1]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"look") == 0){

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna look ");
				else
					printf("\t- Then look ");

				printf("%s",t->words_association[1]);
				printf(". \n");

			}
			first++; //checks that this is not the first action done by the user
			t = t->next_token;

		}

	}

}

int main()
{
    char phrase[300];
    tokens* first_token;

	printf("What do you want to do ? ");
	gets(phrase);
    first_token = lexer(phrase);
    printf("\nRESPONSE OF THE PARSER : \n\n");
    parser(first_token);

    printf("\nWhat do you want to do ? ");
	gets(phrase);
    first_token = lexer(phrase);
    printf("\nRESPONSE OF THE PARSER : \n\n");
    parser(first_token);

    return 0;
}
