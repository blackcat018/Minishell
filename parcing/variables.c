/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:20:25 by codespace         #+#    #+#             */
/*   Updated: 2025/05/14 01:29:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

void free_split(char **strs)
{
    int i;

    i = 0;
    while(strs[i])
    {
        free(strs[i]);
        i++;
    }
    free(strs);
}

char *expand_variables(char *str, char **envp)
{
    char *result = strdup(str);
    char *dollar;
    char *var_name;
    char *var_value;
    int i;
    
    while ((dollar = ft_strchr(result, '$')))
    {
        var_name = malloc(ft_strlen(dollar) + 1);
        i = 1;
        while (dollar[i] && dollar[i] != ' ' && dollar[i] != '$')
        {
            var_name[i-1] = dollar[i];
            i++;
        }
        var_name[i-1] = '\0';
        i = 0;
        var_value = NULL;
        while(envp[i++])
        {
            if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
                && envp[i][ft_strlen(var_name)] == '=')
            {
                var_value = envp[i] + ft_strlen(var_name) + 1;
                break;
            }
        }
        if(var_value)
        {
            size_t prefix_len = dollar - result;
            char *prefix = ft_strndup(result, prefix_len);
            char *suffix = dollar + ft_strlen(var_name) + 1;
            char *new_result = malloc(ft_strlen(prefix) + ft_strlen(var_value) + ft_strlen(suffix) + 1);
            if (!new_result)
                return NULL;
            ft_strlcpy(new_result, prefix, ft_strlen(new_result));
            ft_strlcat(new_result, var_value,ft_strlen(new_result));
            ft_strlcat(new_result, suffix,ft_strlen(new_result));
            free(result);
            free(prefix);
            free(var_name);
            result = new_result;
        }
        free(var_name);
    }
    return(result);
}
