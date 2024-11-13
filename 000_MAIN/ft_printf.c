/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:47:35 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/17 15:08:36 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_fd(const char *str, int fd, ...)
{
	t_params	*pa;

	if (!str || fd < 0)
		return (-1);
	pa = ft_calloc(1, sizeof(t_params));
	pa->str = str;
	pa->fd = fd;
	pa->i = -1;
	va_start(pa->args, fd);
	return (ft_process(pa));
}

int	ft_printf(const char *str, ...)
{
	t_params	*pa;

	if (!str)
		return (-1);
	pa = ft_calloc(1, sizeof(t_params));
	pa->str = str;
	pa->fd = 1;
	pa->i = -1;
	va_start(pa->args, str);
	return (ft_process(pa));
}
