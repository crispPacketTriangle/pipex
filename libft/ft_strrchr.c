/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:35:34 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 17:38:50 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int					i;
	char				*f;
	unsigned char		c_c;
	const unsigned char	*s_s;

	c_c = (unsigned char)c;
	s_s = (const unsigned char *)s;
	f = NULL;
	i = 0;
	while (s_s[i])
	{
		if (s_s[i] == c_c)
		{
			f = (char *)&s_s[i];
		}
		i++;
	}
	if (c_c == '\0')
	{
		f = (char *)&s_s[i];
		return (f);
	}
	return (f);
}
