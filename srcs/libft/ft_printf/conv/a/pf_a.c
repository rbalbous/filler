/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 12:07:23 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/17 19:03:35 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_toa(double *d)
{
	int		count;
	int		sign;

	count = 0;
	sign = 1;
	if ((intmax_t)(*d) == 0 && *d != 0)
	{
		while ((intmax_t)(*d) == 0)
		{
			*d = *d * 2;
			count++;
			sign = -1;
		}
	}
	while ((1 < (intmax_t)(*d) || -1 > (intmax_t)(*d)) && *d != 0)
	{
		*d /= 2;
		count++;
	}
	return (count * sign);
}

static int	pf_create(t_flags *flags, t_var *var, double d, int count)
{
	int		start;

	start = var->bufindex;
	addstr("0x", var);
	if ((pf_ftoa_hexa(d, flags, var)) == -1)
		return (-1);
	addchar('p', var);
	if (count < 0)
	{
		addchar('-', var);
		count *= -1;
	}
	else
		addchar('+', var);
	addstr(ft_itoa(count), var);
	return (0);
}

static char	initialise(t_flags *flags, t_var *var, double d)
{
	if (!(d == d))
		return (pf_nan(flags, var));
	if (d == INFINITY || d == -INFINITY)
		return (pf_infinite(d, flags, var));
	flags->len = 1;
	flags->precision += 15 * (!flags->isp) - 1;
	flags->fwidth -= 1 + flags->precision + 5
	+ (d < 0 || flags->space || flags->plus);
	flags->fwidth *= (flags->fwidth > 0);
	return (' ' + 16 * flags->zero);
}

int			pf_a(t_flags *flags, t_var *var, va_list ap)
{
	double		d;
	int			count;
	char		width;

	if (flags->bigl)
		return (pf_la(flags, var, ap));
	d = va_arg(ap, double);
	width = initialise(flags, var, d);
	count = pf_toa(&d);
	if (d < 0)
		addchar('-', var);
	else if (flags->plus || flags->space)
		addchar(flags->plus ? '+' : ' ', var);
	if (!flags->minus)
		flags->fwidth = addmchar(width, var, flags->fwidth);
	if ((pf_create(flags, var, d, count)) == -1)
		return (-1);
	if (flags->minus)
		flags->fwidth = addmchar(width, var, flags->fwidth);
	return (0);
}
