#include "ssl.h"

void	print_usage(void)
{
	ft_dprintf(2, "ft_ssl usage: ft_ssl command [-%s] [args]\n", OPTIONS);
}

void	print_mode_err(char *mode)
{
	ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n", mode);
	ft_dprintf(2, "\nStandard commands:\n\nMessage Digest commands:\n");
	ft_dprintf(2, "md5\nsha256\n\nCipher commands\n");
}
