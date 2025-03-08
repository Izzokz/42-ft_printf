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
#include "../errmsg.h"

static char	*ft_vgetf(const char *format, va_list args)
{
	t_params	*pa;
	int			len;
	char		*str;

	if (!format)
		return (NULL);
	pa = malloc(sizeof(t_params));
	if (!pa)
		return (NULL);
	*pa = (t_params){.i = -1, .str = format, .out = NULL};
	va_copy(pa->args, args);
	ft_set_pa(pa);
	len = ft_process(pa);
	va_end(pa->args);
	if (len == -2)
		len = -1;
	str = pa->out;
	free(pa);
	last_getf_len(len);
	return (str);
}

/*
Parameters:
	- const char *str;
	- int fd;
	- (args);
Behaviour:
	Acts like dprintf() with more format specifiers.
	NOTE : Every format specifier is explained on GitHub
Returns:
	Number of printed characters
*/
int	ft_printf_fd(const char *format, int fd, ...)
{
	va_list	args;
	char	*str;

	if (!format || fd < 0)
		return (-1);
	va_start(args, fd);
	str = ft_vgetf(format, args);
	va_end(args);
	if (!str)
		return (-1);
	write(fd, str, ft_strlen(str));
	free(str);
	return (last_getf_len(LGL_GET));
}

/*
Parameters:
	- const char *str;
	- (args);
Behaviour:
	Acts like printf() with more format specifiers.
	NOTE : Every format specifier is explained on GitHub
Returns:
	Number of printed characters
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*str;

	if (!format)
		return (-1);
	va_start(args, format);
	str = ft_vgetf(format, args);
	va_end(args);
	if (!str)
		return (-1);
	write(1, str, ft_strlen(str));
	free(str);
	return (last_getf_len(LGL_GET));
}

static int	ft_perr_add(char **pstr1, char **pstr2)
{
	t_ints	i;

	if (!(*pstr1) || !(*pstr2))
	{
		free(*pstr1);
		free(*pstr2);
		return (-1);
	}
	i.len1 = ft_strlen(*pstr1);
	i.len2 = ft_strlen(*pstr2);
	*pstr1 = gnlxio_ft_strjoinfree(pstr1, pstr2);
	if (!(*pstr1))
		return (-1);
	i.len = ft_strlen(*pstr1);
	if (i.len != i.len1 + i.len2)
	{
		free(*pstr1);
		return (-1);
	}
	return (i.len);
}

/*
Parameters:
	- const char *msg;
	- int fd;
	- (args);
Behaviour:
	Will print "<msg>: " before printing the error.
	NOTE : <fd> is necessary because it is usually used in log files.
Returns:
	Number of printed characters
Examples:
	ft_printf_err(NULL, 0) >>> "Remote I/O error"
	ft_printf_err("err", 0) >>> "err: Socket type not supported"
	ft_printf_err("errid[%d]", 0, i) >>> "errid[778]: Success"
*/
int	ft_printf_err(const char *msg, int fd, ...)
{
	va_list	args;
	char	*str;
	char	err;
	int		len;

	err = 0;
	if (msg)
	{
		va_start(args, fd);
		str = ft_vgetf(msg, args);
		va_end(args);
		err = last_getf_len(LGL_GET) == -1;
		if (ft_perr_add(&str, &(char *){ft_strdup(": ")}) < 0)
			return (-1);
	}
	if (ft_perr_add(&str, &(char *){ft_strdup(g_errmsg[errno])}) < 0)
		return (-1);
	err += last_getf_len(LGL_GET) == -1;
	len = ft_strlen(str);
	write(fd, str, len);
	free(str);
	if (err)
		return (-1);
	return (len);
}
