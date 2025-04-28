/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:28:24 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/28 11:28:46 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*add_new(int size)
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		malloc_error();
	tmp->args = calloc(size + 1, sizeof(char *));
	if (!tmp->args)
		malloc_error();
	tmp->next = NULL;
	tmp->cmd = NULL;
	tmp->file = malloc(sizeof(t_file));
	if (!tmp->file)
		malloc_error();
	tmp->file->name = NULL;
	tmp->file->type = 0;
	tmp->file->next = NULL;
	return (tmp);
}
