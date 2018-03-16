/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   added_function_visu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:21:37 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/16 16:34:56 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		display_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void		next_line(int fd, char **line)
{
	if (get_next_line(fd, line) == -1)
		display_error("Read error");
}
