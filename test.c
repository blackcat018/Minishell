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

int single_quote_count(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == '\'')
			count ++;
		i++;
	}
	return(count);
}
int double_quote_count(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == '"')
			count ++;
		i++;
	}
	return(count);
}
int check_quotes(char *str)
{
	char *back;

	int (i), (flag), (len), (S_check), (D_check);
	i = 0;
	len = strlen(str) - 1;
	flag = 0;
	back = strdup(str);
	D_check = double_quote_count(str);
	S_check = single_quote_count(str);
	if((D_check %2 != 0) || (S_check %2 != 0))
		return(3);
	while(str[i])
	{
		if(str[i] == '\'')
		{
			while(back[len])
			{
				if(back[len] == '\'' && len != i)
					return(1);
				len--;
			}
		}
		if(str[i] == '"')
		{
			while(back[len])
			{
				if(back[len] == '"' && len != i)
					return(2);
				len--;
			}
		}
		i++;
	}
    return 0;
}

int main()
{
	char s[] = "hello'\"hello\" bro'words";

	int i = check_quotes(s);
	printf("%d\n",i);
	return (0);
}
