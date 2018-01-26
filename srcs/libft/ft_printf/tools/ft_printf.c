/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 12:14:24 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/19 15:51:37 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_parserror(t_var *var, va_list ap)
{
	write(1, var->buf, var->error);
	va_end(ap);
	return (-1);
}

void	init_conv(int (*f[256])())
{
	f['s'] = pf_s;
	f['c'] = pf_c;
	f['S'] = pf_cap_s;
	f['p'] = pf_lx;
	f['d'] = pf_d;
	f['D'] = pf_cap_d;
	f['i'] = pf_d;
	f['o'] = pf_o;
	f['O'] = pf_cap_o;
	f['u'] = pf_u;
	f['U'] = pf_cap_u;
	f['x'] = pf_x;
	f['X'] = pf_cap_x;
	f['C'] = pf_cap_c;
	f['%'] = pf_percent;
	f['*'] = pf_wildcard;
	f['b'] = pf_b;
	f['f'] = pf_f;
	f['F'] = pf_cap_f;
	f['n'] = pf_n;
	f['e'] = pf_e;
	f['E'] = pf_cap_e;
	f['$'] = pf_dollar;
	f['\''] = pf_apostrophe;
	f['g'] = pf_g;
}

void	init_flags(int (*f[256])(), int i)
{
	while (++i < 256)
		f[i] = pf_percent;
	i = -1;
	f['0'] = ft_zero;
	f['.'] = ft_preci;
	f['+'] = ft_plus;
	f['-'] = ft_minus;
	f['#'] = pf_hashtag;
	f[' '] = ft_space;
	while (++i < 9)
		f['1' + i] = pf_fwidth;
	f['h'] = pf_h;
	f['l'] = pf_l;
	f['j'] = ft_j;
	f['z'] = pf_z;
	f['a'] = pf_a;
	f['A'] = pf_cap_a;
	f['L'] = pf_cap_l;
	f['q'] = pf_q;
	f['r'] = pf_r;
	f['k'] = pf_k;
	f['m'] = pf_m;
	f['w'] = pf_w;
	f['W'] = pf_cap_w;
	init_conv(f);
}

void	initialise_var(t_var *var, va_list ap, int (*f[256])())
{
	int		i;

	i = -1;
	var->index = -1;
	var->bufindex = 0;
	var->dol = 0;
	var->count = 0;
	var->error = 0;
	va_copy(var->begin, ap);
	ft_bzero(var->buf, BUFF_SIZE);
	if (f[0] == NULL)
		init_flags(f, i);
}

int			ft_printf(const char *str, ...)
{
	static int	(*f[256])() = {NULL};
	va_list		ap;
	t_var		var;
	int			ret;

	va_start(ap, str);
	initialise_var(&var, ap, f);
	while (str[++var.index])
	{
		if (str[var.index] == '%' && str[var.index + 1])
		{
			if ((ret = parse((t_uint8*)str, &var, ap, f)) < 0)
			{
				if (ret == -2)
					break ;
				return (pf_parserror(&var, ap));
			}
			var.error = var.bufindex;
		}
		else if (str[var.index] != '%')
			addchar(str[var.index], &var);
	}
	va_end(ap);
	return (write(1, var.buf, var.bufindex));
}
