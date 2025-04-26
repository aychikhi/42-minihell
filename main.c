/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/26 18:45:38 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_fun(void)
{
	printf("Error: Unclosed quotes!\n");
	return (0);
}

void	malloc_error(void)
{
	printf("malloc Error !\n");
	exit(EXIT_FAILURE);
}

void	one_space(char **line)
{
	int	i;
	int	f;
	int	flag;

	i = 0;
	f = 0;
	flag = 0;
	while (line[0][f])
	{
		while (line[0][f] == ' ')
		{
			flag = 1;
			f++;
		}
		if (flag)
		{
			line[0][i] = ' ';
			flag = 0;
			i++;
		}
		line[0][i] = line[0][f];
		f++;
		i++;
	}
	line[0][i] = '\0';
}

int	main(int ac, char **av, char **env)
{
	int		flag;
	char	*line;
	t_env	*new_env;
	t_cmd	cmd;

	(void)av;
	(void)ac;
	new_env = env_init(env);
	while (07)
	{
		line = readline("minishell :");
		if (!line)
			return (2);
		flag = check_quotes(line);
		if (flag)
			tokeniser(line, new_env, &cmd);
		free(line);
	}
	return (0);
}
