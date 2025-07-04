/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:12:17 by moel-idr          #+#    #+#             */
/*   Updated: 2025/05/23 22:48:41 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

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

	int (i), (len), (S_check), (D_check);
	i = 0;
	len = strlen(str) - 1;
	back = ft_strdup(str);
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
		else if(str[i] == '"')
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
