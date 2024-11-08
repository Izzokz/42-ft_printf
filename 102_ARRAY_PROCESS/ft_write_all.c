/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:49:18 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/02 09:49:19 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	call_all(void *ptr, char c, char *sep)
{
	if (c == 'd' || c == 'i')
		return (ft_process_all_d((int *)ptr, sep));
	if (c == 's')
		return (ft_process_all_s((char **)ptr, sep));
	if (c == 'u')
		return (ft_process_all_u((unsigned int *)ptr, sep));
	if (c == 'p')
		return (ft_process_all_p((unsigned long *)ptr, sep));
	return (0);
}

static int	call_of_duty(void **origin, int depth, char c, char *sep)
{
	int		j;
	int		len;

	len = 0;
	if (!origin || depth == 0)
		return (0);
	j = -1;
	if (depth > 1)
	{
		while (origin[++j] != NULL)
		{
			len += call_of_duty(origin[j], depth - 1, c, sep);
			if (origin[j + 1] != NULL && sep)
				len += ft_write_s(sep);
		}
	}
	else
		len += call_all(origin, c, sep);
	return (len);
}

static char	*get_sep(const char *str, size_t *i)
{
	size_t	j;
	size_t	k;
	char	*sep;

	sep = NULL;
	j = *i;
	if (str[j] != '[')
		return (sep);
	while (str[++j] && str[j] != ']')
		;
	if (str[j] != ']' || str[j - 1] == '[')
		return (NULL);
	*i += 1;
	sep = ft_calloc(j - *i + 1, sizeof(char));
	k = 0;
	while (*i < j)
	{
		sep[k] = str[*i];
		*i += 1;
		k++;
	}
	*i += 1;
	return (sep);
}

static int	get_rdepth(const char *str, size_t *i)
{
	++(*i);
	if (str[*i] == '.')
	{
		if (str[*i + 1] >= '0' && str[*i + 1] <= '9')
		{
			*i += 2;
			return (str[*i - 1] - '0' + 1);
		}
		else
			return (-1);
	}
	return (0);
}

int	ft_write_all(va_list *params, const char *str, size_t *i)
{
	size_t	len;
	char	*sep;
	int		recursive;
	void	*ptr;

	len = 0;
	recursive = get_rdepth(str, i);
	if (recursive == -1)
		return (0);
	sep = get_sep(str, i);
	ptr = va_arg(*params, void *);
	if (!ptr)
		return (0);
	if (recursive)
		len += call_of_duty(ptr, recursive - 1, str[*i], sep);
	else
		len += call_all(ptr, str[*i], sep);
	if (sep)
	{
		free(sep);
		sep = NULL;
	}
	return (len);
}
