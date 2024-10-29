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

#include "ft_printf.h"

static int	do_write(const char *str, size_t *i, va_list *params, int fd)
{
	int	init;

	init = 1;
	if (str[*i] == 'b' || str[*i] == 'B')
		return (ft_write_b(params, str, i, fd));
	if (str[*i] == 'c')
		return (ft_write_c((char)va_arg(*params, int), fd));
	if (str[*i] == 's')
		return (ft_write_s(va_arg(*params, char *), fd));
	if (str[*i] == 'i' || str[*i] == 'd')
		return (ft_write_d(va_arg(*params, int), fd));
	if (str[*i] == 'x' || str[*i] == 'X')
		return (ft_write_x(va_arg(*params, int), str[*i] == 'X', fd));
	if (str[*i] == 'p')
		return (ft_write_p(va_arg(*params, unsigned long), fd));
	if (str[*i] == 'u')
		return (ft_write_u(va_arg(*params, unsigned int), &init, fd));
	if (str[*i] == '%')
		return (write(fd, "%", 1));
	return (write(fd, "%", 1));
}

int	ft_process(const char *str, va_list *params, int fd)
{
	size_t	i;
	size_t	len;
	size_t	temp_len;
	size_t	err;

	i = -1;
	len = 0;
	err = 0;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			i++;
			temp_len = do_write(str, &i, params, fd);
			if (!temp_len)
				err = 1;
			len += temp_len;
		}
		else
			len += write(fd, &str[i], 1);
	}
	va_end(*params);
	if (err)
		return (-1);
	return (len);
}
