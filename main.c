#include "srcs/libft/includes/ft_printf.h"
#include <fcntl.h>

int			main(int ac, char **av)
{
	char	*str;
	int		i;

	(void)ac;
	i = 0;
	str = NULL;
	while (get_next_line(0, &str))
	{
		printf("%s\n", str);
		free(str);
		str = NULL;
	}
	return (0);
}
