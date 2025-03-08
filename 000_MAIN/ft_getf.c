/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:36:16 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/06 15:36:18 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static t_params	*param_gsetter(t_params *set)
{
	static t_params	*pa = NULL;

	if (set)
		pa = set;
	return (pa);
}

void	ft_set_pa(t_params *set)
{
	param_gsetter(set);
}

t_params	*ft_get_pa(void)
{
	return (param_gsetter(NULL));
}

int	last_getf_len(int len)
{
	static int	lgl = 0;

	if (len >= -1)
		lgl = len;
	return (lgl);
}

char	*ft_getf(const char *format, ...)
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
	va_start(pa->args, format);
	ft_set_pa(pa);
	len = ft_process(pa);
	va_end(pa->args);
	if (len == -2)
		len = -1;
	last_getf_len(len);
	str = pa->out;
	free(pa);
	return (str);
}
