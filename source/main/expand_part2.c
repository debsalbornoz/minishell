/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/26 18:15:15 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_no_name(char *input, char *position);
static char	*expand_no_value(char *input, char *position, char *name);
static char	*expand_full(char *input, char *position, char *name, char *value);

char	*var_expand(char *input, char *position, char *name, char *value)
{
	if (!name)
		return (expand_no_name(input, position));
	else if (!value)
		return (expand_no_value(input, position, name));
	return (expand_full(input, position, name, value));
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

char	*expand_full(char *input, char *position, char *name, char *value)
{
	char	*res;
	char	*temp;

	res = ft_calloc(1, ft_strlen(input) - ft_strlen(name) + ft_strlen(value));
	temp = res;
	while (*&input != *&position)
		*temp++ = *input++;
	input++;
	while (*value)
		*temp++ = *value++;
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
