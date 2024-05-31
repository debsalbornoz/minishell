/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:52:19 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/31 19:46:48 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "../library/lib.h"
# include "structs.h"

int		builtins(t_list *token, t_list *exec, t_list *envp);
int		mini_cd(t_list *token);
void	mini_pwd(void);
void	mini_env(t_list *envp);
void	mini_echo(t_list *token);
int		mini_exit(void);
void	mini_unset(void);
void	mini_export(t_list *envp);

#endif
