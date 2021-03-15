#include "ssl.h"

static int			find_first_arg(int argn, int argc, char **argv)
{
	while (argn < argc && argv[argn][0] && argv[argn][0] == '-')
		argn++;
	return (argn);
}

static t_args		*new_arg(char *file, char *content)
{
	t_args	*new;

	if (!(new = (t_args *)malloc(sizeof(t_arg))))
		return (NULL);
	new->file = file;
	new->content = content;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

void				set_args(t_args **beg, int argn, int argc, char **argv, int content_type)
{
	t_args	*curr;

	curr = NULL;
	argn = find_first_arg(argn, argc, argv);
	if (argn < argc)
	{
		if (content_type)
			curr = new_arg(NULL, strdup(argv[argn]));
		else
			curr = new_arg(strdup(argv[argn]), NULL);
	}
	*beg = curr;
	while (++argn < argc)
	{
		curr->next = new_arg(strdup(argv[argn]), NULL);
		curr = curr->next;
	}
}

t_args				*arg_from_fd(int fd)
{
	char	*str;	
	t_args	*new;

	if (!(str = read_all(fd)))
		return (NULL);
	new = new_arg(NULL, str);
	new->fd = 0;
	return (new);
}

void				free_args(t_args *args)
{
	t_args	*tmp;

	while (args)
	{
		tmp = args->next; 
		free(args->file);
		free(args->content);
		free(args);
		args = tmp;
	}
}
