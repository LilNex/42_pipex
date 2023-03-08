/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:15 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/08 01:54:31 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *read_file(char *path)
{
    int fd;
    char *buffer;
    char *content;
    char *tmp;
    
    content = ft_strdup("");
    fd = open (path, O_RDONLY);
    buffer = get_next_line(fd);
    while (buffer)
    {
        tmp = ft_strjoin(content,buffer);
        if(content)
            free(content);
        if(buffer)
            free(buffer);
        content = tmp;
        buffer = get_next_line(fd);
    }
    return (content);
}

char *get_fullpath(t_piputils *u, char *command)
{
    // int mode = 0;
    t_list *paths;
    char *tmp;
    char *fullpath;

    paths = u->paths;
    tmp = ft_strjoin(paths->content, "/");
    fullpath = ft_strjoin(tmp, command);
    free(tmp);
    while ((access(fullpath,X_OK) != 0) || 
        ((access(fullpath,X_OK) != 0) && paths->next))
    {
        paths = paths->next;
        tmp = ft_strjoin(paths->content, "/");
        fullpath = ft_strjoin(tmp, command);
        free(tmp);
    }
    return fullpath;
}