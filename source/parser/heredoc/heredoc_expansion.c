/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:43:41 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/29 17:21:38 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*extract_var_value(int counter, char *input);

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

int	get_var_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] != ' ' && input[i] != '$' && input[i] != '\0')
		i++;
	return (i);
}

int	get_substr_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '$' && input[i] != '\0')
		i++;
	return (i);
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
