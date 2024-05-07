/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:57:17 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 17:37:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error(t_list *lst_tokens, t_list	*lst_env, char *input)
{
	if (redirect_error(lst_tokens) || pipe_error(lst_tokens)
		|| dot_error(lst_tokens))
	{
		printf("Syntax error\n");
		update_env_list(lst_env, "?", "2: command not found");
		free_list(lst_tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	if (dot_error(lst_tokens) == 2)
	{
		printf("Syntax error\n");
		update_env_list(lst_env, "?", "127: command not found");
		free_list(lst_tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	lst_tokens->node = lst_tokens->head;
	return (0);
}


int	dot_error(t_list	*lst_tokens)
{
	char	*str;

	str = lst_tokens->head->data->token->value;
	if ((!ft_strncmp(str, ".", ft_strlen(str))
			|| !ft_strncmp(str, "\'.\'", ft_strlen(str))
			|| !ft_strncmp(str, "\".\"", ft_strlen(str)))
		&& lst_tokens->head->next == NULL)
		return (1);
	if ((!ft_strncmp(str, "..", ft_strlen(str))
			|| !ft_strncmp(str, "\'..\'", ft_strlen(str))
			|| !ft_strncmp(str, "\"..\"", ft_strlen(str)))
		&& lst_tokens->head->next == NULL)
		return (2);
	return (0);
}
