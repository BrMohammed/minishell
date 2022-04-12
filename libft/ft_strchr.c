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
	char	*s;
	int		len;

	s = (char *)str;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*s++ == (char)c)
			return (s - 1);
	}
	return (NULL);
}
