/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:19:59 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/19 18:32:10 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include<stddef.h>
# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<limits.h>
# include "libft/libft.h"
# include "gnl/get_next_line_bonus.h"
# include <fcntl.h>

typedef struct s_piputils
{
	t_list			*paths;
	t_list			*commands;
	char			*infile;
	char			*input_data;
	char			*outfile;
	int				infilefd;
	int				outfilefd;
	char			**cmds;
	char			**envp;
}					t_piputils;

typedef struct s_command
{
	char	*cmd;
	char	*fullpath;
	char	**args;
}					t_command;
// t_list *push(t_list **list,int val);
int		ft_error(char *s);
void	parsePath(char **env, t_piputils *utils);
void	parse_args(t_piputils *utils, int ac, char **av);
char	*read_file(char *path);
char	*get_fullpath(t_piputils *u, char *command);
void	execute_commands(t_piputils *u);

#endif