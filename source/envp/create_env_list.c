/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:21:12 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/16 19:38:32 by dlamark-         ###   ########.fr       */
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
	if (!envp || !*envp)
		return (NULL);
	while (*envp)
	{
		env_lst = add_node(env_lst);
		env_lst->node->data = ft_calloc(1, sizeof(union u_data));
		env_lst->node->data->env = ft_calloc(1, sizeof(t_env));
		env_lst->node->data->env->name = get_envp_name(*envp);
		env_lst->node->data->env->value = get_envp_value(*envp);
		envp++;
	}
	env_lst->node = env_lst->head;
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
	if (i > 0)
	{
		name = ft_calloc((i + 1), sizeof(char));
		ft_strlcpy(name, envp, i + 1);
	}
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

t_list	*add_new_node(t_list *lst_env, char *name, char *value)
{
	lst_env = add_node(lst_env);
	lst_env->node->data = ft_calloc(1, sizeof(union u_data));
	lst_env->node->data->env = ft_calloc(1, sizeof(t_env));
	lst_env->node->data->env->name = ft_strdup(name);
	if (value)
		lst_env->node->data->env->value = ft_strdup(value);
	else
		lst_env->node->data->env->value = 0;
	return (lst_env);
}
