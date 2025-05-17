#ifndef INCLUDES_H
#define INCLUDES_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils/libft/libft.h"

typedef enum {
    COMMAND,// done.          0
    CMD_ARG,//done            1
    BUILT_IN,//               2
    QUOTES,//delete or fix    3
    PIPE,//done               4
    AND,//done?               5
    OR,//done                 6
    REDIR_IN,//done           7
    REDIR_OUT,//done          8
    APPEND,//done             9
    HERE_DOC,//done           10
    FILE_NAME,//tbd           11
} NodeType;

typedef struct s_token {
    char *value;
    NodeType type;
    struct s_token *next;
} t_token;


typedef struct s_trs {
    char            **argv;
	char			*value;
	NodeType	    type;
    struct s_trs    *left;
    struct s_trs    *right;
} t_trs;

t_token *create_token(NodeType type, char *value);
void clear_tokens(t_token **head);
void print_tokens(t_token *tokens);
t_token *tokenizer(t_token **head, t_token **tail,char *input);

void add_arg(t_trs *node, char *value);
int is_operator(t_token *node);
t_trs *create_node(char *value);
char    *ft_strndup(const char *str, size_t n)
;

void is_it_pipe(t_token **head, t_token **tail, int *i,char *input);
void is_it_op(t_token **head, t_token **tail, int *i, char *input);
void is_it_quote(t_token **head, t_token **tail, int *i, char *input, char c);
void is_it_word(t_token **head, t_token **tail, int *i, char *input);
void is_it_and(t_token **head, t_token **tail, int *i, char *input);

#endif