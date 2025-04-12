/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:09:50 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/12 17:24:56 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	(void)av;
	(void)ac;
	int		i;
	int		k;
	int		j;
	char	*cmd;
	char	*line;
	t_cmd	*lst;

	lst = NULL;
	i = 0;
	j = 0;
	while (1337)
	{
		line = readline("minishell: ");
		if (!line)
			break;
		while (line[i])
		{
			j = ft_isspecial(line, i);
			cmd = malloc(j + 1);
			k = 0;
			while (k < j)
			{
				cmd[k] = line[i + k];
				k++;
			}
			cmd[k] = '\0';
			if (!lst)
				lst = ft_lstnew(cmd);
			else
				ft_lstadd_back(&lst, ft_lstnew(cmd));
			i += j;
			if (line[i] == '|')
				i++;
		}
		free(line);
		t_cmd *tmp = lst;
		while (tmp)
		{
			printf("---->%s<----\n", (char *)tmp->cmd);
			tmp = tmp->next;
		}
		// cleanup(lst, NULL);
		lst = NULL;
	}
	return (0);
}
