/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:15:16 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/29 05:16:16 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "../library/lib.h"

int		builtins(t_list *token, t_list *exec, t_list *envp);
int		mini_cd(t_list *token);
void	mini_pwd(void);
void	mini_env(void);
void	mini_echo(t_list *token);
int		mini_exit(void);
void	mini_unset(void);
void	mini_export(void);

#endif
