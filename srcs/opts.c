#include "ssl.h"

void	s_opt(t_ssl *ssl, int *an, int ac, char **av)
{
	t_args	*curr;
	int		i;

	ssl->s = 1;
	i = 0;
	while (av[*an][i] && av[*an][i] != 's')
		i++;
	if (av[*an][i + 1])
		curr = new_arg(NULL, ft_strdup(av[*an] + i + 1));
	else if (*an + 1 < ac)
		curr = new_arg(NULL, ft_strdup(av[++(*an)]));
	else
	{
		ft_dprintf(2, "ft_ssl: %s: option requires an argument -- s\n",
			get_mode(*ssl, 0));
		print_usage();
		exit(1);
	}
	hash(ssl, curr);
	free_arg(curr);
	ssl->s = 0;
	ssl->printed++;
}

void	p_opt(t_ssl *ssl)
{
	t_args	*curr;

	ssl->p = 1;
	curr = arg_from_fd(0);
	close(0);
	hash(ssl, curr);
	free_arg(curr);
	ssl->p = 0;
	ssl->printed++;
	ssl->p_print++;
}

void	unknown_opt(t_ssl ssl, int i, char *arg)
{
	ft_dprintf(2, "ft_ssl: %s: illegal option -- %c\n",
		get_mode(ssl, 0), arg[i]);
	print_usage();
	exit(1);
}
