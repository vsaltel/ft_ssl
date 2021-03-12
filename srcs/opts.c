#include "ssl.h"

static void		set_opt(t_ssl *ssl, char o)
{
	if (o == 'p')
		ssl->p = 1;
	else if (o == 'q')
		ssl->q = 1;
	else if (o == 'r')
		ssl->r = 1;
	else if (o == 's')
		ssl->s = 1;
}

void			get_opts(t_ssl *ssl, int an, int ac, char **av)
{
	int		x;

	while (an < ac && av[an][0] && av[an][0] == '-')
	{
		x = 1;
		while (av[an][x])
		{
			set_opt(ssl, av[an][x]);
			x++;
		}
		an++;
	}
}

int				check_opts(int an, int ac, char **av)
{
	int		x;

	while (an < ac && av[an][0] && av[an][0] == '-')
	{
		x = 1;
		while (av[an][x])
		{
			if (!strchr(OPTIONS, av[an][x]))
				return (1);
			x++;
		}
		an++;
	}
	return (0);
}

void			init_ssl(t_ssl *ssl)
{
	ssl->p = 0;
	ssl->q = 0;
	ssl->r = 0;
	ssl->s = 0;
	ssl->md5 = 0;
	ssl->sha256 = 0;
}
