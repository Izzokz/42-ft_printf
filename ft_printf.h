/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:47:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/16 14:47:47 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_gethexa(unsigned long nbr, int up);
int		ft_write_c(char value);
int		ft_write_s(char *value);
int		ft_write_d(int value);
int		ft_write_x(int value);
int		ft_write_xup(int value);
int		ft_write_p(unsigned long value);
int		ft_write_u(unsigned int value, int *len);
int		ft_process(const char *str, va_list *params);
int		ft_printf(const char *str, ...);

#endif
