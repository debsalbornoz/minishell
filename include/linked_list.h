/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:47:49 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/02 16:50:46 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "../library/lib.h"

t_list	*add_node(t_list *list);
t_list	*runs_on_list(t_list *list, t_node *(f)(t_node *));
int		count_nodes(t_list *lst);

void	free_list(t_list *list, void (f)(t_list *));
void	free_lst_tokens(t_list *tokens);
void	free_lst_env(t_list *envp);
void	free_lst_exec(t_list *exec);
void	release_memory(t_list *tokens, t_list *exec, char *input);

#endif
