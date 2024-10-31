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

/*
This function works like a converter from an alnum character
to an integer if <type> == 'c', acts like isdigit if
<type> == 'n' and acts like isalnum if <type> == 'a'
*/
static int	ft_conv(const char type, const char c)
{
	int	conv;

	conv = 0;
	if (type == 'c')
	{
		conv = -1;
		if (c >= '0' && c <= '9')
			conv = c - '0';
		if (c >= 'a' && c <= 'z')
			conv = c - 'a' + 10;
		if (c >= 'A' && c <= 'Z')
			conv = c - 'A' + 10;
	}
	if (type == 'n')
		conv = (c >= '0' && c <= '9');
	if (type == 'a')
		conv = ((c >= '0' && c <= '9')
				|| (c >= 'a' && c <= 'z')
				|| (c >= 'A' && c <= 'Z'));
	return (conv);
}

static int	from_base(const char *str, size_t *i)
{
	size_t	j;
	int		base;

	base = 0;
	j = *i;
	if (str[++j] != '[')
		return (-1);
	while (str[++j] && str[j] != ']' && ft_conv('n', str[j]))
		;
	if (str[j] != ']' || j > *i + 4 || j < *i + 3)
		return (-1);
	*i += 2;
	while (*i < j)
	{
		base = (base * 10) + (str[*i] - '0');
		*i += 1;
	}
	return (base);
}

static int	base_after_b(const char *s, size_t *i)
{
	size_t	j;
	int		base;

	base = 0;
	j = *i;
	if (ft_strlen(s) > j + 2 && ft_conv('n', s[j +1]) && ft_conv('n', s[j +2]))
	{
		base = 10 * (s[j + 1] - '0') + s[j + 2] - '0';
		*i += 2;
	}
	else if (ft_strlen(s) > j + 1 && ft_conv('n', s[j + 1]))
	{
		base = s[j + 1] - '0';
		*i += 1;
	}
	return (base);
}

static int	ft_getdec(const char *str, int base)
{
	unsigned long	dec;
	int				len;
	int				c_to_i;
	int				weight;

	len = ft_strlen(str);
	dec = 0;
	weight = -1;
	while (str[--len])
	{
		c_to_i = ft_conv('c', str[len]);
		if (base <= c_to_i || c_to_i < 0)
			return (0);
		dec += c_to_i * ft_pow(base, ++weight);
	}
	return (dec);
}

/*
<str> is the first parameter of ft_printf()
<p_str> is the string to print
If the user does not use ft_printf in a good way
the result may differ
*/
int	ft_write_b(va_list *params, const char *str, size_t *i, int fd)
{
	size_t	len;
	char	*p_str;
	char	c;
	int		from;
	int		base;

	c = str[*i];
	from = from_base(str, i);
	base = base_after_b(str, i);
	p_str = NULL;
	len = 0;
	if (from != -1 && (from >= 2 && from <= 36))
		from = ft_getdec(va_arg(*params, const char *), from);
	else
		from = va_arg(*params, unsigned long);
	if (base && (base >= 2 && base <= 36))
		p_str = ft_getbase(from, base, c == 'B');
	if (p_str)
	{
		ft_putstr_fd(p_str, fd);
		len = ft_strlen(p_str);
		free(p_str);
		str = NULL;
	}
	return (len);
}
