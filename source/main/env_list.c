/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:21:12 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/26 20:22:30 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*make_lst_env(char **envp)
{
	t_list	*lst_env;

	lst_env = ft_calloc(1, sizeof(t_list));
	if (!lst_env)
		return (NULL);
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
	if(!envp)
		return (NULL);
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
	if(!envp)
		return (NULL);
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

char	**list_to_matrix(t_list *lst_env)
{
	int counter;
	char	**env;
	int i;
	int len;

	i = 0;
	counter = 0;
	len = 0;
	if(!lst_env)
		return(NULL);
	counter = count_nodes(lst_env);
	lst_env->node = lst_env->head;
	//precisa dar free
	env = ft_calloc(counter + 1, sizeof(char *));
	if (!env)
		return (NULL);
	while(lst_env->node)
	{
		len = ft_strlen(lst_env->node->data->env->name) +  ft_strlen(lst_env->node->data->env->value) + 2;
		//precisa dar free
		env[i] = ft_calloc(len, sizeof(char));
		if(!env[i])
			return (NULL);
		env[i] = concatenate(lst_env->node->data->env->name, lst_env->node->data->env->value);
		i++;
		lst_env->node = lst_env->node->next;
	}
	lst_env->node = lst_env->head;
	return (env);
}

int count_nodes(t_list *lst_env)
{
	int i;

	i = 0;
	lst_env->node = lst_env->head;

	while(lst_env->node)
	{
		i++;
		lst_env->node = lst_env->node->next;
	}
	return (i);
}

char *concatenate(char *s1, char *s2)
{
	char *temp;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	//precisa dar free
	temp = ft_calloc(len, sizeof(char));
	while(s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '=';
	i++;
	while(s2[j] != '\0')
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

void free_matrix(char **envp)
{
	int i;

	i = 0;
	if(!envp || !*envp)
		return;
	while(envp[i] != NULL)
	{
		free(envp[i]);
		i++;	
	}
	free(envp);
}