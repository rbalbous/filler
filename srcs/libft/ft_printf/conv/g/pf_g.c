/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_g.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 20:42:14 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/19 22:13:34 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_ground(char *str, t_var *var)
{
	while (*str == '0')
	{
		var->bufindex--;
		str--;
	}
	if (*str == '.')
		var->bufindex--;
	return (0);
}

int		pf_gzer(t_flags *flags, t_var *var, double d)
{
	double	tmp;
	int		count;

	tmp = d;
	count = 0;
	while ((intmax_t)tmp == 0 && d != 0)
	{
		tmp *= 10;
		count++;
	}
	if (count > 4)
	{
		if (flags->bigl)
			return (pf_spe_le(flags, var, d, -count));
		else
			return (pf_spe_e(flags, var, tmp, -count));
	}
	else
	{
		flags->precision += count + (flags->precision == -1);
		if (flags->bigl)
			return (pf_spe_fl(flags, var, d));
		else
			return (pf_spe_f(flags, var, d));
	}
}

int		pf_gpos(t_flags *flags, t_var *var, double d)
{
	int			count;

	count = 0;
	if (flags->len > flags->precision + 1)
	{
		flags->len = 1;
		count = pf_tosc(&d);
		if (flags->bigl)
			pf_spe_le(flags, var, d, count);
		else
			pf_spe_e(flags, var, d, count);
	}
	else
	{
		flags->precision -= flags->len - 1;
		flags->precision *= (flags->precision > 0);
		if (flags->bigl)
			pf_spe_fl(flags, var, d);
		else
			pf_spe_f(flags, var, d);
	}
	return (1);
}

int		pf_g(t_flags *flags, t_var *var, va_list ap)
{
	double		d;

	d = va_arg(ap, double);
	flags->g = 1;
	if (!(d == d))
		return (pf_nan(flags, var));
	if (d == INFINITY || d == -INFINITY || d == 9221120237041090560)
		return (pf_infinite(d, flags, var));
	flags->precision += (!flags->isp) * 7 - 1;
	flags->len = pf_intlen((intmax_t)d, 10) - (d < 0);
	if ((intmax_t)d == 0)
		pf_gzer(flags, var, d);
	else
		pf_gpos(flags, var, d);
	return (0);
}
