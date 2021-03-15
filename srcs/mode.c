#include "ssl.h"

char	*get_mode(t_ssl ssl, int maj)
{
	if (ssl.md5)
	{
		if (maj)
			return ("MD5");
		return ("md5");
	}
	else if (ssl.sha256)
	{
		if (maj)
			return ("SHA256");
		return ("sha256");
	}
	return (NULL);
}

int		set_mode(t_ssl *ssl, char *mode)
{
	if (!strcmp("md5", mode))
	{
		ssl->md5 = 1;
		return (1);
	}
	else if (!strcmp("sha256", mode))
	{
		ssl->sha256 = 1;
		return (1);
	}
	ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n", mode); 
	return (0);
}

void				init_mode(t_ssl *ssl)
{
	ssl->md5 = 0;
	ssl->sha256 = 0;
}
