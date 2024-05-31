/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:57:17 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/20 16:43:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error(t_list *tokens, t_list	*envp, char *input)
{
	if (redirect_error(tokens) || pipe_error(tokens)
		|| dot_error(tokens))
	{
		printf("Syntax error\n");
		update_env_list(envp, "?", "2");
		free_list(tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	if (dot_error(tokens) == 2)
	{
		printf("Syntax error\n");
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
