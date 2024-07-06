/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:57:17 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/20 12:38:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>
#include <errno.h>

int	syntax_error(t_list *tokens, t_list	*envp, char *input)
{
	if (redirect_error(tokens) || pipe_error(tokens)
		|| dot_error(tokens))
	{
		ft_putstr_fd("Syntax error\n", 2);
		update_env_list(envp, "?", "2");
		free_list(tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	if (dot_error(tokens) == 2)
	{
		ft_putstr_fd("Syntax error\n", 2);
		update_env_list(envp, "?", "127");
		free_list(tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	return (0);
}

int	dot_error(t_list	*tokens)
{
	char	*str;

	str = tokens->head->data->token->value;
	if ((!ft_strncmp(str, ".", ft_strlen(str))
			|| !ft_strncmp(str, "\'.\'", ft_strlen(str))
			|| !ft_strncmp(str, "\".\"", ft_strlen(str)))
		&& tokens->head->next == NULL)
		return (1);
	if ((!ft_strncmp(str, "..", ft_strlen(str))
			|| !ft_strncmp(str, "\'..\'", ft_strlen(str))
			|| !ft_strncmp(str, "\"..\"", ft_strlen(str)))
		&& tokens->head->next == NULL)
		return (2);
	return (0);
}
