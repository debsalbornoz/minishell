/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:21:12 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/23 14:59:03 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*make_lst_env(char **envp)
{
	t_list	*lst_env;

	lst_env = ft_calloc(1, sizeof(t_list));
	lst_env->node = NULL;
	while (*envp)
	{
		lst_env = add_node(lst_env);
		lst_env->node->data = ft_calloc(1, sizeof(union u_data));
		lst_env->node->data->env = ft_calloc(1, sizeof(t_env));
		lst_env->node->data->env->name = find_name(*envp);
		lst_env->node->data->env->value = find_value(*envp);
		envp++;
	}
	return (lst_env);
}

char	*find_name(char *envp)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (envp)
	{
		while (envp[i] != '=' && envp[i] != '\0')
		i++;
	temp = ft_calloc((i + 1), sizeof(char));
		ft_strlcpy(temp, envp, i + 1);
	}
	return (temp);
}

char	*find_value(char *envp)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	temp = NULL;
	if (*envp)
	{
		while (envp[i] != '=' && envp[i] != '\0')
			i++;
		if (envp[i] == '=')
			i++;
		j = i;
		while (envp[i] != '\0')
			i++;
		temp = ft_calloc((i - j + 1), sizeof(char));
		ft_strlcpy(temp, &envp[j], i - j + 1);
	}
	return (temp);
}

t_node	*print_lst_env(t_node *node)
{
	printf("%s = %s\n", node->data->env->name, node->data->env->value);
	return (node);
}
