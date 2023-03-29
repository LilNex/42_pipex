/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:49:07 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/28 23:02:42 by ichaiq           ###   ########.fr       */
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
	char			**envp;
	int				*newfd;
}					t_piputils;

typedef struct s_command
{
	char	*cmd;
	char	*fullpath;
	char	**args;
}					t_command;

void	ft_cleanexit(t_piputils *u);
int		ft_error(char *s);
char	*first_word(char *str);
void	get_path(t_piputils *u, char *av, t_command *cmd);
char	*get_fullpath(t_piputils *u, char *command);
void	parse_commands(t_piputils *u, int ac, char **av);
void	parse_args(t_piputils *utils, int ac, char **av);
void	parse_path(char **env, t_piputils *utils);
void	push_path(char *path, t_piputils *utils);
void	do_wait(int *first, int *newfd, int *inputfd, int pid);
void	exec_cmd(int *inputfd, t_list *node, int *first, t_piputils *u);
void	execute_commands(t_piputils *u);

#endif