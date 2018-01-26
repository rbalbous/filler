/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:44:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/20 19:18:06 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_tosc(double *d)
{
	int		count;

	count = 0;
	if (*d == 0)
		return (0);
	if ((intmax_t)(*d) == 0)
	{
		while ((intmax_t)(*d) == 0)
		{
			*d = *d * 10;
			count++;
		}
		count *= -1;
	}
	else
	{
		while ((intmax_t)(*d) < -10 || (intmax_t)(*d) > 10)
		{
			*d /= 10;
			count++;
		}
	}
	return (count);
}

static int	pf_create(t_flags *flags, t_var *var, double d, int count)
{
	int		start;

	start = var->bufindex;
	pf_ftoa(d, flags, var);
	pf_round(&var->buf[var->bufindex - 1], flags, var);
	addchar('e', var);
	if (count < 0)
	{
		addchar('-', var);
		count *= -1;
	}
	else
		addchar('+', var);
	if (count < 10)
		addchar('0', var);
	addstr(ft_itoa(count), var);
	return (0);
}

static int	initialise(t_flags *flags, t_var *var, double d)
{
	if (!(d == d))
		return (pf_nan(flags, var));
	if (d == INFINITY || d == -INFINITY)
		return (pf_infinite(d, flags, var));
	flags->len = 1;
	flags->precision += 7 * (!flags->isp);
	flags->fwidth -= 1 + flags->precision * (!flags->isp) - 5
	+ (d < 0 || flags->space || flags->plus);
	flags->fwidth *= (flags->fwidth > 0);
	return (0);
}

int			pf_e(t_flags *flags, t_var *var, va_list ap)
{
	double		d;
	int			count;

	if (flags->bigl)
		return (pf_le(flags, var, ap));
	else
		d = va_arg(ap, double);
	count = pf_tosc(&d);
	initialise(flags, var, d);
	pf_spe_e(flags, var, d, count);
	return (1);
}

int			pf_spe_e(t_flags *flags, t_var *var, double d, int count)
{
	char		width;

	width = ' ' + 16 * flags->zero;
	flags->fwidth -= 5 * (flags->g || flags->fwidth != 0);
	flags->fwidth *= (flags->fwidth > 0);
	if (d < 0)
		addchar('-', var);
	else if (flags->plus || flags->space)
		addchar(flags->plus ? '+' : ' ', var);
	if (!flags->minus)
	{
		flags->fwidth = addmchar(width, var, flags->fwidth);
		pf_create(flags, var, d, count);
	}
	else
	{
		pf_create(flags, var, d, count);
		flags->fwidth = addmchar(width, var, flags->fwidth);
	}
	return (0);
}
