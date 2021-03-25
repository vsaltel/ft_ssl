#include "ssl.h"

static void	catch_sigint(int signal)
{
	(void)signal;
	ft_printf("\n");
	exit(0);
}

void	interactive_mode(t_ssl *ssl)
{
	char	**tab;
	char	*str;
	int		ret;

	ret = 1;
	signal(2, &catch_sigint);
	while (ret > 0)
	{
		init_mode(ssl);
		init_opts(ssl);
		ft_printf("FT_SSL> ");
		ret = get_next_line(0, &str);
		if (ret <= 0 || !ft_strcmp("quit", str))
		{
			free(str);
			break ;
		}
		tab = ft_strsplit(str, ' ');
		free(str);
		if (tab && tab[0])
			if (set_mode(ssl, tab[0]))
				arg_loop(ssl, 1, ft_tablen(tab), tab);
		ft_tabfree(tab);
	}
}
