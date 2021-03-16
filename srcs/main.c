#include "ssl.h"

static void	empty_hash(t_ssl *ssl)
{
	int		tmp;
	t_args	*arg;

	tmp = ssl->printed;
	ssl->printed = -1;
	arg = new_arg(NULL, ft_strdup(""));
	hash(ssl, arg);
	free(arg);
	ssl->printed = tmp;
}

static void	arg_loop(t_ssl *ssl, int an, int ac, char **av)
{
	t_args	*arg;

	while (an < ac)
	{
		arg = get_arg(ssl, &an, ac, av);
		if (arg)
		{
			hash(ssl, arg);
			ssl->printed++;
			free_arg(arg);
		}
		an++;
	}
	if (!ssl->printed)
	{
		ssl->printed = -1;
		arg = arg_from_fd(0);
		hash(ssl, arg);
		free_arg(arg);
	}
	if (ssl->printed == 1 && ssl->p_print && (ssl->q || ssl->r))
		empty_hash(ssl);
}

int	main(int argc, char **argv)
{
	t_ssl	ssl;

	init_mode(&ssl);
	init_opts(&ssl);
	if (!set_mode(&ssl, argv[1]))
		return (1);
	arg_loop(&ssl, 2, argc, argv);
	return (0);
}
