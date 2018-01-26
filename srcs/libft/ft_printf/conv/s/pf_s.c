/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:36:44 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/09 18:58:57 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_isnull(t_flags *flags, t_var *var)
{
	if (!flags->isp)
		return (addnull(var));
	else
		return (pf_empty_s(flags, var));
}

int		pf_s(t_flags *flags, t_var *var, va_list ap)
{
	char	*tmp;
	char	width;

	if (flags->conv == l)
		return (pf_cap_s(flags, var, ap));
	tmp = va_arg(ap, char*);
	if (tmp == NULL)
		return (pf_isnull(flags, var));
	flags->len = ft_strlen(tmp);
	width = ' ' + 16 * (flags->zero);
	if (flags->precision >= 0 && flags->precision < flags->len)
		flags->len = flags->precision;
	flags->fwidth -= flags->len;
	flags->fwidth *= (flags->fwidth > 0);
	if (flags->minus == 0)
	{
		flags->fwidth = addmchar(width, var, flags->fwidth);
		addnstr(tmp, (size_t)flags->len, var);
	}
	else
	{
		addnstr(tmp, (size_t)flags->len, var);
		flags->fwidth = addmchar(width, var, flags->fwidth);
	}
	return (0);
}
