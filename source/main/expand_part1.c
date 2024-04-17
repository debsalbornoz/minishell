/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 08:30:03 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/17 11:11:24 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_single_quote(t_exp *exp);
static char	*process_default(t_list *lst_env, t_exp *exp);
static char	*search_value(t_list *lst_env, char *name);

char	*expand(t_list *lst_env, char *input)
{
	t_exp	exp;

	exp.input = input;
	exp.temp = exp.input;
	exp.sig_quote = 0;
	while (*exp.temp)
	{
		exp.sig_quote = process_quotes(exp.sig_quote, *exp.temp);
		if (*exp.temp == '$' && (is_space(*(exp.temp + 1)) || !*(exp.temp + 1)))
			exp.temp++;
		else if (is_single_quote(exp.sig_quote))
			exp.temp = process_single_quote(&exp);
		else if (!is_double_quote(exp.sig_quote))
			exp.temp = process_default(lst_env, &exp);
		else if (*exp.temp == '$')
			exp.temp = process_doble_quote(lst_env, &exp);
		else
			exp.temp++;
	}
	return (exp.input);
}

static char	*process_single_quote(t_exp *exp)
{
	while (*exp->temp++ && is_single_quote(exp->sig_quote))
		exp->sig_quote = process_quotes(exp->sig_quote, *exp->temp);
	return (exp->temp);
}

static char	*process_default(t_list *lst_env, t_exp *exp)
{
	if (*exp->temp == '$' && is_quote(*(exp->temp + 1)))
		return (process_dollar(exp));
	else if (*exp->temp == '<' && *(exp->temp + 1) == '<')
		return (process_heredoc(exp));
	else if (*exp->temp == '$')
		exp->temp = search_name(lst_env, exp);
	else
		exp->temp++;
	return (exp->temp);
}

char	*search_name(t_list *lst_env, t_exp *exp)
{
	t_env	var;
	char	*temp;

	var.name = 0;
	var.value = 0;
	temp = exp->temp;
	temp++;
	if (*temp && (*temp == '?' || *temp == '$'))
		var.name = ft_chrjoin(var.name, *temp++);
	else
	{
		while (*temp && (ft_isalnum(*temp) || *temp == '_'))
			var.name = ft_chrjoin(var.name, *temp++);
	}
	if (var.name || (!var.name && !exp->sig_quote))
	{
		var.value = search_value(lst_env, var.name);
		if (!var.value && !is_double_quote(exp->sig_quote))
			var.value = ft_strdup("\"\"");
		exp->input = var_expand(exp->input, exp->temp, &var);
		exp->temp = exp->input;
		exp->sig_quote = 0;
		free(var.name);
	}
	else
		exp->temp++;
	return (exp->temp);
}

static char	*search_value(t_list *lst_env, char *name)
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
