#include <unistd.h>

int		check_str1(char *str, char str2)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == str2)
			return (1);
		i++;
	}
	return (0);
}

int		check_itself(char *str, int i)
{
	int j;

	j = i - 1;
	while (j >= 0)
	{
		if (str[i] == str[j])
			return (1);
		j--;
	}
	return (0);
}

void	ft_union(char *str, char *str2)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!check_itself(str, i))
			write(1, &str[i], 1);
		i++;
	}
	i = 0;
	while (str2[i])
	{
		if (!check_itself(str2, i) && !check_str1(str, str2[i]))
			write(1, &str2[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac != 3)
		write(1, "\n", 1);
	else
	{
		ft_union(av[1], av[2]);
		write(1, "\n", 1);
	}
	return (0);
}
