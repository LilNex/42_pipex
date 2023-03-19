/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:07 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/19 19:02:52 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "pipex.h"

int ft_exit(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(0);
}

void	pushPath(char *path, t_piputils *utils)
{
	ft_lstadd_front(&(utils->paths), ft_lstnew(path));
}

void	parsePath(char **env, t_piputils *utils)
{
	char *tmp;
	char **paths = NULL;
	while (*env)
	{
		if(!ft_strncmp(*env,"PATH=",5))
		{
			ft_strlcpy(tmp = ft_calloc(ft_strlen(*env + 5), sizeof(char)),
				(*env)+ 5, ft_strlen(*env+5));
			paths = ft_split(tmp,':');
			while (*paths)
			   pushPath(*paths++,utils);
			}
		env++;
	}
	
}

void exec_cmd(int inputfd, t_list *node, int *first,t_piputils *u, int *newfd)
{
	int			pid;
	t_command	*cmd;

	cmd = (t_command *)node->content;
	if (pipe(*newfd))
		ft_error("pipe error\n");

	pid = fork();
	if (pid == 0)
	{
		if (*first)
			dup2(inputfd, STDIN_FILENO);
		else
			dup2(inputfd, STDIN_FILENO);
		if (node->next)
			dup2(newfd[1], STDOUT_FILENO);
		else
			dup2(u->outfilefd, STDOUT_FILENO);
		execve(cmd->fullpath, cmd->args, u->envp);
	}
	else
	{

		if (first)
		{
			first = 0;
			close(inputfd);
		}
		close(newfd[1]);
		inputfd = newfd[0];
		waitpid(pid, NULL, 0);

	}
	node = node->next;
}

void	execute_commands(t_piputils *u)
{
	t_list		*node;
	int			inputfd;
	int			newfd[2];
	int			first;

	first = 1;
	node = u->commands;
	if (pipe(newfd))
		printf("pipe error\n");

	inputfd = u->infilefd;

	while (node && node->content)
	{
		exec_cmd(&inputfd, node, &first, u, newfd);
	}
}
