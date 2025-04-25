/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:13:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/25 15:28:27 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF,
}					t_token_type;

typedef struct s_file
{
	char			*name;
	int				type;
	struct s_file	*next;
}					t_file;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_file			*file;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_command
{
	t_env			*env;
	t_cmd			*cmd;
	unsigned char	exit_status;
}					t_command;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_tokenize_state
{
	int				*i;
	t_token			**tokens;
	t_token			**last;
}					t_tokenize_state;

int					error_fun(void);
char				*ft_itoa(int n);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
void				malloc_error(void);
char				*add_word(char *str);
void				one_space(char **line);
char				*extract_var(char *var);
int					check_quotes(char *line);
void				check_unprint(char **line);
int					ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*extract_value(char *value);
void				free_tokens(t_token *tokens);
int					skip_fun(char *line, int flag);
char				*ft_strchr(const char *s, int c);
char				**ft_split(char const *s, char c);
t_env				*ft_lstnew(void *var, void *value);
t_token				*tokeniser(char *input, t_env *env);
char				*expand_env(char *input, t_env *env);
void				ft_lstadd_back(t_env **lst, t_env *new);
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
char				*add_word_inside_quote(char c, char *str);
void				handle_out_redirection(char *input, int *i,
						t_token **tokens, t_token **last);
void				add_token(t_token **tokens, t_token **last,
						t_token_type type, const char *value);
char				*ft_substr(char const *s, int start, int len);
void				handle_word(char *input, int *i, t_token **tokens,
						t_token **last);
// char				*extract_env(char *input, t_env *env, int len_var);
void				handle_quotes(char *input, int *i, t_token **tokens,
						t_token **last);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				handle_redirection(char *input, int *i, t_token **tokens,
						t_token **last);
void				handle_in_redirection(char *input, int *i, t_token **tokens,
						t_token **last);
char				*extract_env(char *input, t_env *env, int dollar_pos,
						char *var_name);
char				*ft_strncpy(char *dest, const char *src, int n);

#endif