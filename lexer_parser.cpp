/*********************************************************


    Parser and Lexer By Salim Regragui
    Code free to use in free and commercial use :)

*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char one_word_actions[][50] = { "go","dance","look" }; //list of actions that need only one word after them
const char two_word_actions[][50] = { "take" }; //list of actions that need one or more words after them

const int one_word_array_size = 3; //number of elements in the one_word_actions array
const int two_word_array_size = 1; //number of elements in the two_word_actions array

typedef struct words words;

struct words{

    char word[50];
    words* next_word;

};

typedef struct tokens tokens;

struct tokens{
	
	char words_association[5][50];
	int number_of_words=0;
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

words* remove_exception_words(words* first_word){ //function that remove words that are not necessary for the parser
	
	words* t = first_word;
	
	while(strcmp(first_word->word,"to") == 0 || strcmp(first_word->word,"the") == 0 ||
	strcmp(first_word->word,"then") == 0 || strcmp(first_word->word,"and") == 0){//if the exception word is in the first word
		
		first_word = t->next_word; //crush value of the first word
		t = first_word;
		
	}
	
	
	while(t->next_word != NULL){ //if the next word is not null
		
		if(strcmp(t->next_word->word,"to") == 0 || strcmp(t->next_word->word,"the") == 0
		  || strcmp(t->next_word->word,"then") == 0 || strcmp(t->next_word->word,"and") == 0){ //if the next word is equal to an exception
			
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
	
	while(t != NULL){ //while the current word is not null
	
		word_type = search_type(t); //we determine in wich action array the word is or if it's in none
		
		if(word_type == 1){ //if the current word is an action that needs only one parameter
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
					
					t = t->next_word->next_word;
					
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
			
			strcpy(current_token->words_association[0],t->word); //we copy the word in the current token
			
			if(t->next_word != NULL){
				strcpy(current_token->words_association[1],t->next_word->word);//we copy the word after it in the token because go 
	 			current_token->number_of_words = 2;		  					   //has only one word needed to function
	 		}else{ // if the user didn"t enter something to do with an action exp("go" with nothing else)
				
				strcpy(first_token->words_association[0],"");
				strcpy(first_token->words_association[0],"Error");
				first_token->next_token = NULL;
				
				return first_token;
				
			}
			
			if(t->next_word->next_word != NULL){ //if there is a word after the item to pick (exp take sword from ground)
				
				if(strcmp(t->next_word->next_word->word,"from") == 0){ //if there is a place from where to pick
				
				
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
								
								t = t->next_word->next_word->next_word->next_word;
								
							}else{ // if the word after the association is null exp(we have "take sword from ground" after 
								  //this association there is no word so we set the pointer of next_token to null
								current_token->next_token = NULL; //we set the current tokens next token to NULL as it is the last word in the phrase
				
								return first_token; //we return the first token
								
							}
							
							
					}else{ //if the user specified from but without the place after it exp("take sword from" with nothing else
						
						current_token->next_token = NULL; //we set the current tokens next token to NULL as it is the last word in the phrase
				
						return first_token; //we return the first token
						
					}
			}else{ //if the word after the association (take/object) is not from
				tokens* new_token; //We create a new token for the next association of words
					
				if(t->next_word->next_word->next_word != NULL){
					
					new_token = (tokens*)malloc(sizeof(tokens)); //we create a new token
					new_token->next_token = NULL;
					
					t = t->next_word->next_word;
					
				}else{
					
					new_token = NULL;
					t = t->next_word->next_word;
					
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
	
	return first_token; //we return the first token of our list
	
}

void clean_words(words* first_word){ //function that optimises our application by clearing the memory from the used words
	
	words* t = first_word;
	
	while(t != NULL){
		
		free(t); //Release the memory used
		t = t->next_word;
		
	}
	
}

tokens* lexer(char phrase[150]){
	
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
	
	clean_words(first_word);
	
	tokens* k = first_token;
	
	int d=0;
	
	while(k != NULL){
		printf("\n\" ");
		
		while(d < k->number_of_words){
			
			printf("%s ",k->words_association[d]);
			d++;
		}
		printf("\"\n");
		k = k->next_token;
		d=0;
		
	}
    
    return first_token; //returns the first word of the list

}

char* parser(tokens* first_token){
	
	tokens* t = first_token;
	char result[150]=""; //the result we are gonna show to the player
	int first = 0;
	
	if(strcmp(t->words_association[0],"Error") == 0){
		
		strcpy(result,"You need to specify something to do with the action !");
		
	}else{
	
		while(t != NULL){
			
			if(strcmp(t->words_association[0],"go") == 0){ //if the word is go
				if(first == 0)
					strcat(result,"Oh you wanna go ");
				else
					strcat(result,"And then go ");
					
				strcat(result,t->words_association[1]);
				strcat(result,". ");
			}else if(strcmp(t->words_association[0],"take") == 0 && t->number_of_words == 2){ //if the action is take without a from
				if(first == 0)
					strcat(result,"Oh you wanna take the ");
				else
					strcat(result,"And then take the ");
					
				strcat(result,t->words_association[1]);
				strcat(result,". ");
				
			}else if(strcmp(t->words_association[0],"take") == 0 && t->number_of_words == 4){ //if the action is take with from
				if(first == 0)
					strcat(result,"Oh you wanna take the ");
				else
					strcat(result,"And then take the ");
					
				strcat(result,t->words_association[1]);
				strcat(result," from the ");
				strcat(result,t->words_association[3]);
				strcat(result,". ");
				
			}else if(strcmp(t->words_association[0],"dance") == 0){ //if the action is dance
				if(first == 0)
					strcat(result,"Oh you wanna dance the ");
				else
					strcat(result,"And then dance the ");
					
				strcat(result,t->words_association[1]);
				strcat(result,". ");
				
			}else if(strcmp(t->words_association[0],"look") == 0){
				
				if(first == 0)
					strcat(result,"Oh you wanna look ");
				else
					strcat(result,"And then look ");
					
				strcat(result,t->words_association[1]);
				strcat(result,". ");
				
				
			}
			first++;
			t = t->next_token;
			
		}
		
		if(strcmp(result,"") == 0)
			strcpy(result,"What the hell are you trying to do ?");
			
	}
		
	return result;
	
}

int main()
{
    char phrase[150];
    tokens* first_token;
    char response[150]="";
	
	printf("What do you want to do ? ");
	gets(phrase);
    first_token = lexer(phrase);
    strcpy(response,parser(first_token));
    printf("\n\nRESPONSE : ");
    puts(response);
    
    printf("\nWhat do you want to do ? ");
	gets(phrase);
    first_token = lexer(phrase);
    strcpy(response,parser(first_token));
    printf("\n\nRESPONSE : ");
    puts(response);

    return 0;
}

