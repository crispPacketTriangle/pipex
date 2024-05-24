/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:07:40 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 17:37:22 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_c;
	unsigned char	c_c;

	s_c = (unsigned char *)s;
	c_c = (unsigned char)c;
	i = 0;
	while (n--)
	{
		if (s_c[i] == c_c)
		{
			return (&s_c[i]);
		}
		i++;
	}
	return (NULL);
}
