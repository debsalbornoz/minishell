/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:52:08 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/04 15:47:06 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s3_len;
	char	*s3;
	int		i;
	int		j;

	i = 0;
	s3_len = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc((s3_len + 1) * sizeof(char));
	if (!s3 || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[s3_len] = '\0';
	return (s3);
}
