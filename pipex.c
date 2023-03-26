/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:29:11 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/26 16:58:46 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void ft_cleanexit(t_piputils *u)
{
	t_list		*tmp;
	t_command	*cmd;

	tmp = u->commands;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		free(cmd->fullpath);
		while (*cmd->args)
		{
			printf("arg : %s\n",*cmd->args);
			free(*cmd->args++);
		}
		free(cmd->cmd);
		tmp = tmp->next;
	}
	ft_lstiter(u->paths, free);
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
		while (1)
			;
		

	}

	return (0);
}
