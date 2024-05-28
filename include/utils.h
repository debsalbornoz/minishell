/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 02:44:52 by jackson           #+#    #+#             */
/*   Updated: 2024/05/28 02:51:37 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../library/lib.h"

int		ft_strcmp(char	*str1, char *str2);
char	*ft_chrjoin(char *dest, char src);
char	*ft_rmchr(char *input, char *position);

#endif
