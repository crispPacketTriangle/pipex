/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:41:30 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 17:37:35 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst_c;
	unsigned const char	*src_c;

	dst_c = (unsigned char *)dest;
	src_c = (unsigned const char *)src;
	if (dst_c == src_c || n == 0)
		return (dest);
	if (dst_c < src_c || dst_c >= src_c + n)
	{
		while (n-- > 0)
			*dst_c++ = *src_c++;
	}
	else
	{
		dst_c += n - 1;
		src_c += n - 1;
		while (n > 0)
		{
			*dst_c-- = *src_c--;
			n--;
		}
	}
	return (dest);
}
