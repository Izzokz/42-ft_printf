/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <kzhen-cl@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:07:17 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/30 00:07:20 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_isnum(const char c)
{
	return (c >= '0' && c <= '9');
}

static int	base_after_b(const char *str, size_t *i)
{
	size_t	j;
	int		base;

	base = 0;
	j = *i;
	if (ft_strlen(str) > j + 2 && ft_isnum(str[j + 1]) && ft_isnum(str[j + 2]))
	{
		base = 10 * (str[j + 1] - '0') + str[j + 2] - '0';
		*i += 2;
	}
	else if (ft_strlen(str) > j + 1 && ft_isnum(str[j + 1]))
	{
		base = str[j + 1] - '0';
		*i += 1;
	}
	return (base);
}

/*
<str> is the first parameter of ft_printf()
<p_str> is the string to print
*/
int	ft_write_b(va_list *params, const char *str, size_t *i, int fd)
{
	size_t	len;
	char	*p_str;
	char	c;
	int		base;

	c = str[*i];
	base = base_after_b(str, i);
	p_str = NULL;
	len = 0;
	if (base && (base >= 2 && base <= 36))
		p_str = ft_getbase(va_arg(*params, unsigned long), base, c == 'B');
	if (p_str)
	{
		ft_putstr_fd(p_str, fd);
		len = ft_strlen(p_str);
		free(p_str);
		str = NULL;
	}
	return (len);
}
