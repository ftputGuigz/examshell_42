/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:58:04 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/10 14:37:03 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"
#include <stdio.h>

int		ft_strlen(char *str)
{
	int i;

	for(i = 0; str[i]; i++);
	return (i);
}

char	*ft_strdup(char *str)
{
	int i;
	char *cpy;

	cpy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cpy)
		return (NULL);
	for (i = 0; str[i]; i++)
		cpy[i] = str[i];
	cpy[i] = '\0';
	return (cpy);
}

char 	**dup_double(char **arr, int j)
{
	char **cpy;
	int i;

	cpy = malloc(sizeof(char *) * (j + 1));
	if (!cpy)
		return (NULL);
	cpy[j] = 0;
	for (i = 0; i < j; i++)
		cpy[i] = ft_strdup(arr[i]);
	return (cpy);
}

void	free_double(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

void	ft_putstr_fd(char *str, int fd)
{
	int i;

	for (i = 0; str[i]; i++)
		write(fd, &str[i], 1);
}

int ft_strlen_double(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++);
	return (i);
}

int	ft_error(int error, char *str)
{
	if (error == FATAL)
		ft_putstr_fd("error: fatal", STDERR);
	else if (error == EXECVE)
	{
		ft_putstr_fd("error: cannot execute ", STDERR);
		ft_putstr_fd(str, STDERR);
	}
	else if (error == CD_ARG)
		ft_putstr_fd("error: cd: bad arguments", STDERR);
	else if (error == CD_PATH)
	{
		ft_putstr_fd("error: cd: cannot change directory to ", STDERR);
		ft_putstr_fd(str, STDERR);
	}
	ft_putstr_fd("\n", 2);
	if (error == FATAL)
		return (ERROR);
	else
		return (SUCCESS);
}

int	bin_cd(t_command *cmd)
{
	if (ft_strlen_double(cmd->arg) != 2)
		ft_error(CD_ARG, NULL);
	if (chdir(cmd->arg[1]))
		ft_error(CD_PATH, cmd->arg[0]);
	return (SUCCESS);
}

t_command *tab_pipes(char **av, int *ret)
{
	int i;
	int size = 1;
	t_command *cmd;

	for (i = 0; av[i]; i++)
		if (!strcmp(av[i], "|"))
			size++;
	*ret = size;
	cmd = malloc(sizeof(t_command) * size);
	if (!cmd)
		return (NULL);
	i = 0;
	int j = 0;
	while (av[j])
	{
		int pos = j;
		while (av[pos] && strcmp(av[pos], "|"))
			pos++;
		cmd[i].bin = av[j];
		cmd[i++].arg = dup_double(av + j, pos - j);
		j = pos;
		if (av[j] && !strcmp(av[j], "|"))
			j++;
	}
	return (cmd);
}

void	free_tab(t_command *cmd, int tab_size)
{
	int i;

	for (i = 0; i < tab_size; i++)
		free_double(cmd[i].arg);
	free(cmd);
}

int	pipex(t_command *cmd, int tab_size, char **env)
{
	int i = 0;
	pid_t pid;
	int fd[2];
	int ret;

	while (i + 1 < tab_size)
	{
		if (pipe(fd) == -1)
			return (ft_error(FATAL, NULL));
		if ((pid = fork()) == -1)
			return (ft_error(FATAL, NULL));
		if (pid == 0)
		{
			dup2(fd[1], STDOUT);
			close(fd[0]);
			close(fd[1]);
			if (!strcmp(cmd[i].bin, "cd"))
				ret = bin_cd(cmd + i);
			else
				ret = execve(cmd[i].bin, cmd[i].arg, env);
			if (ret == ERROR)
				ft_error(EXECVE, cmd[i].bin);
			exit(SUCCESS);
		}
		waitpid(pid, 0, 0);
		dup2(fd[0], STDIN);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	if (!strcmp(cmd[i].bin, "cd"))
		ret = bin_cd(cmd + i);
	else
	{
		if ((pid = fork()) == -1)
			return (ft_error(FATAL, NULL));
		if (pid == 0)
		{
			ret = execve(cmd[i].bin, cmd[i].arg, env);
			if (ret == ERROR)
				ft_error(EXECVE, cmd[i].bin);
			exit (SUCCESS);
		}
		waitpid(pid, 0, 0);
		ret = SUCCESS;
	}
	return (ret);
}

int	treat_pipe(char **av, char **env)
{
	t_command *cmd;
	int		tab_size;

	cmd = tab_pipes(av, &tab_size);
	if (!cmd)
		return (ft_error(FATAL, NULL));
	pipex(cmd, tab_size, env);
	free_tab(cmd, tab_size);
	return (SUCCESS);
}

int	microshell(char **av, char **env)
{
	int i;
	int j;
	char **arg;

	i = 0;
	while (av[i])
	{	
		j = i;
		while (av[j] && strcmp(av[j], ";"))
			j++;
		if (j != i)
		{
			arg = dup_double(av + i, j - i);
			if (!arg)
				return (ft_error(FATAL, NULL));
			treat_pipe(arg, env);
			free_double(arg);
			i = j;
		}
		if (av[i])
			i++;
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
		return (0);
	else
	{
		if (microshell(av + 1, env))
			return (ERROR);
		else
			return (SUCCESS);
	}
}
