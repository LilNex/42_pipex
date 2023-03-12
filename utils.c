/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:55:07 by ichaiq            #+#    #+#             */
/*   Updated: 2023/03/12 18:17:33 by ichaiq           ###   ########.fr       */
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
        printf("count : %d\n", count++);
        cmd = (t_command *)node->content;

        // int fd = -1;
        // if(pipe(newfd) == -1)
        //     printf("pipe error\n");
        // dup2(newfd[1], STDOUT_FILENO);
        // write(newfd[1], "hello\n\n", 7);
        // fd = dup(STDOUT_FILENO);
        
        pid = fork();
        if (pid == 0)
        {
            if (first)
            {
            //     // close(STDIN_FILENO);
                dup2(inputfd, STDIN_FILENO);
            }
            else
                // dup2(newfd[1], newfd[0]);
                dup2(newfd[0], newfd[1]);

            dup2(newfd[1], STDOUT_FILENO);
            // dup2(newfd[0], STDIN_FILENO);
            execve(cmd->fullpath, cmd->args, u->envp);
            
            // dup2(STDI)
        }
        else
        {

            if(first)
            {
                first = 0;
                // close(STDIN_FILENO);
                close(inputfd);
            }
            waitpid(pid, NULL, 0);
            // close(newfd[1]);
            content = ft_calloc(10000, sizeof(char));
            // read(newfd[0], content, 10000);
            // printf("content : %s\n", content);
        }
        
        // dup2(newfd[1], STDOUT_FILENO);
        
        
        printf("node : %p\n", node);
        node = node->next;
    }

    
}