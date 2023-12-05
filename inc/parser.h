/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:40:29 by soutin            #+#    #+#             */
/*   Updated: 2023/12/05 15:59:26 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	PIPE,
	OR,
	AND,
	O_PARENTHESIS,
	C_PARENTHESIS,
	WORD,
	ERRORLVL,
	LIMITER,
	CLOBBER,
	INDEFINE,
}					t_token_type;

typedef enum e_node_type
{
	NPIPE,
	NAND,
	NOR,
	NCMD,
}					t_node_type;

typedef struct s_tokens
{
	char			*string;
	int				type;
	int				*expand;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_str_data
{
	char			*buff;
	int				buff_size;
	int				curpos;
}					t_str_data;

typedef struct s_ast
{
	struct s_tokens	*tokens;
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

int					token_m(t_str_data *str_in, t_tokens **tok);
int					check_char(t_str_data *str_in);
int					del_quote(char *str);
int					tok_type(char *content);

t_ast				*is_branch(t_tokens **curr_tok, int min_prec);
bool				is_ope(int type);
int					value_prec(int type);
t_ast				*ft_astnew(t_node_type type, t_ast *left, t_ast *right);
void				del_a_tok_and_move_forward(t_tokens **curr_tok);

// int					is_branch(t_tokens **curr_tok, t_ast **curr_node,
// bool from_pipe);
// void				ft_newleaf(t_ast **node,
// t_tokens **current);
// int					is_last_leaf(t_tokens *current);

#endif