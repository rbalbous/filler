/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:08:32 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/19 01:13:44 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnjoinfree(char const *s1, char const *s2, int ret, int *len)
{
	char	*str;
	int		i;

	i = 0;
	ft_printf("%d %d\n", ret, *len);
	if ((str = (char*)malloc(sizeof(str) * (*len + ret) + 1)) == 0)
		return (NULL);
	ft_strcpy(str, s1);
	while (ret > i)
	{
		str[(*len) + i] = s2[i];
		i++;
	}
	str[(*len) + i] = 0;
	(*len) += ret;
	ft_printf("%d %d\n", ret, *len);
	free((void*)s1);
	return (str);
}

int		getendline(char *store, char **line, char *tmp, int *len)
{
	if ((*line = ft_strsub(store, 0, tmp - store)) == NULL)
		return (-1);
	*len -= tmp - store;
	ft_strcpy(store, tmp + 1);
	return (1);
}

int		last_lines(char *store, char **line, int *len)
{
	if ((*line = ft_strsub(store, 0, *len)) == 0)
		return (-1);
	*len = 0;
	if (*line[0] != 0)
	{
		ft_strclr(store);
		return (1);
	}
	else
		ft_strdel(&store);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char	*store = NULL;
	char		*tmp;
	static int	len = 0;

	if (fd < 0 || fd > OPEN_MAX || BUFF_SIZE <= 0 || !line)
		return (-1);
	ft_printf("%d\n", len);
	if (store == NULL)
	{
		if ((store = malloc(1)) == NULL)
			return (-1);
		store[0] = 0;
	}
	if ((tmp = ft_strnchr(store, '\n', len)) != NULL)
	{
		ft_printf("la?\n");
		return (getendline(store, line, tmp, &len));
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		ft_printf("[%s] %d %d\n", store, len, ret);
		store = ft_strnjoinfree(store, buf, ret, &len);
		ft_printf("[%s] %d\n", store, ret);
		if ((tmp = ft_strnchr(store, '\n', len)) != NULL)
			return (getendline(store, line, tmp, &len));
	}
	if (ret == -1)
		return (-1);
	return (last_lines(store, line, &len));
}
