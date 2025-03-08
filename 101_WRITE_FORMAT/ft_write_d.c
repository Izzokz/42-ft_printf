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

#include "../ft_printf.h"

int	ft_write_d(int value)
{
	return (ft_out_add(&(char *){ft_itoa(value)}));
}

int	ft_write_x(int value, int up)
{
	return (ft_out_add(&(char *){ft_getbase((unsigned int)value, 16, up)}));
}

int	ft_write_u(unsigned int value)
{
	char	*c;
	int		len;
	int		tmp;

	len = 1;
	if (value > 9)
	{
		tmp = ft_write_u(value / 10);
		if (tmp == -2)
			return (-2);
		len += tmp;
	}
	c = malloc(2);
	if (!c)
		return (-2);
	c[0] = (value % 10) + '0';
	c[1] = 0;
	return (ft_out_add(&c));
}

int	ft_write_p(unsigned long value)
{
	int		len;

	if (!value)
		return (ft_out_add(&(char *){ft_strdup("(nil)")}));
	if (ft_out_add(&(char *){ft_strdup("0x")}) == -2)
		return (-2);
	len = ft_out_add(&(char *){ft_getbase(value, 16, 0)});
	if (len >= 0)
		return (len + 2);
	return (len);
}

int	ft_write_bool(int value, int colored)
{
	if (value)
	{
		if (colored)
			return (ft_out_add(&(char *){ft_strdup("TRUE")}));
		return (ft_out_add(&(char *){ft_strdup("\e[1m\e[32mTRUE\e[0m\e[m")}));
	}
	if (!colored)
		return (ft_out_add(&(char *){ft_strdup("FALSE")}));
	return (ft_out_add(&(char *){ft_strdup("\e[1m\e[31mFALSE\e[0m\e[m")}));
}
