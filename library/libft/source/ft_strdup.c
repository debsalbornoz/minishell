/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:23:14 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/11 15:50:21 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*duplicate;
	int		i;

	if (!s)
		return (NULL);
	duplicate = NULL;
	len = ft_strlen(s) + 1;
	if (len > 0)
		duplicate = (char *)malloc(len * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	*duplicate = '\0';
	i = 0;
	while (s[i] != '\0')
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
