/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:51:48 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/26 17:12:05 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(char	*str1, char *str2)
{
	if ((*str1 && !*str2) || (!*str1 && *str2))
		return (1);
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
