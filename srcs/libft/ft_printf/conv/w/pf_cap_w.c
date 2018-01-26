/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_cap_w.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:17:07 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/17 17:30:20 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_cap_w(t_flags *flags, t_var *var, va_list ap)
{
	char	*s;
	char	*result;
	int		keylen;
	int		ind;
	int		i;

	s = va_arg(ap, char*);
	flags->len = ft_strlen(s);
	keylen = ft_strlen(KEY);
	ind = 0;
	i = 0;
	if (!(result = malloc(sizeof(*result) * (flags->len + 1))))
		return (-1);
	while (ind < flags->len)
	{
		i *= (i != keylen);
		result[ind] = (s[ind] - KEY[i] + 95) % 95 + 32;
		ind++;
		i++;
	}
	result[ind] = 0;
	addnstr(result, flags->len, var);
	free(result);
	return (0);
}
