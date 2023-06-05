/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:29:11 by ichaiq            #+#    #+#             */
/*   Updated: 2023/05/25 19:40:58 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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

void	ft_cleanexit(t_piputils *u)
{
	t_list		*tmp;
	t_command	*cmd;
	void		*t;

	tmp = u->commands;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		ft_free(cmd->fullpath);
		t = cmd->args;
		while (*cmd->args)
			ft_free(*cmd->args++);
		ft_free(cmd);
		ft_free(t);
		ft_free(tmp);
		tmp = tmp->next;
	}
	ft_lstclear(&u->paths, free);
	ft_free(u);
}

void f(){
	system("leaks pipex");
}

int	main(int ac, char **av, char **envp)
{
	t_piputils	*utils;
	atexit(f);
	if (ac >= 5)
	{
		utils = (t_piputils *) ft_calloc(1, sizeof(t_piputils));
		utils->envp = envp;
		parse_path(envp, utils);
		parse_args(utils, ac, av);
		if (utils->commands)
			execute_commands(utils);
		ft_cleanexit(utils);
		ft_error("fin");

	}
	else
		ft_error("Pipex needs some minimals args");
	return (0);
}
