void show_list_of_actions(){ //function that shows all the actions that the user can do

    printf("\nHERE IS A LIST OF ALL THE ACTIONS AVAILABLE : \n");

    for(int i=0;i<one_word_array_size;i++){

		printf("\t%s\n",one_word_actions[i]);

	}

	for(int j=0;j<two_word_array_size;j++){

		printf("\t%s\n",two_word_actions[j]);

	}

}

void parser(tokens* first_token){

	tokens* t = first_token;
	int first = 0; //if it's the first action (only needed for better text output

    if(strcmp(t->words_association[0],"Empty") == 0){ //if there is an error in one of the actions

        printf("\t- You need to put some actions in order for me to help you !\n");

	 }else if(strcmp(t->words_association[0],"I don't understand") == 0){ //if the parser didn't understand what the user wants to do

        printf("\t- I'm sorry but i don't understand what you're trying to do !\n");

	 }else if(strcmp(t->words_association[0],"list") == 0){ //if the user wanted to see the list of actions available

        show_list_of_actions();

	 }else if(strcmp(t->words_association[0],"help") == 0){ //if the user wanted to see help

        if(strcmp(t->words_association[1],"") == 0){ //if the user typed help with nothing else

            printf("\thelp : This function gives you information on how to use an action.");
            printf("\t\t- how to use : help 'action' (exemple : help go)\n");

        }else{

            int word_type = search_type(t->words_association[1]); //check if the word after help is an action.

            if(word_type == 0){ //if the word after help is not an action

                printf("\thelp : I'm sorry but this action is unknown to me right now.\n");

            }else{

                if(strcmp(t->words_association[1],"go") == 0){

                    printf("\n\tgo : This action allows you to go to a certain place or direction.");
                    printf("\t\t- how to use : go 'place' (exemple : go left)\n");

                }

            }

        }

     }else{

		while(t != NULL){

			if(strcmp(t->words_association[0],"go") == 0){ //if the word is go

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna go to the ");
				else
					printf("\t- After that go to the ");

				printf("%s",t->words_association[1]);
				printf(".\n ");

			}else if(strcmp(t->words_association[0],"take") == 0 && t->number_of_words == 2){ //if the action is take without a from

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna take the ");
				else
					printf("\t- After that take the ");

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
					printf("\t- After that get the ");

				printf("%s",t->words_association[1]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"get") == 0 && t->number_of_words == 4){ //if the action is get with from

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna get the ");
				else
					printf("\t- After that get the ");

				printf("%s",t->words_association[1]);
				printf(" from the ");
				printf("%s",t->words_association[3]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"dance") == 0){ //if the action is dance

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna dance the ");
				else
					printf("\t- After that dance the ");

				printf("%s",t->words_association[1]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"look") == 0){

				if(first == 0) //if this is the first action of the list
					printf("\t- You wanna look ");
				else
					printf("\t- After that look ");

				printf("%s",t->words_association[1]);
				printf(". \n");

			}else if(strcmp(t->words_association[0],"Error") == 0){ //if there is an error in one of the actions

                printf("\t- You didn't specify what you wanted to do with the action \"%s\" so i couldn't execute it.\n",t->words_association[1]);

            }
			first++; //checks that this is not the first action done by the user
			t = t->next_token;

		}

	}

	clean_tokens(first_token);

}
