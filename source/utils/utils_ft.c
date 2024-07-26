/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:51:48 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/25 18:39:21 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	ft_strcmp(char	*str1, char *str2)
{
	if (!str1 || !str2)
		return (1);
	if ((*str1 && !*str2) || (!*str1 && *str2))
		return (1);
	while (*str1 || *str2)
	{
		if (*str1++ != *str2++)
			return (1);
	}
	return (0);
}

char	*ft_chrjoin(char *dest, char src)
{
	char	*res;
	char	*temp1;
	char	*temp2;

	res = 0;
	temp1 = 0;
	temp2 = 0;
	if (!dest)
	{
		res = ft_calloc(2, sizeof(char));
		*res = src;
		return (res);
	}
	res = ft_calloc(1, ft_strlen(dest) + 2);
	temp1 = res;
	temp2 = dest;
	while (*temp2)
		*temp1++ = *temp2++;
	*temp1 = src;
	free(dest);
	return (res);
}

char	*ft_rmchr(char *input, char *position)
{
	char	*result;
	char	*temp_input;
	char	*temp_result;

	temp_input = input;
	result = ft_calloc(1, ft_strlen(input));
	temp_result = result;
	while (*&temp_input != *&position)
		*temp_result++ = *temp_input++;
	temp_input++;
	while (*temp_input)
		*temp_result++ = *temp_input++;
	ft_bzero(input, ft_strlen(input));
	free(input);
	return (result);
}

int	ft_str_exist(char *str)
{
	return (str && *str);
}

int	ft_free_str(char *str)
{
	if (str)
		return (free(str), 1);
	return (0);
}
