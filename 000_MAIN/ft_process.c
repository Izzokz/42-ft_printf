/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:08:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/17 15:08:44 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	is_flag(const char *flag, t_params *pa)
{
	size_t	k;
	size_t	init;

	init = pa->i;
	k = 0;
	while (pa->str[pa->i] && flag[k]
		&& pa->str[pa->i] == flag[k])
	{
		(pa->i)++;
		k++;
	}
	if (!flag[k] && pa->str[--(pa->i)] == flag[k - 1])
		return (1);
	pa->i = init;
	return (0);
}

static int	do_write(t_params *pa)
{
	if (pa->str[pa->i] == '*')
		return (ft_write_all(pa));
	if (is_flag("f#", pa))
		return (ft_write_file(pa));
	if (is_flag("_0", pa))
		return (ft_write_bool(va_arg(pa->args, int), 0));
	if (is_flag("_1", pa))
		return (ft_write_bool(va_arg(pa->args, int), 1));
	if (pa->str[pa->i] == 'b' || pa->str[pa->i] == 'B')
		return (ft_write_b(pa));
	if (pa->str[pa->i] == 'c')
		return (ft_write_c((char)va_arg(pa->args, int)));
	if (pa->str[pa->i] == 's')
		return (ft_write_s(va_arg(pa->args, char *)));
	if (pa->str[pa->i] == 'i' || pa->str[pa->i] == 'd')
		return (ft_write_d(va_arg(pa->args, int)));
	if (pa->str[pa->i] == 'x')
		return (ft_write_x(va_arg(pa->args, int), 0));
	if (pa->str[pa->i] == 'X')
		return (ft_write_x(va_arg(pa->args, int), 1));
	if (pa->str[pa->i] == 'p')
		return (ft_write_p(va_arg(pa->args, unsigned long)));
	if (pa->str[pa->i] == 'u')
		return (ft_write_u(va_arg(pa->args, unsigned int)));
	return (ft_out_add(&(char *){ft_strdup("%")}));
}

static char	*ft_ctos(char c)
{
	char	*str;

	if (!c)
		return (ft_calloc(1, 1));
	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = 0;
	return (str);
}

/*
len[0] is the total length
len[1] is temporary
*/
int	ft_process(t_params *pa)
{
	int		len[2];
	char	err;

	len[0] = 0;
	err = 0;
	while (pa->str[++(pa->i)])
	{
		if (pa->str[pa->i] == '%')
			len[1] = (pa->i++) * 0 + do_write(pa);
		else
			len[1] = ft_out_add(&(char *){ft_ctos(pa->str[pa->i])});
		if (len[1] == -1)
			err = 1;
		else if (len[1] == -2)
			return (-2);
		len[0] += len[1];
	}
	if (err)
		return (-1);
	return (len[0]);
}
