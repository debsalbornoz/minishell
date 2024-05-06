/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:21:12 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/06 14:47:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*data_env_addr(void)
{
	static t_list	lst_env;

	lst_env.node = 0;
	return (&lst_env);
}
t_list	*create_env_list(char **envp, t_list *env_lst)
{
	while (*envp)
	{
		env_lst = add_node(env_lst);
		env_lst->node->data = ft_calloc(1, sizeof(union u_data));
		env_lst->node->data->env = ft_calloc(1, sizeof(t_env));
		env_lst->node->data->env->name = get_envp_name(*envp);
		env_lst->node->data->env->value = get_envp_value(*envp);
		envp++;
	}
	return (env_lst);
}

char	*get_envp_name(char *envp)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] != '=' && envp[i] != '\0')
		i++;
	name = ft_calloc((i + 1), sizeof(char));
	ft_strlcpy(name, envp, i + 1);
	return (name);
}

char	*get_envp_value(char *envp)
{
	char	*value;
	int		i;
	int		begin;

	i = 0;
	value = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] != '=' && envp[i] != '\0')
		i++;
	if (envp[i] == '=')
		i++;
	begin = i;
	while (envp[i] != '\0')
		i++;
	value = ft_calloc((i - begin + 1), sizeof(char));
	ft_strlcpy(value, &envp[begin], i - begin + 1);
	return (value);
}
