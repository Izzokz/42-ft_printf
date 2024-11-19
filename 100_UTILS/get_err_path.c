/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_err_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:26:56 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/19 16:26:57 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*get_err_path(void)
{
	char	*file;

	file = ft_calloc(PATH_MAX, sizeof(char));
	printf("|%s|", realpath("errmsg.txt", file));
	return (file);
}
