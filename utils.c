/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:07 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/26 23:36:40 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
	exit(0);
}

void	push_path(char *path, t_piputils *utils)
{
	ft_lstadd_front(&(utils->paths), ft_lstnew(path));
}

void	do_wait(int *first, int *newfd, int *inputfd, int pid)
{
	if (*first)
	{
		*first = 0;
		close(*inputfd);
	}
	close(newfd[1]);
	*inputfd = newfd[0];
	waitpid(pid, NULL, 0);
}

void	exec_cmd(int *inputfd, t_list *node, int *first, t_piputils *u)
{
	int			pid;
	int			newfd[2];

	if (pipe(newfd))
		ft_error("pipe error\n");
	pid = fork();
	if (pid == 0)
	{
		dup2(*inputfd, STDIN_FILENO);
		if (node->next)
			dup2(newfd[1], STDOUT_FILENO);
		else
			dup2(u->outfilefd, STDOUT_FILENO);
		execve(((t_command *)node->content)->fullpath,
			((t_command *)node->content)->args, u->envp);
	}
	else
		do_wait(first, newfd, inputfd, pid);
}

void	execute_commands(t_piputils *u)
{
	t_list		*node;
	int			inputfd;
	int			first;

	first = 1;
	node = u->commands;
	inputfd = u->infilefd;
	while (node && node->content)
	{
		exec_cmd(&inputfd, node, &first, u);
		node = node->next;
	}
}
