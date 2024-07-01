/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:43:41 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/01 11:44:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*expand_input(char *input)
{
	int		i;
	char	*input_expanded;
	int		counter;
	char	*env_value;
	char	*str;

	i = 0;
	str = NULL;
	input_expanded = NULL;
	env_value = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] != '\0')
		{
			counter = get_var_len(&input[i + 1]);
			env_value = extract_var_value(counter, &input[i + 1]);
			input_expanded = ft_strjoin_free(input_expanded, env_value);
			i += counter + 1;
		}
		else
		{
			counter = get_substr_len(&input[i]);
			str = extract_substr(&i, counter, input);
			input_expanded = ft_strjoin_free(input_expanded, str);
		}
	}
	return (input_expanded);
}

char	*extract_substr(int *i, int counter, char *input)
{
	char	*str;

	str = ft_calloc(counter + 1, sizeof(char));
	ft_strlcpy(str, &input[*i], counter + 1);
	*i += counter;
	return (str);
}

char	*extract_var_value(int counter, char *input)
{
	char	*env_var;
	char	*env_value;

	env_var = ft_calloc(counter + 1, sizeof(char));
	ft_strlcpy(env_var, input, counter + 1);
	env_value = ft_strdup(ft_get_env(env_var));
	free(env_var);
	return (env_value);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;

	result = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (s2);
	else if (s2 == NULL)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = (char *) ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len_s1 + len_s2 + 1);
	ft_strlcat(result, s2, len_s1 + len_s2 + 1);
	free(s1);
	free(s2);
	return (result);
}
