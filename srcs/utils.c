#include "ssl.h"

char	*read_all(int fd)
{
	char	buf[BUFF_SIZE];
	char	*str;
	int		ret;

	str = ft_strdup("");
	ret = read(fd, &buf, BUFF_SIZE - 1);
	while (ret > 0)
	{
		buf[ret] = '\0';
		str = ft_strfjoin(str, buf, str);
		ret = read(fd, &buf, BUFF_SIZE - 1);
	}
	if (ret == -1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*add_dquote(char **str)
{
	char	*new;
	int		len;

	if (!str)
		return (NULL);
	if (!*str || !*str[0])
		ft_strdup("\"\"");
	len = ft_strlen(*str);
	new = malloc(len + 3);
	if (!new)
		return (NULL);
	new[0] = '"';
	ft_strcpy(new + 1, *str);
	new[len + 1] = '"';
	new[len + 2] = '\0';
	free(*str);
	*str = new;
	return (new);
}
