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

#include "ft_printf.h"

int	ft_printf_fd(const char *str, int fd, ...)
{
	va_list	params;

	if (!str || fd < 0)
		return (-1);
	g_fd = fd;
	va_start(params, fd);
	return (ft_process(str, &params));
}

int	ft_printf(const char *str, ...)
{
	va_list	params;

	if (!str)
		return (-1);
	g_fd = 1;
	va_start(params, str);
	return (ft_process(str, &params));
}
