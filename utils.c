/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:07 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/09 00:56:00 by ichaiq           ###   ########.fr       */
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
            ft_strlcpy(tmp = ft_calloc(ft_strlen(*env + 5),sizeof(char)),
                (*env)+ 5, ft_strlen(*env+5));
            // printf("tmp : %s\n",tmp);
            paths = ft_split(tmp,':');
            while (*paths)
               pushPath(*paths++,utils);
            // return ;
        }
        env++;
    }
    
}

void execute_commands(t_piputils *u)
{
    int count;
    t_list *node;
    t_command *cmd;
    int pid;

    count = 0;
    node = u->commands;
    while (node && node->content)
    {
        printf("count : %d\n",count++);
        cmd = (t_command *)node->content;
        pid = fork();
        if (pid == 0)
        {
            execve(cmd->fullpath, cmd->args, u->envp);
        }
        else
            waitpid(pid, NULL, 0);
        unlink()
        node = node->next;
        printf("node : %p\n", node);
    }

    
}