#include "ssl.h"

char			*get_mode(t_ssl ssl, int maj)
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

void			set_mode(t_ssl *ssl, char *mode)
{
	if (!strcmp("md5", mode))
		ssl->md5 = 1;
	else if (!strcmp("sha256", mode))
		ssl->sha256 = 1;
}

int				check_mode(char *mode)
{
	if (!strcmp("md5", mode))
		return (1);	
	else if (!strcmp("sha256", mode))
		return (2);	
	return (0);	
}
