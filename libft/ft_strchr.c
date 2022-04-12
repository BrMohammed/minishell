/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:18:16 by brmohamm          #+#    #+#             */
/*   Updated: 2021/11/20 16:23:39 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( const char *str, int c )
{
	unsigned char	chr;
	char			*st;
	int				n;

	chr = c;
	st = (char *)str;
	n = 0;
	while (st[n] != '\0')
	{
		if (st[n] == chr)
		{
			return ((char*)1);
		}
		n++;
	}
		return (0);
}
