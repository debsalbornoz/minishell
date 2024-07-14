/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/06/15 22:55:21 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_operator(char c);
int	value_len(char *value);

char	*process_dollar(t_exp *exp)
{
	exp->input = ft_rmchr(exp->input, exp->temp);
	exp->temp = exp->input;
	return (exp->temp);
}

char	*process_heredoc(t_exp *exp)
{
	exp->temp++;
	exp->temp++;
	while (ft_str_exist(exp->temp) && is_space(*exp->temp))
		exp->temp++;
	if (*exp->temp == '$' && is_quote(*(exp->temp + 1)))
		exp->temp = process_dollar(exp);
	else
	{
		while (*exp->temp && !(is_space(*exp->temp) && !exp->sig_quote))
			exp->sig_quote = process_quotes(exp->sig_quote, *exp->temp++);
	}
	return (exp->temp);
}

char	*process_doble_quote(t_list *lst_env, t_exp *exp)
{
	exp->temp = search_name(lst_env, exp);
	return (exp->temp);
}

char	*var_expand(t_exp *cur, t_env *var)
{
	char	*res;
	t_exp	exp;
	t_env	tmp;

	tmp = *var;
	exp = *cur;
	res = ft_calloc(1, ft_strlen(exp.input) - ft_strlen(tmp.name)
			+ value_len(tmp.value));
	exp.temp = res;
	while (*&exp.input != *&cur->temp)
		*exp.temp++ = *exp.input++;
	exp.input++;
	while (tmp.value && *tmp.value)
	{
		if (is_operator(*(tmp.value)))
			{
				*exp.temp++ = '\'';
				*exp.temp++ = *tmp.value++;
				*exp.temp++ = '\'';
			}
		else
			*exp.temp++ = *tmp.value++;
	}
	while (*exp.input && *tmp.name && *exp.input == *tmp.name)
	{
		exp.input++;
		tmp.name++;
	}
	while (*exp.input)
		*exp.temp++ = *exp.input++;
	return (free(cur->input), res);
}

char	*var_is_null(char *value, char sig)
{
	if (!value && !is_double_quote(sig))
		value = "\"\"";
	return (value);
}

static int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	value_len(char *value)
{
	char	sig_quote;
	char	*tmp_value;
	int		qty_operators;

	sig_quote = 0;
	tmp_value = value;
	qty_operators = 0;
	while(ft_str_exist(tmp_value))
	{
		sig_quote = process_quotes(sig_quote, *tmp_value);
		if (!sig_quote && is_operator(*tmp_value))
			qty_operators++;
		tmp_value++;
	}
	return ((qty_operators * 2) + ft_strlen(value));
}
