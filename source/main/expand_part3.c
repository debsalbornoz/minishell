/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:20:11 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/07 21:31:42 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_no_name(char *input, char *position);
static char	*expand_no_value(char *input, char *position, char *name);
static char	*expand_full(char *input, char *position, t_env *var);

char	*var_expand(char *input, char *position, t_env *var)
{
	if (!var->name)
		return (expand_no_name(input, position));
	else if (!var->value)
		return (expand_no_value(input, position, var->name));
	return (expand_full(input, position, var));
}

char	*expand_no_name(char *input, char *position)
{
	char	*res;
	char	*temp;

	res = ft_calloc(1, ft_strlen(input) + 3);
	temp = res;
	while (*&input != *&position)
		*temp++ = *input++;
	*temp++ = '\'';
	*temp++ = *input++;
	*temp++ = '\'';
	while (*input)
		*temp++ = *input++;
	temp = 0;
	return (res);
}

char	*expand_no_value(char *input, char *position, char *name)
{
	char	*res;
	char	*temp;

	res = ft_calloc(1, ft_strlen(input) - ft_strlen(name));
	temp = res;
	while (*&input != *&position)
		*temp++ = *input++;
	input++;
	while (*input && *name && *input == *name)
	{
		input++;
		name++;
	}
	while (*input)
		*temp++ = *input++;
	temp = 0;
	return (res);
}

char	*expand_full(char *input, char *position, t_env *var)
{
	int		len;
	char	*res;
	char	*temp;
	t_env	tmp_var;

	tmp_var = *var;
	len = ft_strlen(input) - ft_strlen(tmp_var.name) + ft_strlen(tmp_var.value);
	res = ft_calloc(1, len);
	temp = res;
	while (*&input != *&position)
		*temp++ = *input++;
	input++;
	while (*tmp_var.value)
		*temp++ = *tmp_var.value++;
	while (*input && *tmp_var.name && *input == *tmp_var.name)
	{
		input++;
		tmp_var.name++;
	}
	while (*input)
		*temp++ = *input++;
	temp = 0;
	return (res);
}
