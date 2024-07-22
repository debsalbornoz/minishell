/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:41 by jackson           #+#    #+#             */
/*   Updated: 2024/07/09 14:58:13 by dlamark-         ###   ########.fr       */
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
t_list	*add_new_node(t_list *lst_env, char *name, char *value);

//update_env_list.c
t_list	*update_env_list(t_list *lst_env, char *name, char *value);
int		update_existing_node(t_list *lst_env, char *name, char *value);
char	*ft_get_env(char *name);
int		exist_var(t_list *envp, char *name);
int		get_env_error(t_list *envp);

#endif
