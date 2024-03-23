/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/22 18:52:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*process_heredoc(char signal, char *input);
char	*find_variable_name(t_list *lst_env, char *input, char *position);
char	*concatenation_chr(char *dest, char src);

char  *find_varible(t_list *lst_env, char *input)
{
	char	*temp;
	char	signal_quote;
	int		*signal_heredoc;

	temp = input;
	signal_quote = 0;
	signal_heredoc = 0;
	while (*temp)
	{
		signal_quote = process_quotes(signal_quote, *temp);
		if (!is_single_quote(signal_quote))
		{
			if (is_double_quote(signal_quote))
				temp = find_variable_name(lst_env, input, temp);
			else
			{
				temp = process_heredoc(signal_quote, temp);
				temp = find_variable_name(lst_env, input, temp);
			}
		}
		temp++;
	}
	temp = 0;
	return (input);
}

char	*process_heredoc(char signal, char *input)
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

char	*find_variable_name(t_list *lst_env, char *input, char *position)
{
	char	*temp;
	char	*variable_name;

	variable_name = 0;
	temp = position;
	if (*temp == '$')
	{
		temp++;
		while (*temp && (ft_isalnum(*temp) || *temp == '_'))
			variable_name = concatenation_chr(variable_name, *temp++);
	}
	if (variable_name)
		free(variable_name);
	return (input);
}

char	*concatenation_chr(char *dest, char src)
{
	char	*temp;

	temp = 0;
	if (!dest)
	{
		temp = ft_calloc(2, sizeof(char));
		*temp = src;
		return (temp);
	}
	temp = ft_calloc(1, ft_strlen(dest) + 2);
	while(*dest)
		*temp++ = *dest++;
	*temp = src;
	return (temp);
}

char	*expand(t_list *lst_env, char *name, char *input)
{
	return (input);
}
