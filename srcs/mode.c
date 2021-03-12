#include "ssl.h"

char			*get_mode(t_ssl ssl)
{
	if (ssl.md5)
		return ("MD5");
	else if (ssl.sha256)
		return ("SHA256");
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
