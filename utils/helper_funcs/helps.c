/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:34:19 by codespace         #+#    #+#             */
/*   Updated: 2025/05/14 01:02:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	size_t	len;
	char	*dup;
    
	len = ft_strlen(str);
	if (n < len)
		len = n;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

t_token *create_token(NodeType type, char *value)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if(!new_token)
        return(NULL);
    new_token->value = ft_strdup(value);
    new_token->type = type;
    new_token->next = NULL;
    return(new_token);
}
t_trs *create_node(char *value)
{
    t_trs   *new_node;

    new_node = malloc(sizeof(t_trs));
     if(!new_node)
        return(NULL);
    new_node->value = ft_strdup(value);
    new_node->right = NULL;
    new_node->left = NULL;
    return(new_node);
}

int is_operator(t_token *node)
{
    return(node->type == PIPE);
}

void add_arg(t_trs *node, char *value)
{
    char    **new_arg;

    int (i), (j);
    i = 0;
    j = 0;
    if(node->argv)
    {
        while (node->argv[i])
            i++;
    }
    new_arg = malloc(sizeof(char) * (i + 2));
    if(!new_arg)
        exit(1);
    while (j < i)
    {
        new_arg[j] = node->argv[j];
        j++;
    }
    new_arg[i] = ft_strdup(value);
    new_arg[i + 1] = NULL;
    if(node->argv)
        free(node->argv);
    node->argv = new_arg;
}
