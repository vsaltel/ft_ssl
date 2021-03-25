#include "ssl.h"

void	init_opts(t_ssl *ssl)
{
	ssl->file_arg = 0;
	ssl->p_print = 0;
	ssl->printed = 0;
	ssl->p = 0;
	ssl->q = 0;
	ssl->r = 0;
	ssl->s = 0;
}

t_args	*new_arg(char *file, char *content)
{
	t_args	*new;

	new = (t_args *)malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->file = file;
	new->content = content;
	return (new);
}

void	free_arg(t_args *arg)
{
	free(arg->file);
	free(arg->content);
	free(arg);
}
