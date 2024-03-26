/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/26 11:31:54 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_heredoc(char signal, char *input);
static char	*find_var_name(t_list *lst_env, char *input, char *position);
static char	*find_var_value(t_list *lst_env, char *name);
static char	*var_expand(char *input, char *position, char *name, char *value);

char	*find_varible(t_list *lst_env, char *input)
{
	char	*temp;
	char	signal_quote;
	int		signal_heredoc;

	temp = input;
	signal_quote = 0;
	signal_heredoc = 0;
	while (*temp)
	{
		signal_quote = process_quotes(signal_quote, *temp);
		if (!is_single_quote(signal_quote))
		{
			if (is_double_quote(signal_quote))
				temp = find_var_name(lst_env, input, temp);
			else
			{
				temp = process_heredoc(signal_quote, temp);
				return (find_var_name(lst_env, input, temp));
			}
		}
		temp++;
	}
	temp = 0;
	return (input);
}

static char	*process_heredoc(char signal, char *input)
{
	if (*input == '<' && *(input + 1) == '<')
	{
		input++;
		input++;
		input = trim_start_spaces(input);
		while (!signal && *(input + 1) && !is_space(*(input + 1)))
			input++;
	}
	return (input);
}

static char	*find_var_name(t_list *lst_env, char *input, char *position)
{
	char	*temp;
	char	*var_name;
	char	*var_value;

	temp = position;
	var_name = 0;
	var_value = 0;
	if (*temp == '$')
	{
		temp++;
		while (*temp && (ft_isalnum(*temp) || *temp == '_'))
			var_name = ft_chrjoin(var_name, *temp++);
		if (var_name)
			var_value = find_var_value(lst_env, var_name);
		temp = var_expand(input, position, var_name, var_value);
	}
	if (var_name)
		free(var_name);
	return (temp);
}

static char	*find_var_value(t_list *lst_env, char *name)
{
	if (lst_env->node)
	{
		lst_env->node = lst_env->head;
		while (lst_env->node && lst_env->node->next)
		{
			if (!ft_strcmp(lst_env->node->data->env->name, name))
				return (lst_env->node->data->env->value);
			lst_env->node = lst_env->node->next;
		}
		if (!ft_strcmp(lst_env->node->data->env->name, name))
			return (lst_env->node->data->env->value);
	}
	return (0);
}

static char	*var_expand(char *input, char *position, char *name, char *value)
{
	char	*res;
	char	*temp;

	res = ft_calloc(1, ft_strlen(input) - ft_strlen(name) + ft_strlen(value));
	temp = res;
	while (*input != *position)
		*temp++ = *input++;
	while (*value)
		*temp++ = *value++;
	input++;
	while (*input == *name)
	{
		input++;
		name++;
	}
	while (*input)
		*temp++ = *input++;
	temp = 0;
	return (res);
}
