/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:51:15 by gpetit            #+#    #+#             */
/*   Updated: 2021/06/04 16:45:34 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct	s_size
{
	char back_char;
	int	width;
	int height;
}	t_size;

typedef	struct	s_rectangle
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	rec_char;
}	t_rectangle;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
		ft_putchar(str[i++]);
}

int	get_size(FILE *file_ptr, t_size *size, char **matrice)
{
	int ret;

	ret = fscanf(file_ptr, "%d %d %c\n", &size->width, &size->height, &size->back_char);
	if (ret != 3 || (size->width <= 0 || size->width > 300 || size->height <= 0 || size->height > 300))
		return (1);
	else
	{
		*matrice = malloc(sizeof(char) * (size->width * size->height + 1));
		if (!(*matrice))
			return (1);
		(*matrice)[size->width * size->height] = 0;
		memset(*matrice, size->back_char, size->width * size->height);
		return (0);
	}
}

void	write_or_not(t_size *size, t_rectangle *rectangle, char **matrice, int a, int b)
{
	float x = a;
	float y = b;
	
	if (x >= rectangle->x && x <= rectangle->x + rectangle->width && y >= rectangle->y && y <= rectangle->y + rectangle->height)
	{
		if (rectangle->type == 'R')
			(*matrice)[b * size->width + a] = rectangle->rec_char;
		else
		{
			if (!(x - 1 >= rectangle->x && x + 1 <= rectangle->x + rectangle->width && y - 1 >= rectangle->y && y + 1 <= rectangle->y + rectangle->height))
				(*matrice)[b * size->width + a] = rectangle->rec_char;
		}
	}
	else
		return ;
}

int	register_in_matrice(t_size *size, t_rectangle *rectangle, char **matrice)
{
	int x; 
	int y;
	if (rectangle->type != 'R' && rectangle->type != 'r')
		return (1);
	else if (rectangle->width <= 0 || rectangle->height <= 0)
		return (1);
	y = 0;
	while (y < size->height)
	{
		x = 0;
		while (x < size->width)
		{
			write_or_not(size, rectangle, matrice, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

void	print_matrice(t_size *size, char *matrice)
{
	int i;
	int j;

	i = 0;
	while (i < size->height)
	{
		j = 0;
		while (j < size->width)
		{
			ft_putchar(matrice[i * size->width + j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}

}

int	execute_paint(FILE *file_ptr)
{
	int ret;
	t_size size;
	t_rectangle rectangle;
	char *matrice;

	if (!get_size(file_ptr, &size, &matrice))
	{
		while ((ret = fscanf(file_ptr, "%c %f %f %f %f %c\n", &rectangle.type, &rectangle.x, &rectangle.y, &rectangle.width, &rectangle.height, &rectangle.rec_char)) == 6)
			register_in_matrice(&size, &rectangle, &matrice);
		if (ret == -1)
		{
			print_matrice(&size, matrice);
			return (0);
		}
		else
			return (1);
	}
	else
		return (1);
}

int	main(int ac, char **av)
{
	FILE 		*file_ptr;
	int 		ret;

	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	file_ptr = fopen(av[1], "r");
	if (!file_ptr)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if (execute_paint(file_ptr))
		return (1);
	fclose(file_ptr);
	return (0);
}

