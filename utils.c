/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:07 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/14 00:09:08 by ichaiq           ###   ########.fr       */
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
            ft_strlcpy(tmp = ft_calloc(ft_strlen(*env + 5), sizeof(char)),
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
    char *content = NULL;
    int inputfd;
    count = 0;
    content = ft_calloc(10000, sizeof(char));
    node = u->commands;
    int newfd[2];
    if (pipe(newfd))
        printf("pipe error\n");
    inputfd = open(u->infile, O_RDWR);
    // dup2(newfd[1], inputfd);
    // int fd = dup(inputfd);
    int first = 1;

    while (node && node->content)
    {
        printf("count : %d first : %d\n", count++, first);
        cmd = (t_command *)node->content;

        if (pipe(newfd))
            printf("pipe error\n");
        
        pid = fork();
        if (pid == 0)
        {
            if (first)
            {
                dup2(inputfd, STDIN_FILENO);
                // close(newfd[0]);
                // close(newfd[1]);
            }
            else
            {
                dup2(inputfd, STDIN_FILENO);
                // close(newfd[0]);
                // close(newfd[1]);
            }
            dup2(newfd[1] , STDOUT_FILENO);
            execve(cmd->fullpath, cmd->args, u->envp);
        }
        else
        {

            if(first)
            {
                first = 0;
                close(inputfd);
            }
            close(newfd[1]);
            inputfd = newfd[0];
            waitpid(pid, NULL, 0);

        }
        printf("node : %p\n", node);
        node = node->next;
    }
    content = ft_calloc(10000, sizeof(char));
    read(newfd[0], content, 10000);
    printf("content : %s\n", content);
    
}