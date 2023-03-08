/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:07 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/08 01:53:15 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "pipex.h"


void pushPath(char *path, t_piputils *utils){
    // utils->paths;
    ft_lstadd_front(&(utils->paths),ft_lstnew(path));
}

void parsePath(char **env, t_piputils *utils)
{
    char *tmp;
    char **paths = NULL;
    while (*env)
    {
        if(!ft_strncmp(*env,"PATH=",5))
        {
            // printf("%s\n",*env+ 5);
            ft_strlcpy(tmp = ft_calloc(ft_strlen(*env+5),sizeof(char)), (*env)+ 5, ft_strlen(*env+5));
            // printf("tmp : %s\n",tmp);
            paths = ft_split(tmp,':');
            while (*paths)
               pushPath(*paths++,utils);
            // return ;
        }
        env++;
    }
    
}

void parse_args(t_piputils *utils, int ac, char **av)
{
    // int c = 0;
    char *infile;
    char *outfile;
    utils->cmds = ft_calloc(ac - 3, sizeof(char));
    if (ac >= 5 )
    {
        infile = av[1];
        // utils->infile = rea
        outfile = av[ac - 1];
        utils->input_data = read_file(infile);

        printf("infile : %s\n", utils->input_data);
        printf("outfile : %s\n", get_fullpath(utils, "ls"));
    }
    
}


