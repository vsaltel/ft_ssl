#include "ssl.h"

char	*read_all(int fd)
{
	char	buf[BUFF_SIZE];
	char	*str;
	int		ret;

	str = strdup("");
	while ((ret = read(fd, &buf, BUFF_SIZE - 1)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strfjoin(str, buf, str);	
		if (ret < BUFF_SIZE - 1)
			break ;
	}
	if (ret == -1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

void	print_args(t_args *args)
{
	int	i;

	i = 1;
	while (args)
	{
		ft_printf("ARG%d:'%s' -> '%s'\n", i, args->file, args->content);
		args = args->next;
		i++;
	}
}

void	print_mode(t_ssl ssl)
{
		ft_printf("MODE: %s\n", ssl.md5 ? "md5" : "sha256");
}

void	print_opts(t_ssl ssl)
{
		ft_printf("OPTS: %s%s%s%s\n", ssl.p ? "p" : "", ssl.q ? "q" : "", ssl.r ? "r" : "", ssl.s ? "s" : "");
}
