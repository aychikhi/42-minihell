/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:46:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/27 19:52:15 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokenize_state	tokenize_state_init(int *i, t_token **tokens,
		t_token **last)
{
	t_tokenize_state	state;

	state.i = i;
	state.tokens = tokens;
	state.last = last;
	return (state);
}

t_env	*env_init(char **env)
{
	t_env	*new_env;
	t_env	*last;
	t_env	*new_node;
	int		i;

	new_env = NULL;
	last = NULL;
	if (!env || !*env)
		return (NULL);
	new_env = ft_lstnew(extract_var(env[0]), extract_value(env[0]));
	if (!new_env)
		return (NULL);
	last = new_env;
	i = 1;
	while (env[i])
	{
		new_node = ft_lstnew(extract_var(env[i]), extract_value(env[i]));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&last, new_node);
		last = last->next;
		i++;
	}
	return (new_env);
}

static int	arg_size(t_token *tokens)
{
	t_token	*tmp;
	int		size;

	size = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 9)
			break ;
		else if (tmp->type == 3 || tmp->type == 4 || tmp->type == 5
			|| tmp->type == 6)
			tmp = tmp->next->next->next;
		else if (tmp->type == 2)
			tmp = tmp->next;
		else
		{
			size++;
			tmp = tmp->next;
		}
	}
	return (size);
}

// void	init_cmd(t_cmd **cmd, t_token *tokens)
// {
// 	t_cmd	*tmp;
// 	t_cmd	*new;
// 	int		i = 0;

// 	*cmd = malloc (sizeof(t_cmd));
// 	(*cmd)->args = malloc ((arg_size(tokens) + 1) * sizeof(char *));
// 	for (int i = 0; i < arg_size(tokens); i++)
// 		(*cmd)->args[i] = NULL;
// 	(*cmd)->next = NULL;
// 	(*cmd)->file = malloc (sizeof(t_file));
// 	(*cmd)->file->name = NULL;
// 	(*cmd)->file->type = 0;
// 	(*cmd)->file->next = NULL;
// 	tmp = *cmd;
// 	while (tokens && tokens->type != 9)
// 	{
// 		if (tokens->type == 2)
// 			tokens = tokens->next;
// 		else
// 		{
// 			if (tokens->type == 1)
// 			{
// 				i = 0;
// 				new = malloc (sizeof(t_cmd));
// 				new->args = malloc ((arg_size(tokens) + 1) * sizeof(char *));
// 				for (int i = 0; i < arg_size(tokens); i++)
// 					new->args[i] = NULL;
// 				new->next = NULL;
// 				new->file = malloc (sizeof(t_file));
// 				new->file->name = NULL;
// 				new->file->type = 0;
// 				new->file->next = NULL;
// 				tmp->next = new;
// 			}
// 			tmp->cmd = tokens->value;
// 			while (tokens->type != 1 && tokens->type != 3 && tokens->type != 4
// 				&& tokens->type != 5 && tokens->type != 6 && tokens->type != 9)
// 			{
// 				if (tokens->type == 2)
// 					tokens = tokens->next;
// 				tmp->args[i] = ft_strdup(tokens->value);
// 				i++;
// 				tokens = tokens->next;
// 			}
// 			if (tokens->type == 3 || tokens->type == 4 || tokens->type == 5
// 				|| tokens->type == 6)
// 			{
// 				tmp->file->type = tokens->type;
// 				tmp->file->name = ft_strdup(tokens->next->value);
// 				tmp->file = tmp->file->next;
// 			}
// 		}
// 		tokens = tokens->next;
// 	}
// }

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
			if (tokens->next && tokens->next->type != 9)
			{
				tmp->file->name = ft_strdup(tokens->next->value);
				new_file = malloc(sizeof(t_file));
				new_file->name = NULL;
				new_file->type = 0;
				new_file->next = NULL;
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

void	init_command(t_command **cmd, t_token *tokens, t_env **env)
{
	if (!*cmd)
	{
		*cmd = malloc(sizeof(t_command));
		if (!*cmd)
			malloc_error();
	}
	(*cmd)->env = *env;
	init_cmd(&(*cmd)->cmd, tokens);
	(*cmd)->exit_status = 0;
}
