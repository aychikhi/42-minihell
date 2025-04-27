/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:34:34 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/27 20:35:03 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmd(t_cmd **cmd, t_token *tokens)
{
	t_cmd	*tmp;
	t_cmd	*new;
	t_file	*new_file;
	int		i;

	i = 0;
	*cmd = malloc(sizeof(t_cmd));
	(*cmd)->args = malloc((arg_size(tokens) + 1) * sizeof(char *));
	for (int j = 0; j <= arg_size(tokens); j++)
		(*cmd)->args[j] = NULL;
	(*cmd)->next = NULL;
	(*cmd)->file = malloc(sizeof(t_file));
	(*cmd)->file->name = NULL;
	(*cmd)->file->type = 0;
	(*cmd)->file->next = NULL;
	(*cmd)->cmd = NULL;
	tmp = *cmd;
	while (tokens && tokens->type != 9)
	{
		if (tokens->type == 2)
			tokens = tokens->next;
		else if (tokens->type == 1)
		{
			i = 0;
			new = malloc(sizeof(t_cmd));
			new->args = malloc((arg_size(tokens->next) + 1) * sizeof(char *));
			for (int j = 0; j <= arg_size(tokens->next); j++)
				new->args[j] = NULL;
			new->next = NULL;
			new->cmd = NULL;
			new->file = malloc(sizeof(t_file));
			new->file->name = NULL;
			new->file->type = 0;
			new->file->next = NULL;
			tmp->next = new;
			tmp = new;
			tokens = tokens->next;
		}
		else if (tokens->type == 3 || tokens->type == 4 || tokens->type == 5
			|| tokens->type == 6)
		{
			tmp->file->type = tokens->type;
			while (tokens->next->type == 2)
				tokens = tokens->next;
			if (tokens->next && tokens->next->type != 9)
			{
				new_file = malloc(sizeof(t_file));
				new_file->name = ft_strdup(tokens->next->value);
				new_file->next = NULL;
				new_file->type = tmp->file->type;
				tmp->file->next = new_file;
				tmp->file = tmp->file->next;
				tokens = tokens->next->next;
			}
			else
				tokens = tokens->next;
		}
		else
		{
			if (!tmp->cmd)
				tmp->cmd = ft_strdup(tokens->value);
			tmp->args[i] = ft_strdup(tokens->value);
			i++;
			tokens = tokens->next;
		}
	}
}
