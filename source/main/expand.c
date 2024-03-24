/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/23 14:35:30 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// char	*process_heredoc(char signal, char *input);
// char	*find_variable_name(t_list *lst_env, char *input, char *position);
// char	*chrjoin(char *dest, char src);
// char	*find_variable_value(t_list *lst_env, char *name);
// int		ft_strcmp(char	*str1, char *str2);
// char	*variable_expand(char *input, char *position, char *name, char *value);

// char	*find_varible(t_list *lst_env, char *input)
// {
// 	char	*temp;
// 	char	signal_quote;
// 	//int		*signal_heredoc;

// 	temp = input;
// 	signal_quote = 0;
// 	signal_heredoc = 0;
// 	while (*temp)
// 	{
// 		signal_quote = process_quotes(signal_quote, *temp);
// 		if (!is_single_quote(signal_quote))
// 		{
// 			if (is_double_quote(signal_quote))
// 				temp = find_variable_name(lst_env, input, temp);
// 			else
// 			{
// 				temp = process_heredoc(signal_quote, temp);
// 				temp = find_variable_name(lst_env, input, temp);
// 			}
// 		}
// 		temp++;
// 	}
// 	temp = 0;
// 	return (input);
// }

// char	*process_heredoc(char signal, char *input)
// {
// 	if (*input == '<' && *(input + 1) == '<')
// 	{
// 		input++;
// 		input++;
// 		input = trim_start_spaces(input);
// 		while (!signal && *(input + 1) && !is_space(*(input + 1)))
// 			input++;
// 	}
// 	return (input);
// }

// char	*find_variable_name(t_list *lst_env, char *input, char *position)
// {
// 	char	*temp;
// 	char	*variable_name;
// 	char	*variable_value;

// 	temp = position;
// 	variable_name = 0;
// 	variable_value = 0;
// 	if (*temp == '$')
// 	{
// 		temp++;
// 		while (*temp && (ft_isalnum(*temp) || *temp == '_'))
// 			variable_name = chrjoin(variable_name, *temp++);
// 		if (variable_name)
// 			variable_value = find_variable_value(lst_env, variable_name);
// 		temp = variable_expand(input, position, variable_name, variable_value);
// 	}
// 	if (variable_name)
// 		free(variable_name);
// 	return (input);
// }

// char	*chrjoin(char *dest, char src)
// {
// 	char	*temp;

// 	temp = 0;
// 	if (!dest)
// 	{
// 		temp = ft_calloc(2, sizeof(char));
// 		*temp = src;
// 		return (temp);
// 	}
// 	temp = ft_calloc(1, ft_strlen(dest) + 2);
// 	while (*dest)
// 		*temp++ = *dest++;
// 	*temp = src;
// 	return (temp);
// }

// char	*find_variable_value(t_list *lst_env, char *name)
// {
// 	if (lst_env->node)
// 	{
// 		lst_env->node = lst_env->head;
// 		while (lst_env->node && lst_env->node->next)
// 		{
// 			if (!ft_strcmp(lst_env->node->data->env->name, name))
// 				return (lst_env->node->data->env->value);
// 			lst_env->node = lst_env->node->next;
// 		}
// 		if (!ft_strcmp(lst_env->node->data->env->name, name))
// 			return (lst_env->node->data->env->value);
// 	}
// 	return (0);
// }

// int	ft_strcmp(char	*str1, char *str2)
// {
// 	while (*str1 && *str2)
// 	{
// 		if (*str1++ != *str2++)
// 			return ((unsigned char)*str1 - (unsigned char)*str2);
// 	}
// 	return (0);
// }

// char	*variable_expand(char *input, char *position, char *name, char *value)
// {
// 	char	*res;
// 	char	*temp;

// 	res = ft_calloc(1, ft_strlen(input) - ft_strlen(name) + ft_strlen(value));
// 	temp = res;
// 	while (*(input + 1) != *position)
// 		*temp++ = *input++;
// 	while (*value)
// 		*temp++ = *value++;
// 	input++;
// 	while (*input == *name)
// 		input++;
// 	while (*input)
// 		*temp++ = *input++;
// 	temp = 0;
// 	return (res);	
// }
