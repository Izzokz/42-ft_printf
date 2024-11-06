/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:35:22 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/17 16:35:23 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	g_fd; // Read Only

int	ft_write_d(int value)
{
	char	*str;
	int		len;

	str = ft_itoa(value);
	if (!str)
		return (0);
	ft_putstr_fd(str, g_fd);
	len = ft_strlen(str);
	if (str)
		free(str);
	return (len);
}

int	ft_write_x(int value, int up)
{
	char	*str;
	int		len;

	str = NULL;
	str = ft_getbase((unsigned int)value, 16, up);
	if (!str)
		return (0);
	ft_putstr_fd(str, g_fd);
	len = ft_strlen(str);
	free(str);
	return (len);
}

int	ft_write_u(unsigned int value)
{
	char	c;
	int		len;

	len = 1;
	if (value > 9)
		len += ft_write_u(value / 10);
	c = (value % 10) + '0';
	write(g_fd, &c, 1);
	return (len);
}

int	ft_write_p(unsigned long value)
{
	int		len;
	char	*str;

	if (!value)
	{
		ft_putstr_fd("(nil)", g_fd);
		return (5);
	}
	str = NULL;
	str = ft_getbase(value, 16, 0);
	if (!str)
		return (0);
	ft_putstr_fd("0x", g_fd);
	len = ft_strlen(str) + 2;
	ft_putstr_fd(str, g_fd);
	free(str);
	return (len);
}

int	ft_write_bool(int value, int colored)
{
	if (value)
	{
		if (colored)
			return (ft_write_s("\x1B[1m\x1B[32mTRUE\x1B[0m\x1B[m"));
		return (ft_write_s("TRUE"));
	}
	if (colored)
		return (ft_write_s("\x1B[1m\x1B[31mFALSE\x1B[0m\x1B[m"));
	return (ft_write_s("FALSE"));
}
