/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:52:19 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/20 20:02:37 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "structs.h"
# include "env_list.h"
# include "linked_list.h"
# include "../library/lib.h"

int		builtins(t_list *exec, t_list *envp, int fd_in, int fd_out);
int		mini_cd(char **exec);
int		mini_pwd(char **exec);
int		mini_echo(char **exec);
int		mini_unset(char **exec, t_list *envp);
int		mini_env(t_list *envp);
int		mini_export(char **exec, t_list *envp);
int		mini_exit(char **exec, t_list *envp);
int		ft_is_alpha(char c);
int		ft_is_digit(char c);
int		ft_isalphanum(char c);
int		is_not_ocult_var(char *name);
char	**handle_sort_envp(t_list *lst_env);
char	**sort(char **envp);
char	*build_env_var2(char *name, char *value);
void	print_envp(char **envp);
void	free_matrix(char **matrix);
char	*allocate_env_var(char *name, char *value);

union u_func
{
	int	(*f_cmd_table)(char **);
	int	(*f_env_list)(t_list *);
	int	(*f_cmd_table_n_env_list)(char **, t_list *);
};

#endif
