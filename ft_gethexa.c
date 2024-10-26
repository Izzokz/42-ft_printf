/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:35:28 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/17 16:35:29 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_len(unsigned long nbr, int *len)
{
	if (nbr > 0)
		init_len(nbr / 16, len);
	if (nbr / 16 == 0 && nbr % 16 == 0)
		return ;
	*len += 1;
	return ;
}

static void	setchar(char **str, int i, unsigned long nbr, int up)
{
	char	nbr_to_char;

	nbr_to_char = nbr + '0';
	if (nbr > 9)
	{
		if (up)
			nbr_to_char = nbr + 'A' - 10;
		else
			nbr_to_char = nbr + 'a' - 10;
	}
	(*str)[i] = nbr_to_char;
	return ;
}

static void	recursive_core(char **str, unsigned long nbr, int i, int up)
{
	if (nbr >= 16)
		recursive_core(str, nbr / 16, i - 1, up);
	setchar(str, i, nbr % 16, up);
	return ;
}

char	*ft_gethexa(unsigned long nbr, int up)
{
	int		len;
	char	*str;

	if (!nbr)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '0';
		return (str);
	}
	len = 0;
	init_len(nbr, &len);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	recursive_core(&str, nbr, --len, up);
	return (str);
}
