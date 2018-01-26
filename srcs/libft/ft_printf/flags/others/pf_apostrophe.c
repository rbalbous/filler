/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_apostrophe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 15:21:08 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/15 17:56:04 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_apostrophe(t_flags *flags)
{
	flags->dpt = *nl_langinfo(RADIXCHAR);
	flags->tsep = *nl_langinfo(THOUSEP);
	return (1);
}
