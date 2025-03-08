/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:32:03 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/06 16:32:04 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_out_add(char **pstr)
{
	t_params	*pa;
	t_ints		i;

	if (!(*pstr))
		return (-2);
	pa = ft_get_pa();
	if (pa->out)
		i.len1 = ft_strlen(pa->out);
	else
		i.len1 = 0;
	i.len2 = ft_strlen(*pstr);
	pa->out = gnlxio_ft_strjoinfree(&(pa->out), pstr);
	if (!(pa->out))
		return (-2);
	i.len = ft_strlen(pa->out);
	if (i.len1 + i.len2 != i.len)
		return (-2);
	return (i.len);
}
