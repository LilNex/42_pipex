/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:30:06 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/26 17:00:06 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*first_word(char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(word, str, i + 1);
	return (word);
}

char	*get_fullpath(t_piputils *u, char *command)
{
	t_list	*paths;
	char	*tmp;
	char	*fullpath;

	paths = u->paths;
	tmp = ft_strjoin(paths->content, "/");
	fullpath = ft_strjoin(tmp, command);
	free(tmp);
	while ((access(fullpath, X_OK) < 0) && paths->next)
	{
		free(fullpath);
		paths = paths->next;
		tmp = ft_strjoin(paths->content, "/");
		fullpath = ft_strjoin(tmp, command);
		free(tmp);
	}
	if ((access(fullpath, X_OK) >= 0))
		return (fullpath);
	else
		return (ft_error("A command was not found in env path"), NULL);
}

void	parse_commands(t_piputils *u, int ac, char **av)
{
	int			i;
	t_command	*cmd;

	i = 2;
	(void)u;
	while (i < ac -1)
	{
		cmd = ft_calloc(1, sizeof(t_command));
		cmd->cmd = first_word(av[i]);
		cmd->fullpath = get_fullpath(u, cmd->cmd);
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

	paths = NULL;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
		{
			ft_strlcpy(tmp = ft_calloc(ft_strlen(*env + 5), sizeof(char)),
				(*env) + 5, ft_strlen(*env + 5));
			paths = ft_split(tmp, ':');
			p_tmp = paths;
			while (*paths)
				ft_lstadd_front(&(utils->paths), ft_lstnew(*paths++));
			free(tmp);
			free(p_tmp);
		}
		env++;
	}
}
