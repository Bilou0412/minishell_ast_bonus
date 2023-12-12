/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:57 by soutin            #+#    #+#             */
/*   Updated: 2023/12/12 20:56:50 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parser.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define LEFT 1
# define RIGHT 0

typedef struct s_files
{
	int				fd;
	struct s_files	*next;
}					t_files;

typedef struct s_cmd
{
	t_files			*infiles;
	t_files			*outfiles;
	char			**argv;
	char			*path;
	char			**env_paths;
	char			**envp;
	int				nb_pipes;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_vars
{
	t_str_data		str_in;
	t_tokens		*tokens;
	t_ast			*ast;
	t_cmd			cmd;
	int				last_return_val;
	t_env			*envl;
	bool			stop;
	bool			error;
	struct termios	original;

}					t_vars;

t_vars				*_vars(void);

/*PRINT functions*/
void				print_tree(t_ast *ast, int depth);
void				printtab(char **v);
void				printtokens(t_tokens **head);

/*FREE functions*/
void				freetabs(char **tab);
void				free_tree(t_ast **ast);
void				freevars(t_vars *vars, int i);
void				free_envl(t_env **lst);
void				free_files(t_files **lst);

/*ERRORS handler*/
int					syntax_error(t_tokens **head);
int					print_syntax_error(char *string);

/*ENV handler*/
int					setup_env(t_env **envl, char **envp);
t_env				*search_envl(t_env **envl, char *key);
t_env				*ft_env_new(char *key, char *value);
t_env				*ft_env_last(t_env **tok);
void				ft_env_add_back(t_env **tok, t_env *new);
int					ft_env_size(t_env **envl);
char				**env_to_tab(t_env **envl);
void				ft_env_add_back(t_env **tok, t_env *new);
t_env				*ft_env_new(char *key, char *value);

/*TOKENS handler*/
t_tokens			*ft_toknew(char *content, int type, t_expand *lst_expand);
t_expand			*ft_explast(t_expand **lst_expand);
void				ft_tokadd_front(t_tokens **lst, t_tokens *new);
int					ft_toksize(t_tokens *lst);
t_tokens			*ft_toklast(t_tokens **tok);
void				ft_tokadd_back(t_tokens **lst, t_tokens *new);
void				ft_tokclear(t_tokens **lst);
void				delete_file_tokens(t_tokens **head, t_tokens **curr);

int					file_add_back(t_files **head, int new_fd);

/*TOKENS build*/
void				token_m(t_vars *vars, t_tokens **tok);
int					make_word(t_str_data *str_in, t_tokens **tok);
int					double_char_tok(t_str_data *str_in, t_tokens **tok);
int					single_char_tok(t_str_data *str_in, t_tokens **tok);
int					content_to_token(char *content, t_tokens **tok, int type,
						t_expand *lst_expand);
int					check_char(t_str_data *str_in);
int					del_quote(char *str);
int					tok_type(char *content);
t_expand			*create_lst_expand(char *word, t_tokens **tok);

int					launch_ast(t_vars *vars);

/*AST build*/
t_ast				*is_branch(t_tokens **curr_tok, int min_prec);
t_ast				*is_term(t_tokens **curr_tok);
t_ast				*is_leaf(t_tokens **curr_tok);
bool				is_ope(int type);
int					value_prec(int type);
t_ast				*ft_astnew(t_node_type type, t_ast *left, t_ast *right);
void				del_a_tok_and_move_forward(t_tokens **curr_tok);

/*AST reader*/
int					read_ast(t_vars *vars, t_ast *current, bool is_pipe);
int					exec_pipes(t_vars *vars, t_ast *curr, int *pipe_fds,
						bool direction);
int					exec_simple(t_vars *vars, t_tokens **head, bool is_pipe);
int					exec_builtin(t_vars *vars);

/*CMD init*/
int					is_builtin(char *word);
int					sort_cmd(t_vars *vars, t_tokens **head);
int					fill_cmd_argv(t_vars *vars, t_tokens *tokens);
int					handle_files(t_cmd *cmd, t_tokens *arm);
int					here_doc_loop(t_cmd *cmd, t_tokens *curr);
char				**init_paths(t_vars *vars);
int					path_to_argv(t_cmd *cmd);
char				*cmdjoin(char *path, char *cmd);
int					multiple_dup2(t_vars *vars, int flag);
void				init_cmd_path(t_vars *vars);
int					waitchilds(t_vars *vars, int *pid, int childmax);
int					check_stds(int *stds);
int					redirections(t_vars *vars);

/*BUILTINS functions*/
int					cd(char *cd_path, t_env **envl);
void				env(t_env **envl);
int					pwd(char **arg_cmd);
int					export(char **arg_cmd, t_env **envl);
int					unset(char **cmd, t_env **envl);
int					echo(char **arg_cmd);
void				clear(void);

int					*char_to_expand(char *str);
void				del_char(char *address, char char_to_del);
int					browse_lst_and_expand(t_tokens **head, t_vars *vars);
void				content_to_lst_expand(char *to_expand, t_expand **expand);
t_expand			*ft_expand_new(char *content);
void				ft_exp_add_back(t_expand **expand, t_expand *new);
int					count_char_in_str(char *str, char c);

/*SIGNALS handler*/
void				nothing(int sig);
void				ctrl_c(int sig);
void				nothing(int sig);
char				**env_to_tab(t_env **envl);
void				expand(t_vars *vars, t_tokens **head);
void				ft_env_add_back(t_env **tok, t_env *new);
t_env				*ft_env_new(char *key, char *value);
int					unset(char **cmd, t_env **envl);
void				ctrl_c_child(int sig);

int					exit_prog(int code_err);

void				shrek_print(void);
void				bye_print(void);

#endif