/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:13:15 by home              #+#    #+#             */
/*   Updated: 2017/11/08 21:48:38 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dest_size;
	int		i;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	dest_size = ft_strlen(dest);
	if (n == 0)
		return (src_size);
	while (src[i] != '\0' && dest_size + i < n - 1)
	{
		dest[dest_size + i] = src[i];
		i++;
	}
	dest[dest_size + i] = '\0';
	if (n < dest_size)
		return (n + src_size);
	return (dest_size + src_size);
}
