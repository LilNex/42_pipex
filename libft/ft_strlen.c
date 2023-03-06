/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:19:59 by ichaiq            #+#    #+#             */
/*   Updated: 2023/01/12 20:38:20 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "libft.h"


size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

size_t	ft_lstlen(const char **c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	
	return (i);
}
