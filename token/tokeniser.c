/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:03:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/25 17:53:58 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_error(void)
{
	printf("malloc Error !\n");
	exit(EXIT_FAILURE);
}

char	*add_word(char *str)
{
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	while (str[l] && str[l] != '\'' && str[l] != '\"' && str[l] != ' '
		&& str[l] != '<' && str[l] != '>')
		l++;
	ptr = malloc(l + 1);
	if (!ptr)
		malloc_error();
	while (i < l)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*add_word_inside_quote(char c, char *str)
{
	int		l;
	int		i;
	char	*ptr;

	i = 0;
	l = 0;
	while (str[l] && str[l] != c)
		l++;
	ptr = malloc(l + 1);
	if (!ptr)
		malloc_error();
	while (i < l)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	handle_token(char c, char *input, t_tokenize_state *state)
{
	if (c == ' ')
		(*state->i)++;
	else if (c == '|')
	{
		add_token(state->tokens, state->last, TOKEN_PIPE, "|");
		(*state->i)++;
	}
	else if (c == '<' || c == '>')
		handle_redirection(input, state->i, state->tokens, state->last);
	else if (c == '\'' || c == '\"')
		handle_quotes(input, state->i, state->tokens, state->last);
	else
		handle_word(input, state->i, state->tokens, state->last);
}

static void	print_token(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

// t_token	*tokeniser(char *input, t_env *env)
void	tokeniser(char *input, t_env *env, t_cmd *cmd)
{
	int					i;
	t_token				*tokens;
	t_token				*last;
	t_tokenize_state	state;
	char				*new_input;

	(void)cmd;
	i = 0;
	new_input = expand_env(input, env);
	last = NULL;
	tokens = NULL;
	state = tokenize_state_init(&i, &tokens, &last);
	if (!new_input)
		return ;
	while (new_input[i])
		handle_token(new_input[i], new_input, &state);
	add_token(&tokens, &last, TOKEN_EOF, "EOF");
	// cmd = init_cmd(&cmd, tokens);
	print_token(tokens);
	free_tokens(tokens);
	// return (tokens);
}
