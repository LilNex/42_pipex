/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:30:06 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/19 19:04:14 by ichaiq           ###   ########.fr       */
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

void	parse_commands(t_piputils *u, int ac, char **av)
{
	int			i;
	t_command	*cmd;
	char		*tmp;

	i = 2;
	(void)u;
	while (i < ac -1)
	{
		cmd = ft_calloc(1, sizeof(t_command));
		cmd->cmd = first_word(av[i]);
		cmd->fullpath = get_fullpath(u, cmd->cmd);
		if (ft_strlen(av[i]) > ft_strlen(cmd->cmd))
			tmp = ft_strdup(av[i] + 1 + ft_strlen(cmd->cmd));
		else
			tmp = ft_strdup("");
		cmd->args = ft_split(av[i], ' ');

		ft_lstadd_back(&u->commands, ft_lstnew(cmd));
		i++;
	}

}


void	print_cmds(t_command *u)
{
	printf("------------------\n");
	printf("cmd : %s | path : %s\n",u->cmd,u->fullpath);
	for (size_t i = 0; i < ft_lstlen((const char **)u->args); i++)
	{
		printf("arg[%zu] : %s\n",i,u->args[i]);
	}
	printf("------------------\n");
}

void	parse_args(t_piputils *utils, int ac, char **av)
{
	utils->cmds = ft_calloc(ac - 3, sizeof(char));
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


