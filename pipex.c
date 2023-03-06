
#include "libft/libft.h"
#include "pipex.h"


int ft_exit(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
	exit(0);
}


void pPath(void *c)
{
	char *s;

	s = (char *)c;
	printf("%s\n",s);
}



int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_piputils *utils;
	// char **args;
	int count;
	// t_list *list;
	utils = (t_piputils *) ft_calloc(1,sizeof(t_piputils));
	count = 0;
	// if (ac >= 5 )
	// {

		
	// 	// printf("tt\n"); 
	// 	while (av[count]) 
	// 	{
	// 		args = ft_split(av[count], ' ');
			
	// 	}
		
	// }
	// while (*envp)
	// {
		parsePath(envp,utils);
		parse_args(utils, ac, av);

	// ft_lstiter(utils->paths,pPath);
	
	// 	printf("%s\n",*envp++);
	// }
	

	return 0;
}