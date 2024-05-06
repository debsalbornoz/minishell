/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/06 16:06:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	exp->temp = trim_start_spaces(exp->temp);
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
	int		len;
	char	*res;
	t_exp	exp;
	t_env	tmp;

	tmp = *var;
	exp = *cur;
	len = ft_strlen(exp.input) - ft_strlen(tmp.name) + ft_strlen(tmp.value);
	res = ft_calloc(1, len);
	exp.temp = res;
	while (*&exp.input != *&cur->temp)
		*exp.temp++ = *exp.input++;
	exp.input++;
	while (tmp.value && *tmp.value)
		*exp.temp++ = *tmp.value++;
	while (*exp.input && *tmp.name && *exp.input == *tmp.name)
	{
		exp.input++;
		tmp.name++;
	}
	while (*exp.input)
		*exp.temp++ = *exp.input++;
	exp.temp = 0;
	free(cur->input);
	return (res);
}

char	*var_is_null(char *value, char sig)
{
	if (!value && !is_double_quote(sig))
		value = "\"\"";
	return (value);
}
