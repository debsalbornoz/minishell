/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/30 18:13:27 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_single_quote(char	*input, char sig_quote);
static char	*process_heredoc(char signal, char *input);
// static char	*find_var_name(t_list *lst_env, char *input, char *position);
// static char	*find_var_value(t_list *lst_env, char *name);
// static char	*update_expand(char *temp1, char *temp2, char *input);

char	*expand(t_list *lst_env, char *input)
{
	char	*temp;
	char	sig_quote;

	(void)lst_env;
	temp = input;
	while (*temp)
	{
		sig_quote = process_quotes(sig_quote, *temp);
		if (is_single_quote(sig_quote))
			temp = process_single_quote(temp, sig_quote);
		else if (!is_double_quote(sig_quote))
			temp = process_heredoc(sig_quote, temp);
		else
		 	temp++;
	}
	return (input);
}

static char	*process_single_quote(char	*input, char sig_quote)
{
	char	*temp;

	temp = input;
	while (*temp++ && is_single_quote(sig_quote))
		sig_quote = process_quotes(sig_quote, *(temp + 1));
	return (temp);
}

static char	*process_heredoc(char signal, char *input)
{
	if (*input == '<' && *(input + 1) == '<')
	{
		input++;
		input++;
		input = trim_start_spaces(input);
		while (!signal && *input && !is_space(*input))
			input++;
	}
	return (input);
}

// char	*expand(t_list *lst_env, char *input)
// {
// 	char	*temp1;
// 	char	*temp2;
// 	char	sig_quote;

// 	if (!input)
// 		return (NULL);
// 	temp1 = input;
// 	sig_quote = 0;
// 	while (*temp1)
// 	{
// 		temp2 = temp1;
// 		sig_quote = process_quotes(sig_quote, *temp1);
// 		if (!is_single_quote(sig_quote))
// 		{
// 			if (is_double_quote(sig_quote))
// 				temp1 = find_var_name(lst_env, input, temp1);
// 			else
// 			{
// 				temp1 = process_heredoc(sig_quote, temp1);
// 				if (ft_strcmp(temp1, temp2))
// 					temp2 = temp1;
// 				temp1 = find_var_name(lst_env, input, temp1);
// 			}
// 		}
// 		temp1 = update_expand(temp1, temp2, input);
// 	}
// 	return (input);
// }


// static char	*find_var_name(t_list *lst_env, char *input, char *position)
// {
// 	char	*temp;
// 	char	*var_name;
// 	char	*var_value;

// 	temp = position;
// 	var_name = 0;
// 	var_value = 0;
// 	if (*temp == '$')
// 	{
// 		temp++;
// 		while (*temp && (ft_isalnum(*temp) || *temp == '_' || *temp == '?'))
// 			var_name = ft_chrjoin(var_name, *temp++);
// 		if (var_name)
// 			var_value = find_var_value(lst_env, var_name);
// 		temp = var_expand(input, position, var_name, var_value);
// 	}
// 	if (var_name)
// 		free(var_name);
// 	return (temp);
// }

// static char	*find_var_value(t_list *lst_env, char *name)
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

// char	*update_expand(char *temp1, char *temp2, char *input)
// {
// 	if (ft_strcmp(temp1, temp2))
// 	{
// 		free(input);
// 		input = temp1;
// 	}
// 	else
// 		return (++temp1);
// 	return (input);
// }
