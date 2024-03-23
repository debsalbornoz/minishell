/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:51:48 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/23 15:49:29 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(char	*str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1++ != *str2++)
			return (1);
	}
	return (0);
}

char	*ft_chrjoin(char *dest, char src)
{
	char	*res;
	char	*temp;

	res = 0;
	temp = 0;
	if (!dest)
	{
		res = ft_calloc(2, sizeof(char));
		*res = src;
		return (res);
	}
	res = ft_calloc(1, ft_strlen(dest) + 2);
	temp = res;
	while (*dest)
		*temp++ = *dest++;
	*temp = src;
	return (res);
}
