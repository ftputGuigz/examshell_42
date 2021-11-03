/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:44:51 by gpetit            #+#    #+#             */
/*   Updated: 2021/09/09 15:02:49 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>

# define ERROR -1
# define SUCCESS 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define FATAL -1
# define EXECVE -2
# define CD_ARG -3
# define CD_PATH -4

typedef struct	s_command
{
	char *bin;
	char **arg;
}	t_command;

#endif
