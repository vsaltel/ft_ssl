#ifndef SSL_H
# define SSL_H

# define OPTIONS "pqrs"

# include <stdio.h>
# include "libft.h"

typedef struct s_ssl
{
	int				p_print;
	int				printed;
	int				md5;
	int				sha256;
	int				p;
	int				q;
	int				r;
	int				s;
}				t_ssl;

typedef struct s_args
{
	char			*file;
	char			*content;
}				t_args;

/*
** srcs/mode.c
*/

char			*get_mode(t_ssl ssl, int maj);
int				set_mode(t_ssl *ssl, char *mode);
void			init_mode(t_ssl *ssl);
int				check_mode(char *mode);

/*
** srcs/args_utils.c
*/

void			init_opts(t_ssl *ssl);
t_args			*new_arg(char *file, char *content);
void			free_arg(t_args *arg);

/*
** srcs/args.c
*/

t_args			*arg_from_fd(int fd);
t_args			*get_arg(t_ssl *ssl, int *an, int ac, char **av);

/*
** srcs/usage.c
*/

void			print_usage(void);
void			print_mode_err(char *mode);

/*
** srcs/opts.c
*/

void			s_opt(t_ssl *ssl, int *an, int ac, char **av);
void			p_opt(t_ssl *ssl);
void			unknown_opt(t_ssl ssl, int i, char *arg);

/*
** srcs/ssl.c
*/

void			hash(t_ssl *ssl, t_args *arg);

/*
** srcs/utils.c
*/

char			*read_all(int fd);
char			*add_dquote(char **str);
void			print_args(t_args *args);
void			print_mode(t_ssl ssl);
void			print_opts(t_ssl ssl);

#endif
