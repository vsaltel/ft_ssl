#include <fcntl.h>
#include "ssl.h"

static void	print_hash(t_ssl *ssl, t_args *arg, char *hash)
{
	if (ssl->p)
		ft_printf("%s%s\n", arg->content, hash);
	else
	{
		if (ssl->q || ssl->printed < 0)
			ft_printf("%s\n", hash);
		else if (ssl->r)
		{
			if (ssl->s)
				ft_printf("%s %s\n", hash, add_dquote(&arg->content));
			else
				ft_printf("%s %s\n", hash, arg->file);
		}
		else
		{
			if (ssl->s)
				ft_printf("%s (%s) = %s\n", get_mode(*ssl, 1),
					add_dquote(&arg->content), hash);
			else
				ft_printf("%s (%s) = %s\n", get_mode(*ssl, 1), arg->file, hash);
		}
	}
}

static void	hash_exec(t_ssl *ssl, t_args *arg)
{
	char	*hash;

	hash = NULL;
	if (ssl->md5)
		hash = md5((uint8_t *)arg->content, ft_strlen(arg->content));
	else if (ssl->sha256)
		hash = sha256(arg->content);
	print_hash(ssl, arg, hash);
	free(hash);
}

void	hash(t_ssl *ssl, t_args *arg)
{
	int	fd;

	if (arg->file)
	{
		fd = open(arg->file, O_RDONLY);
		if (fd < 0)
		{
			ft_dprintf(2, "ft_ssl: %s: %s: Cannot open.\n",
				get_mode(*ssl, 0), arg->file);
			return ;
		}
		arg->content = read_all(fd);
		if (!arg->content)
			return ;
		close(fd);
	}
	hash_exec(ssl, arg);
}
