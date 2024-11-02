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

static int	call_all(void *ptr, const char *str, size_t *i, char *sep)
{
	int	len;

	if (str[*i] == 'd' || str[*i] == 'i')
		return (ft_process_all_d((int *)ptr, str, i, sep));
	if (str[*i] == 's')
		return (ft_process_all_s((char **)ptr, str, i, sep));
	if (str[*i] == 'u')
		return (ft_process_all_u((unsigned int *)ptr, str, i, sep));
	if (str[*i] == 'p')
		return (ft_process_all_p(ptr, str, i, sep));
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
	return (**check_double_ptr != NULL);
}

static int	call_of_duty(void *origin, const char *str, size_t *i, char *sep)
{
	int		j;
	int		len;
	void	**cast_ptr;

	len = 0;
	if (!origin)
		return (0);
	j = -1;
	cast_ptr = (void **)origin;
	while (cast_ptr[++j] != NULL)
	{
		if (points_to_pointer(cast_ptr[j], 0)
			&& !points_to_pointer(cast_ptr[j], 1))
			len += call_of_duty(cast_ptr[j], str, i, sep);
		else
			len += call_all(cast_ptr[j], str, i, sep);
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
	if (str[++j] != '[')
		return (sep);
	while (str[++j] && str[j] != ']')
		;
	if (str[j] != ']')
		return (-1);
	*i += 2;
	sep = ft_calloc(j - *i + 1, sizeof(char));
	k = 0;
	while (*i < j)
	{
		sep[*i] = str[k];
		*i += 1;
		k++;
	}
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
		len += call_all(va_arg(*params, void *), str, i, sep);
	len += call_of_duty(va_arg(*params, void *), str, i, sep);
	if (sep)
	{
		free(sep);
		sep = NULL;
	}
	return (len);
}
