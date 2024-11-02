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

#include "ft_printf.h"

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

static int	points_to_pointer(void *ptr, int double_check)
{
	void	**check_ptr;
	void	***check_double_ptr;

	if (!ptr)
		return (0);
	check_ptr = (void **)ptr;
	if (!double_check || *check_ptr == NULL)
		return (*check_ptr != NULL);
	check_double_ptr = (void ***)ptr;
	if (check_double_ptr && *check_double_ptr)
		return (**check_double_ptr != NULL);
	return (0);
}

static int	call_of_duty(void *origin, char c, char *sep)
{
	int		j;
	int		len;
	void	**cast_ptr;

	len = 0;
	if (!origin)
		return (0);
	if (c != 's' && c != 'p')
		return (call_all(origin, c, sep));
	j = -1;
	cast_ptr = (void **)origin;
	while (cast_ptr[++j] != NULL)
	{
		if (points_to_pointer(cast_ptr[j], 0)
			&& !points_to_pointer(cast_ptr[j], 1))
			len += call_of_duty(cast_ptr[j], c, sep);
		else
		{
			len += call_all(cast_ptr[j], c, sep);
			if (cast_ptr[j + 1] != NULL)
				len += ft_write_s(sep);
		}
	}
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

int	ft_write_all(va_list *params, const char *str, size_t *i)
{
	size_t	len;
	char	*sep;
	int		recursive;

	len = 0;
	recursive = 0;
	if (str[*i + 1] == '.')
	{
		recursive += 1;
		*i += 1;
	}
	*i += 1;
	sep = get_sep(str, i);
	if (recursive)
		len += call_of_duty(va_arg(*params, void *), str[*i], sep);
	else
		len += call_all(va_arg(*params, void *), str[*i], sep);
	if (sep)
	{
		free(sep);
		sep = NULL;
	}
	return (len);
}
