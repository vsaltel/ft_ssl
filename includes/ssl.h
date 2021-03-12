#ifndef SSL_H
# define SSL_H

# define OPTIONS "pqrs"

# include <stdio.h>
# include "libft.h"

typedef struct			s_ssl
{
	int				md5;
	int				sha256;
	int				p;
	int				q;
	int				r;
	int				s;
}						t_ssl;


typedef struct			s_args
{
	int				fd;
	char			*file;
	char			*content;
	struct s_args	*next;
}						t_args;

/*
** srcs/opts.c
*/

void			init_ssl(t_ssl *ssl);
void			get_opts(t_ssl *ssl, int an, int ac, char **av);
int				check_opts(int an, int ac, char **av);

/*
** srcs/mode.c
*/

char			*get_mode(t_ssl ssl);
void			set_mode(t_ssl *ssl, char *mode);
int				check_mode(char *mode);

/*
** srcs/args.c
*/

void		set_args(t_args **beg, int argn, int argc, char **argv, int content_type);
void		free_args(t_args *args);
t_args		*arg_from_fd(int fd);

/*
** srcs/usage.c
*/

void			print_usage(void);
void			print_mode_err(char *mode);

/*
** srcs/ssl.c
*/

void			hash_loop(t_ssl ssl, t_args *args);

/*
** srcs/sha256.c
*/

char			*sha256(char *input);

/*
** srcs/md5.c
*/

char			*md5(char *input);

/*
** srcs/utils.c
*/

char			*read_all(int fd);
char			*add_dquote(char **str);
void			print_args(t_args *args);
void			print_mode(t_ssl ssl);
void			print_opts(t_ssl ssl);

#endif
