/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:35:24 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/01 20:16:29 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int			is_sig(char chr);
static int			is_dig(char chr);
static long long	latoi(const char *arg, int *err);
static int			valid_nbr(char *arg);

int	mini_exit(char **exec, t_list *envp)
{
	unsigned long long	nbr;
	int					err;

	err = 0;
	nbr = 0;
	printf("exit\n");
	if (!ft_str_exist(*(exec + 1)))
		return (update_env_list(envp, "?", "normal_exit"), 1);
	if (valid_nbr(*(exec + 1)))
		return (ft_putstr_fd("exit: numeric argument required\n", 2), 2);
	nbr = latoi(*(exec + 1), &err);
	if (err)
		return (ft_putstr_fd("exit: numeric argument required\n", 2), 2);
	if (ft_str_exist(*(exec + 2)))
		return (update_env_list(envp, "?", "error_exit")
			, ft_putstr_fd("exit: too many arguments\n", 2), 2);
	if (nbr > 255)
		return (nbr % 256);
	else
		return (nbr);
}

static int	is_sig(char chr)
{
	return (chr == '+' || chr == '-');
}

static int	is_dig(char chr)
{
	return (chr >= '0' && chr <= '9');
}

static long long	latoi(const char *arg, int *err)
{
	int			sig;
	long long	res;
	char		*arg_tmp;

	sig = 1;
	res = 0;
	arg_tmp = (char *)arg;
	if (is_sig(*arg_tmp))
	{
		if (*arg_tmp++ == '-')
			sig *= -1;
	}
	while (*arg_tmp && is_dig(*arg_tmp))
	{
		if (res >= 922337203685477580
			&& ((sig >= 0 && *arg_tmp > '7') || (sig < 0 && *arg_tmp > '8')))
			return (*err = 1, 0);
		res = res * 10 + (*arg_tmp++ - '0');
	}
	return (res * sig);
}

static int	valid_nbr(char *arg)
{
	int			has_digits;
	const char	*arg_tmp;

	has_digits = 0;
	arg_tmp = arg;
	if (!*arg_tmp)
		return (1);
	if (*arg_tmp == '+' || *arg_tmp == '-')
		arg_tmp++;
	if (!*arg_tmp)
		return (1);
	while (*arg_tmp)
	{
		if (*arg_tmp < '0' || *arg_tmp > '9')
			return (1);
		has_digits = 1;
		arg_tmp++;
	}
	return (!has_digits);
}
