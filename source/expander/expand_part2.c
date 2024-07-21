/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/21 18:50:24 by dlamark-         ###   ########.fr       */
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

char	*var_is_null(char *value, char sig)
{
	if (!value && !is_double_quote(sig))
		value = "\"\"";
	return (value);
}
