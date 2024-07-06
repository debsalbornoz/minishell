/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:41 by jackson           #+#    #+#             */
/*   Updated: 2024/07/01 14:15:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H

# include "utils.h"
# include "linked_list.h"
# include "../library/lib.h"

//create_env_list.c
t_list	*data_env_addr(void);
t_list	*create_env_list(char **envp, t_list *env_lst);
char	*get_envp_name(char *envp);
char	*get_envp_value(char *envp);

//update_env_list.c
int		update_env_list(t_list *lst_env, char *name, char *value);
void	add_new_node(t_list *lst_env, char *name, char *value);
int		update_existing_node(t_list *lst_env, char *name, char *value);
char	*ft_get_env(char *name);
int		exist_var(t_list *envp, char *name);

#endif
