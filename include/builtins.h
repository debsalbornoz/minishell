/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:52:19 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/31 20:43:49 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "structs.h"
# include "env_list.h"
# include "linked_list.h"
# include "../library/lib.h"

int		builtins(t_list *exec, t_list *envp);
int		mini_cd(char **exec);
int		mini_pwd(char **exec);
int		mini_echo(char **exec);
int		mini_unset(char **exec, t_list *envp);
void	mini_env(t_list *envp);
int		mini_export(char **exec, t_list *envp);
int		mini_exit(char **exec, t_list *envp);

union u_func
{
	int	(*f_cmd_table)(char **);
	int	(*f_cmd_table_n_env_list)(char **, t_list *);
};

#endif
