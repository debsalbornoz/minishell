/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:21:12 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/17 13:32:38 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*make_env_list(char **envp, t_list *env_list)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i] != NULL)
	{
		name = find_name(envp[i]);
		value = find_value(envp[i]);
		add_node(env_list);
		env_list->node->data->name = ft_strdup(name);
		env_list->node->value = ft_strdup(value);
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

void	print_env_list(t_node *variable)
{
	printf("%s = %s\n", variable->data->name, variable->value);
}
