/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:54:56 by gpetit            #+#    #+#             */
/*   Updated: 2021/06/04 15:01:09 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct	s_screen
{
	int	width;
	int	height;
	char back_char;
}	t_screen;

typedef struct	s_circle
{
	char	type;
	float	x;
	float	y;
	float	rad;
	char	back_char;
}	t_circle;

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

int	first_line(FILE *file, t_screen *screen, char **matrice)
{
	int ret;

	ret = fscanf(file, "%d %d %c\n", &screen->width, &screen->height, &screen->back_char);
	if (ret != 3 || (screen->width <= 0 || screen->width > 300 || screen->height <= 0 || screen->width > 300))
		return (1);
	else 
	{
		*matrice = (char *)malloc(sizeof(char) * (screen->width * screen->height + 1));
		if (!(*matrice))
			return (1);
		(*matrice)[screen->width * screen->height] = 0;
		memset(*matrice, screen->back_char, screen->width * screen->height);
		return (0);
	}
}

void	print_matrice(t_screen *screen, char *matrice)
{
	int x;
	int y = 0;

	while (y < screen->height)
	{
		x = 0;
		while (x < screen->width)
		{	
			ft_putchar(matrice[x + y * screen->width]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

int		is_in_circle(t_screen *screen, t_circle *circle, char **matrice, float x, float y)
{
	if (circle->type == 'C' && sqrt(powf((x - circle->x), 2) + powf((y - circle->y), 2)) <= circle->rad)
		return (1);
	else if (circle->type == 'c' && sqrt(powf((x - circle->x), 2) + powf((y - circle->y), 2)) - circle->rad >= 0.00000 && sqrt(powf((x - circle->x), 2) + powf((y - circle->y), 2)) - circle->rad < 1.00000)
		return (1);
	return (0);
}

void	circle_or_not(t_screen *screen, t_circle *circle, char **matrice, int x, int y)
{
	if (is_in_circle(screen, circle, matrice, (float)x, (float)y))
		(*matrice)[x + y * screen->width] = circle->back_char;
	return ;
}

int	edit_matrice(t_screen *screen, t_circle *circle, char **matrice)
{
	int x;
	int y = 0;

	if ((circle->type != 'c' && circle->type != 'C') || (circle->rad <= 0))
		return (1);
	while (y < screen->height)
	{
		x = 0;
		while (x < screen->width)
			circle_or_not(screen, circle, matrice, x++, y);
		y++;
	}
	return (0);
}

int	execute_file(FILE *file)
{
	t_screen 	screen;
	t_circle 	circle;
	char 		*matrice;
	int			ret;

	if (!first_line(file, &screen, &matrice))
	{
		while ((ret = fscanf(file, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.rad, &circle.back_char)) == 5)
		{
			if (edit_matrice(&screen, &circle, &matrice))
			{	
				free(matrice);
				return (1);
			}
		}
		if (ret == -1)
		{
			print_matrice(&screen, matrice);
			free(matrice);
			return (0);
		}
		else
		{
			free(matrice);
			return (1);
		}
	}
	else
		return (1);
}

int	main(int ac, char **av)
{
	FILE 	*file;
	int 	ret;

	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	file = fopen(av[1], "r");
	if (!file)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	ret = execute_file(file);
	fclose(file);
	if (ret)
		return (1);
	else
		return (0);
}
