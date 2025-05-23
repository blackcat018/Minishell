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


int check_quotes(const char *str)
{
	int i;
	int flag;
	int len;
	char *back;

	i = 0;
	len = strlen(str) - 1;
	flag = 0;
	back = strdup(str);
	while(str[i])
	{
		if(str[i] == '\'')
			break;
		i++;
	}
    return 0;
}

int main()
{
	char s[] = "hello\"hello bro\"words";

	int i = check_quotes(s);
	printf("%d\n",i);
	return (0);
}
