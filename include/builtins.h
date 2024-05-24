/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:15:16 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/23 17:43:31 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../library/lib.h"

void	pwd(void);
void	echo(char **argv);
int		cd(int argc, char **argv);
void	mini_exit(int argc, char **argv);

#endif
