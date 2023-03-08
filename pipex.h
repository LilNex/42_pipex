/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:19:59 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/08 01:53:02 by ichaiq           ###   ########.fr       */
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
	char 			*infile;
	char 			*input_data;
	char 			*outfile;
	// char 			**paths;
	char 			**cmds;
}					t_piputils;
// t_list *push(t_list **list,int val);
void parsePath(char **env, t_piputils *utils);
void parse_args(t_piputils *utils, int ac, char **av);
char *read_file(char *path);
char *get_fullpath(t_piputils *u, char *command);

#endif