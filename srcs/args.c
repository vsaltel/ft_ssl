#include "ssl.h"

t_args			*arg_from_fd(int fd)
{
	char	*str;	
	t_args	*new;

	if (!(str = read_all(fd)))
		return (NULL);
	new = new_arg(NULL, str);
	return (new);
}

static void		get_opt(t_ssl *ssl, int *an, int ac, char **av)
{
	int	i;

	i = 0;
	while (av[*an][++i])
	{
		if (av[*an][i] == 's')
		{
			s_opt(ssl, an, ac, av);
			return ;
		}
		else if (av[*an][i] == 'p')
			p_opt(ssl);
		else if (av[*an][i] == 'r')
			ssl->r = 1;
		else if (av[*an][i] == 'q')
			ssl->q = 1;
		else
			unknown_opt(*ssl, i, av[*an]);
	}
}

t_args			*get_arg(t_ssl *ssl, int *an, int ac, char **av)
{

	if (!ssl->file_arg && av[*an][0] == '-')
	{
		get_opt(ssl, an, ac, av);
		return (NULL);
	}
	ssl->file_arg++;
	return (new_arg(strdup(av[*an]), NULL));
}
