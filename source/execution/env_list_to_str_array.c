/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_str_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/29 12:19:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_list_to_str_array(t_list *lst_env)
{
	char	**envp;
	int		i;
	int		nodes;
	t_node	*aux;

	if (!lst_env)
		return (NULL);
	i = 0;
	aux = lst_env->head;
	nodes = count_nodes(lst_env);
	aux = lst_env->head;
	envp = ft_calloc(nodes + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (aux)
	{
		envp[i] = concatenate(aux->data->env->name,
				aux->data->env->value);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	aux = lst_env->head;
	return (envp);
}

char	*concatenate(char *s1, char *s2)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	temp = ft_calloc(len, sizeof(char));
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '=';
	i++;
	while (s2[j] != '\0')
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix || !*matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
