#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char *str)
{
	int i;
	char *new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char *strjoin(char *str, char *str2)
{
	int size;
	char *new;
	int i = 0;
	int j = 0;

	size = ft_strlen(str) + ft_strlen(str2);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (str2[j])
		new[i++] = str2[j++];
	new[size] = '\0';
	return (new);
}

int	get_next_line(char **line)
{
	int by;
	char buf[2];
	char *tmp;

	buf[1] = '\0';
	*line = ft_strdup("");
	if (!(*line))
	{
		*line = NULL;
		return (-1);
	}
	by = read(0, buf, 1);
	while (by > 0 && buf[0] != '\0' && buf[0] != '\n')
	{
		tmp = *line;
		*line = strjoin(tmp, buf);
		free(tmp);
		by = read(0, buf, 1);
	}
	if (by > 0 && buf[0] == '\n')
		return (1);
	else if (by > 0 && buf[0] == '\0')
		return (0);
	else if (by == 0)
		return (0);
	else
		return (-1);
}
