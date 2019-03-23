/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:50:03 by ybereshc          #+#    #+#             */
/*   Updated: 2018/10/23 19:50:05 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t n)
{
	return (ft_bzero(malloc(n), n));
}

void	*ft_free(int n, ...)
{
	va_list	ap;

	if (n < 1)
		return (0);
	va_start(ap, n);
	while (n--)
		free(va_arg(ap, void*));
	va_end(ap);
	return (0);
}
