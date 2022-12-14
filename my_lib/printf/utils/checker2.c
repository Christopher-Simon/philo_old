/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:13:28 by chsimon           #+#    #+#             */
/*   Updated: 2022/05/30 11:53:38 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	flag_first(char c)
{
	if (c == '-' || c == '+' || c == ' '
		|| c == '0' || c == '#')
		return (1);
	if (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X')
		return (1);
	return (0);
}

int	ft_isdig_not_0(int c)
{
	if (c >= '1' && c <= '9')
		return (1);
	return (0);
}
