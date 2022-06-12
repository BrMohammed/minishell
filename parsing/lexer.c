/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:39:49 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 22:57:57 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	agr_in_next_token(t_lexer *lexer)
{
	lexer->i++;
	if (lexer->i > lexer->size)
		return (1);
	lexer->c = lexer->src[lexer->i];
	return (0);
}

void	qeuat_detect(char *quat, int *type, char c, int *ii)
{
	if ((*quat == '\'' && c == '\'') || (*quat == '"' && c == '"'))
	{	
		*ii = *ii +1;
		*quat = '\0';
	}
	else if (c == '\'' && *quat == '\0')
	{
		*quat = '\'';
		*type = TYPE_QUOTE;
		*ii = *ii +1;
	}
	else if (c == '"' && *quat == '\0')
	{
		*quat = '"';
		*ii = *ii +1;
	}
}

int	qaut_detect_and_break_in_other(t_lexer *lexer, char **text,
	int *type, char quat)
{
	int		ii;
	char	*temp_char;

	temp_char = malloc(2);
	temp_char[1] = '\0';
	ii = 0;
	while (lexer->i <= lexer->size)
	{
		temp_char[0] = lexer->c;
		qeuat_detect(&quat, type, lexer->c, &ii);
		*text = ft_strjoin(*text, temp_char);
		if (agr_in_next_token(lexer) == 1)
			break ;
		if (((lexer->c == '(' || lexer->c == ')' || lexer->c == '&'
					|| lexer->c == '|' || lexer->c == '>' || lexer->c == '<')
				&& (quat == '\0')) || ((lexer->c == '\n' || lexer->c == '\t'
					|| lexer->c == 32) && (quat == '\0')))
			break ;
	}
	free(temp_char);
	return (ii);
}

void	string_join(t_lexer *lexer, char **text, int *type)
{
	char	quat;
	int		ii;

	ii = 0;
	quat = '\0';
	ii = qaut_detect_and_break_in_other(lexer, text, type, quat);
	if (lexer->i > lexer->size && ii % 2 != 0)
		*type = TYPE_ERROR;
	else if (ii > 0)
		*type = TYPE_QUOTE;
	else
		*type = TYPE_TEXT;
}

void	skip_redir(t_lexer *lexer, int *type, char **text, char **Temp_Char)
{
	*text[0] = lexer->c;
	agr_in_next_token(lexer);
	*Temp_Char[0] = lexer->c;
	*text = ft_strjoin(*text,*Temp_Char);
	*type = TYPE_DLredirection;
	agr_in_next_token(lexer);
}

void	give_the_type(t_lexer *lexer, int *type, char **text, char **Temp_Char)
{
	if (lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
		skip_redir(lexer, type, text, Temp_Char);
	else if (lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
		skip_redir(lexer, type, text, Temp_Char);
	else if (lexer->c == '|')
		*type = TYPE_PIPE;
	else if (lexer->c == '<')
		*type = TYPE_Lredirection;
	else if (lexer->c == '>')
		*type = TYPE_Rredirection;
	else
		string_join(lexer, text, type);
	if (*text[0] == '\0')
	{
		*text[0] = lexer->c;
		if (lexer->i <= lexer->size)
			agr_in_next_token(lexer);
	}
	if (*text[0] == '\0')
	{
		*type = TYPE_EOF;
		free(*text);
		*text = NULL;
	}
	free(*Temp_Char);
}

char	*token_type(t_lexer *lexer, int *type)
{
	char	*text;
	char	*temp_char;

	text = malloc(2);
	text[0] = '\0';
	text[1] = '\0';
	while ((lexer->i <= lexer->size) && (lexer->c == '\n'
			|| lexer->c == '\t' || lexer->c == 32))
		agr_in_next_token(lexer);
	temp_char = malloc(2);
	temp_char[0] = lexer->c;
	temp_char[1] = '\0';
	give_the_type(lexer, type, &text, &temp_char);
	return (text);
}

t_token	*get_next_token(t_lexer *lexer)
{
	t_token	*token;
	char	*temp_text;
	int		type;

	type = TYPE_TEXT;
	temp_text = token_type(lexer, &type);
	token = init_token(temp_text, type);
	free(temp_text);
	return (token);
}
