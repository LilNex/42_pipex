/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:29:11 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/27 02:03:44 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	ft_cleanexit(t_piputils *u)
{
	t_list		*tmp;
	t_command	*cmd;
	void		*t;

	tmp = u->commands;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		free(cmd->cmd);
		free(cmd->fullpath);
		t = cmd->args;
		while (*cmd->args)
			free(*cmd->args++);
		free(cmd);
		free(t);
		free(tmp);
		tmp = tmp->next;
	}
	ft_lstclear(&u->paths, free);
	free(u);
}

int	main(int ac, char **av, char **envp)
{
	t_piputils	*utils;
	int			count;

	if (ac >= 5)
	{
		utils = (t_piputils *) ft_calloc(1, sizeof(t_piputils));
		utils->envp = envp;
		count = 0;
		parse_path(envp, utils);
		parse_args(utils, ac, av);
		if (utils->commands)
			execute_commands(utils);
		ft_cleanexit(utils);
	}
	else
		ft_error("Pipex needs some minimals args");
	return (0);
}
