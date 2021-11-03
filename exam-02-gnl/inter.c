#include <unistd.h>

int		check_behind(char *str, int i)
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

void	inter(char *str, char *str2)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str[i] == str2[j] && !check_behind(str, i))
			{
				write(1, &str[i], 1);
				break;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
		write(1, "\n", 1);
	else
	{
		inter(av[1], av[2]);
		write(1, "\n", 1);
	}
	return (0);
}
