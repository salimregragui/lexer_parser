#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

int search_type(words* word);
int check_if_exception_word(words* word);
const char* get_needed_word(words* word);
char* remove_spaces(char phrase[300]);
words* remove_exception_words(words* first_word);
tokens* make_tokens(tokens* first_token,words* first_word);
void clean_words(words* first_word);
void clean_tokens(tokens* first_token);
tokens* lexer(char phrase[300]);

#endif // LEXER_H_INCLUDED
