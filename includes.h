#ifndef INCLUDES_H
#define INCLUDES_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils/libft/libft.h"

typedef enum e_token_type {
    WORD,// chno bghit nchra7 raha word dafuq!
    PIPE, // |
	OPS, // >> , > , < , <<
    QUOTED_STRING,// "" or ''
	AND_IF, // &&
	OR_IF,   // ||
} e_token;

typedef struct s_token {
    char *value;
    e_token type;
    struct s_token *next;
} t_token;

typedef struct s_trs
{
	char *value;
	int type;
	struct s_trs *left;
	struct s_trs *right;
} t_trs;

t_token *create_token(e_token type, char *value);
void is_it_pipe(t_token **head, t_token **tail, int *i);
void is_it_op(t_token **head, t_token **tail, int *i, char *input);
void is_it_quote(t_token **head, t_token **tail, int *i, char *input, char c);
void is_it_word(t_token **head, t_token **tail, int *i, char *input);

#endif