#include <fcntl.h>
#include "ssl.h"

static void	print_hash(t_ssl ssl, t_args *arg, char *hash)
{
	if (!arg->fd || ssl.q)
		ft_printf("%s\n", hash);
	else
	{
		if (ssl.r)
			ft_printf("%s %s\n", hash, ssl.s ? add_dquote(&arg->content) : arg->file);
		else
			ft_printf("%s (%s) = %s\n", get_mode(ssl), ssl.s ? add_dquote(&arg->content) : arg->file, hash);
	}
}

static void	hash_exec(t_ssl ssl, t_args *arg)
{
	char	*hash;

	hash = NULL;
	if (ssl.md5)
		hash = md5((uint8_t *)arg->content, ft_strlen(arg->content));
	else if (ssl.sha256)
		hash = sha256(arg->content);
	print_hash(ssl, arg, hash);
	free(hash);
}

void		hash_loop(t_ssl ssl, t_args *args)
{
	while (args)
	{
		if (args->file)
		{
			if ((args->fd = open(args->file, O_RDONLY)) < 0)
			{
				ft_dprintf(2, "ft_ssl: %s: Cannot open.\n", args->file);
				args = args->next;
				continue ;
			}
			if (!(args->content = read_all(args->fd)))
				return ;
			close(args->fd);
		}
		hash_exec(ssl, args);
		args = args->next;
	}
}
