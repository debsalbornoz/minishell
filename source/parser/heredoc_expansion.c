/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:43:41 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/17 21:33:25 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		count_var_size(char *input);
char	*get_env_value(int counter, char *input);
int		get_input_len(char *input);

char	*return_var(char *input)
{
	int		i;
	int		counter;
	char	*env_value;
	char	*input_expanded;
	int		input_len;
	char	*str;

	i = 0;
	counter = 0;
	env_value = NULL;
	input_expanded = NULL;
	input_len = 0;
	str = NULL;
	while (input[i] != '\0')
	{
		input_len = get_input_len(input);
		if (input_len > 0)
		{
			str = ft_calloc(input_len + 1, sizeof(char));
			ft_strlcpy(str, &input[i], input_len + 1);
			if (input[i + input_len - 1])
				i += input_len;
		}
		if (input[i] == '$' && input[i + 1])
		{
			counter = count_var_size(&input[i + 1]);
			env_value = get_env_value(counter, &input[i + 1]);
			if (input[i + counter])
				i += counter - 1;
			input_expanded = ft_strjoin(str, env_value);
		}
		i++;
	}
	return (input_expanded);
}

int	count_var_size(char *input)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (input[i] != 13 && input[i] != 32
		&& input[i] != '$' && input[i] != '\0')
	{
		counter++;
		i++;
	}
	return (counter);
}

char	*get_env_value(int counter, char *input)
{
	char	*env_var;
	char	*env_value;

	env_var = NULL;
	env_var = ft_calloc((counter + 1), sizeof(char));
	ft_strlcpy(env_var, input, counter + 1);
	env_value = ft_get_env(env_var);
	free (env_var);
	return (env_value);
}

int	get_input_len(char *input)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (input[i] != '$' && input[i] != '\0')
	{
		counter++;
		i++;
	}
	return (counter);
}
