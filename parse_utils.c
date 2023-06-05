/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:30:06 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/30 22:19:00 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_fullpath(t_piputils *u, char *command)
{
	t_list	*paths;
	char	*tmp;
	char	*fullpath;

	paths = u->paths;
	tmp = ft_strjoin(paths->content, "/");
	fullpath = ft_strjoin(tmp, command);
	ft_free(tmp);
	while ((access(fullpath, X_OK) < 0) && paths->next)
	{
		ft_free(fullpath);
		paths = paths->next;
		tmp = ft_strjoin(paths->content, "/");
		fullpath = ft_strjoin(tmp, command);
		ft_free(tmp);
	}
	ft_free(command);
	if ((access(fullpath, X_OK) >= 0))
		return (fullpath);
	else
		return (ft_error("A command was not found in env path"), NULL);
}

void	get_path(t_piputils *u, char *av, t_command *cmd)
{
	if ((*av == '.' || *av == '/' ))
	{
		cmd->fullpath = first_word(av);
		if (access(cmd->fullpath, X_OK) < 0)
			ft_error("The command was not found in path");
	}
	else
	{
		if (u->paths)
			cmd->fullpath = get_fullpath(u, first_word(av));
	}
}

void	parse_commands(t_piputils *u, int ac, char **av)
{
	int			i;
	t_command	*cmd;

	i = 2;
	(void)u;
	while (i < ac -1)
	{
		if (!*av[i])
			ft_error("A command is invalid");
		cmd = ft_calloc(1, sizeof(t_command));
		get_path(u, av[i], cmd);
		cmd->args = ft_split(av[i], ' ');
		ft_lstadd_back(&u->commands, ft_lstnew(cmd));
		i++;
	}
}

void	parse_args(t_piputils *utils, int ac, char **av)
{
	if (ac >= 5)
	{
		utils->infile = av[1];
		utils->outfile = av[ac - 1];
		utils->infilefd = open(utils->infile, O_RDWR);
		if (utils->infilefd < 0)
			ft_error("Input file is invalid");
		utils->outfilefd = open(utils->outfile,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (utils->outfilefd < 0)
			ft_error("Output file is invalid");
		parse_commands(utils, ac, av);
	}
}

void	parse_path(char **env, t_piputils *utils)
{
	char	*tmp;
	char	**paths;
	char	**p_tmp;
	int		flag;

	paths = NULL;
	flag = 0;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
		{
			flag = 1;
			ft_strlcpy(tmp = ft_calloc(ft_strlen(*env + 5), sizeof(char)),
				(*env) + 5, ft_strlen(*env + 5));
			paths = ft_split(tmp, ':');
			p_tmp = paths;
			while (*paths)
				ft_lstadd_front(&(utils->paths), ft_lstnew(*paths++));
			ft_free(tmp);
			ft_free(p_tmp);
		}
		env++;
	}
	if (!flag)
		ft_error("Env path is invalid");
}
