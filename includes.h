#ifndef INCLUDES_H
#define INCLUDES_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils/libft/libft.h"
#include <sys/types.h>
#include <dirent.h>

#define REDD     "\033[0;101m"
#define WHITE     "\033[0;7m"
#define GREEN	"\033[0;42m"
#define RED     "\033[0;95m"
#define YELLOW  "\033[0;33m"
#define SKYBLUE "\033[0;36m"
#define RESET   "\033[0m"

// int g_exit_status;

typedef enum {
    COMMAND,// done.          0
    CMD_ARG,//done            1
	OR,
	AND,
	SINGL_QU,//               4
	DOUBLE_QU,//			  5
    PIPE,//done               6               8
    REDIR_IN,//done           9
    REDIR_OUT,//done          10
    APPEND,//done             11
    HERE_DOC,//done           12
    FILE_NAME,//tbd
	VAR,           
	QUOTED_VAR,
    CONCATENATED_VAR,
} NodeType;

typedef struct s_token {
    char *value;
     char *var_nam;
    NodeType type;
	int quote_flag;
    struct s_token *next;
} t_token;

typedef struct s_exit
{
     int exit_status;
}t_exit;

typedef struct s_ctx
{
    int i;
    int j;
    int in_single;
    int in_double;
	int len;
    t_exit exit;
}   t_ctx;

typedef struct s_cmd
{
	char **argv;
	char **redirect;
	char **file;
	struct s_cmd *next;
}t_cmd;

int is_space_unquoted(char *str, int index);

void free_split(char **strs);
int red_flag(t_token *token);
void free_token_list(t_token *token);
int token_has_quotes(t_token *token);
t_token *handel_wild_card(t_token *xpnd);
void clear_cmd(t_cmd **head);
// int check_quotes(char *str);
// void err_handle(t_token *xpnd, char **envp); tf were you thinking!

void	print_system_error(char *context);
void	print_command_error(char *cmd, char *error_msg);
void	print_syntax_error(char *token);
void	print_file_error(char *filename);
void	print_ambiguous_redirect(char *var_name);
void	print_cmd_not_found(char *cmd);
t_token *expanding_it(t_token *token, char **env);

void append_list(t_token **head, t_token *new_node);

char *strip_token(char *value);

int pipe_err(t_token **list);
int	is_token_redirect(t_token *R);
int is_it_doubled(t_token *dollar);
t_token *stripper(t_token *xpnd);

t_token	*create_token(NodeType type, char *value, char *var_nam);
void clear_tokens(t_token **head);
void print_tokens(t_token *tokens);
t_token *tokenizer(t_token **head, t_token **tail,char *input);
t_cmd *store_cmds(t_token *token);
t_token *expand_variables(t_token *tokens, char **envp);
t_cmd *build_cmd_list(t_token *token);

int is_it_singled(t_token *dollar);

// void add_arg(t_trs *node, char *value);
// int is_operator(t_token *node);
// t_trs *create_node(char *value);
// char    *ft_strndup(const char *str, size_t n);

void is_it_and(t_token **head, t_token **tail, int *i, char *input);
void is_it_pipe(t_token **head, t_token **tail, int *i,char *input);
void is_it_op(t_token **head, t_token **tail, int *i, char *input);
void is_it_quote(t_token **head, t_token **tail, int *i, char *input, char c);
void is_it_word(t_token **head, t_token **tail, int *i, char *input);
int make_full_token(char *input, int len, int start, t_token **new);
void get_full_quote(char *input, int* i, int *in_q, char *type, int *len);
// void is_it_and(t_token **head, t_token **tail, int *i, char *input);

int	is_token_cmd(t_token *T);
int	is_token_redirect(t_token *R);
int is_it_opp(t_token *op);
int is_token_breaker(char c);
int is_empty_string(t_token *token);
int redir_check (t_token *token);

char	*replace_in_quotes(char *str, char **env);
char	*strip_str(char *str);
char *handle_double(t_token *token, char **env);
char *expand(t_token *tokens, char **env);
char *replace_in_arg(char *str, char **env);
int is_it_var(char *str);
char *var_name(char *str);
char *get_env_value(char *name, char **env);
int double_dollars(char *result, int j);
int handle_token(t_token *xpnd, t_token **result, t_token *prev);
int split_var_token(t_token *xpnd, t_token **result);
char	*remove_quotes(char *value);
int copy_token(t_token *xpnd, t_token **result);
#endif