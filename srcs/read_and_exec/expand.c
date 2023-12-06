/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:51:16 by soutin            #+#    #+#             */
/*   Updated: 2023/12/06 20:26:10 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lst_expand(char *word, t_tokens **tok)
{
	t_expand	*lst_expand;
	char		*dollars_expand;
	int			i_word;
	int			i_dollars_expand;
	char		quote_char;

	lst_expand = NULL;
	i_dollars_expand = 0;
	i_word = 0;
	quote_char = false;
	while (word[i_word])
	{
		if (word[i_word] == '\'' || word[i_word] == '\"')
		{
			if (!quote_char)
			{
				quote_char = word[i_word];
				if(quote_char == '\'')
					
					
			}
			else if (quote_char == word[i_word])
				quote_char = false;
		}
		i_word++;
	}
}
