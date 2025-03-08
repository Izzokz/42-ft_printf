/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:55:25 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/17 15:55:26 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_write_c(char value)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (-2);
	str[0] = value;
	str[1] = 0;
	return (ft_out_add(&str));
}

int	ft_write_s(char *value)
{
	if (!value)
		return (ft_out_add(&(char *){ft_strdup("(null)")}));
	return (ft_out_add(&(char *){ft_strdup(value)}));
}
