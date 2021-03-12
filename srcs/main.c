#include "ssl.h"

int		check(int argc, char **argv)
{
	if (argc < 2)
	{
		print_usage();
		return (1);
	}
	if (!check_mode(argv[1]))
	{
		print_mode_err(argv[1]);
		return (2);
	}
	if (check_opts(2, argc, argv))
	{
		print_usage();
		return (3);
	}
	return (0);
}

int		arg_from_stdin(t_ssl ssl, t_args **args)
{
	t_args	*tmp;

	if (!args)
		return (4);
	if (!*args || ssl.p)
	{
		tmp = arg_from_fd(0);
		if (!tmp)
			return (5);
		if (args && *args)
			tmp->next = *args;
		*args = tmp;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_ssl	ssl;
	t_args	*args;
	int		ret;

	if ((ret = check(argc, argv)))
		return (ret);
	args = NULL;
	init_ssl(&ssl);
	set_mode(&ssl, argv[1]);
	get_opts(&ssl, 2, argc, argv);
	//print_mode(ssl);
	//print_opts(ssl);
	set_args(&args, 2, argc, argv, ssl.s);
	if ((ret = arg_from_stdin(ssl, &args)))
		return (ret);
	//print_args(args);
	hash_loop(ssl, args);
	free_args(args);
	return (0);
}
