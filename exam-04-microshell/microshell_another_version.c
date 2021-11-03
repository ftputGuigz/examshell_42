/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:37:45 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/10 12:41:09 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "microshell.h"

void	ft_putstr(char *str, int fd)
{
	int i;

	for (i = 0; str[i]; i++)
		write(1, &str[i], fd);
}

int ft_strlen(char *str)
{
	int i;

	for (i = 0; str[i]; i++);
	return (i);
}

int ft_strlen_double(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++);
	return (i);
}

char *ft_strdup(char *str)
{
	char *cpy;
	int i;

	cpy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cpy)
		return (NULL);
	cpy[ft_strlen(str)] = '\0';
	for (i = 0; str[i]; i++)
		cpy[i] = str[i];
	return (cpy);
}

char **double_strdup(char **av, int size)
{
	char **cpy;
	int i;

	cpy = malloc(sizeof(char *) * (size + 1));
	if (!cpy)
		return (NULL);
	cpy[size] = 0;
	for (i = 0; i < size; i++)
		cpy[i] = ft_strdup(av[i]);
	return (cpy);
}

void	free_double(char **av)
{
	int i;

	for (i = 0; av[i]; i++)
		free(av[i]);
}

void	free_tab(t_command *cmd, int cmd_nb)
{
	int i;

	for (i = 0; i < cmd_nb; i++)
		free_double(cmd[i].arg);
	free(cmd);
}

t_command *create_tab(char **av, int *cmd_nb)
{
	t_command *cmd;
	int size = 1;
	int i;
	int pos;
	int nb = 0;

	for (i = 0; av[i]; i++)
		if (av[i] && !strcmp(av[i], "|"))
			size++;
	*cmd_nb = size;
	cmd = malloc(sizeof(t_command) * size);
	if (!cmd)
		return (NULL);
	i = 0;
	while (av[i])
	{
		pos = i;
		while (av[pos] && strcmp(av[pos], "|"))
			pos++;
		cmd[nb].bin = av[i];
		cmd[nb++].arg = double_strdup(av + i, pos - i);
		i = pos;
		if (av[i] && !strcmp(av[i], "|"))
			i++;
	}
	return (cmd);
}

int	bin_cd(char **arg)
{
	int	size;

	size = ft_strlen_double(arg);
	if (size != 2)
		return (ERROR);
	if (chdir(arg[1]))
		return (ERROR);
	return (SUCCESS);
}

int	pipex(t_command *cmd, int cmd_nb, char **env)
{
	int i = 0;
	pid_t pid;
	int	fd[2];
	int ret = SUCCESS;

	while (i + 1 < cmd_nb)
	{
		if (pipe(fd) == -1)
			return (ERROR);
		close(fd[0]);
		if ((pid = fork()) == -1)
			return (ERROR);
		if (pid == 0)
		{
			dup2(fd[1], STDOUT);
			close(fd[0]);
			close(fd[1]);
			if (cmd[i].bin && !strcmp(cmd[i].bin, "cd"))
				ret = bin_cd(cmd[i].arg);
			else
				ret = execve(cmd[i].bin, cmd[i].arg, env);
			exit (ret);
		}
		waitpid(pid, 0, 0);
		dup2(fd[0], STDIN);
		close(fd[1]);
		i++;
	}
	if (!strcmp(cmd[i].bin, "cd"))
		ret = bin_cd(cmd[i].arg);
	else
	{
		if ((pid = fork()) == -1)
			return (ERROR);
		if (pid == 0)
		{
			ret = execve(cmd[i].bin, cmd[i].arg, env);
			exit (ret);
		}
		waitpid(pid, 0, 0);
	}
	return (ret);
}

int treat_pipes(char **av, char **env)
{
	t_command *cmd;
	int	cmd_nb;

	cmd = create_tab(av, &cmd_nb);
	if (!cmd)
		return (ERROR);
	pipex(cmd, cmd_nb, env);
	free_tab(cmd, cmd_nb);
	return (SUCCESS);
}

void	minishell(char **av, char **env)
{
	int i;
	int pos;
	char **arg;

	i = 0;
	while (av[i])
	{
		pos = i;
		while (av[pos] && strcmp(av[pos], ";"))
			pos++;
		if (pos != i)
		{
			arg = double_strdup(av + i, pos - i);
			treat_pipes(arg, env);
			free_double(arg);
			i = pos;
		}
		if (av[i] && !strcmp(av[pos], ";"))
			i++;
	}
}

int main(int ac, char **av, char **env)
{
	if (ac == 1)
		return (0);
	else
		minishell(av + 1, env);
	return (0);
}
