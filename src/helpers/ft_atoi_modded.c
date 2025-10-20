/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:33 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/20 00:59:54 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

static int	check_limits(long num, int sign)
{
	if (sign == -1 && num > 2147483648)
		return (0);
	if (sign == 1 && num > 2147483647)
		return (0);
	return (1);
}

static int	skip_space_and_sign(const char *str, int *i, int *sign)
{
	while ((str[*i] == ' ') || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i + 1] == '+' || str[*i + 1] == '-')
			return (0);
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	return (1);
}

int	ft_atoi_pushswap(const char *str, int *error)
{
	int		i;
	int		sign;
	long	result;

	*error = 0;
	i = 0;
	sign = 1;
	result = 0;
	if (!skip_space_and_sign(str, &i, &sign))
		return (*error = 1, 0);
	if (str[i] < '0' || str[i] > '9')
		return (*error = 1, 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (!check_limits(result, sign))
			return (*error = 1, 0);
		i++;
	}
	if (str[i] != '\0')
		return (*error = 1, 0);
	return (result * sign);
}

int	is_empty_string(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			return (0);
		i++;
	}
	return (1);
}
