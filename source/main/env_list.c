/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:21:12 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/16 14:21:36 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_list	*make_env_list(char **envp, t_env_list *env_list)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i] != NULL)
	{
		name = find_name(envp[i]);
		value = find_value(envp[i]);
		add_env_node(env_list, name, value);
		free(name);
		free(value);
		i++;
	}
	return (env_list);
}

char	*find_name(char *envp)
{
	char	*temp;
	int		i;

	i = 0;
	while (envp[i] != '=')
		i++;
	temp = ft_calloc((i + 1), sizeof(char));
	ft_strlcpy(temp, envp, i + 1);
	return (temp);
}

char	*find_value(char *envp)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (envp[i] != '=')
		i++;
	if (envp[i] == '=')
		i++;
	j = i;
	while (envp[i] != '\0')
		i++;
	temp = ft_calloc((i - j + 1), sizeof(char));
	ft_strlcpy(temp, &envp[j], i - j + 1);
	return (temp);
}
