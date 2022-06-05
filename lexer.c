#include "minishell.h"

void AgrimNextToken(t_lexer* lexer)
{
	lexer->i++;
	lexer->c = lexer->src[lexer->i];
}

void string_join(t_lexer *lexer, char **text,int *type)
{
	char quat;
	char *Temp_Char;
	int ii = 0;

	Temp_Char = malloc(2);
	Temp_Char[1] = '\0';
	quat = '\0';
	while(lexer->i <= lexer->size)
	{
		Temp_Char[0] = lexer->c;
		if((quat == '\'' && lexer->c == '\'') || (quat == '"' && lexer->c == '"'))
		{	
			ii++;
			quat = '\0';
		}
		else if(lexer->c == '\'' && quat == '\0')
		{
			quat = '\'';
			*type = TYPE_QUOTE;
			ii++;
		}
		else if(lexer->c == '"' && quat == '\0')
		{
			quat = '"';
			ii++;
		}
		*text = ft_strjoin(*text,Temp_Char);
		AgrimNextToken(lexer);
		if(((lexer->c == '(' || lexer->c == ')' || lexer->c == '&' ||lexer->c == '|' 
		|| lexer->c == '>' || lexer->c == '<') && ( quat == '\0')) || ((lexer->c == '\n' || lexer->c  == '\t' 
		|| lexer->c  == 32) && ( quat == '\0')))
			break;
	}
	if (lexer->i > lexer->size && ii % 2 != 0)
		*type = TYPE_ERROR;
	else if(ii > 0)
		*type = TYPE_QUOTE;
	else
		*type = TYPE_TEXT;
	free(Temp_Char);
}

char* token_type(t_lexer *lexer, int *type)
{
	char* text;
	char *Temp_Char;

	text = malloc(2);
	text[0] = '\0';
	text[1] = '\0';
	while((lexer->i <= lexer->size ) && (lexer->c == '\n' || lexer->c  == '\t' || lexer->c  == 32))
		AgrimNextToken(lexer);
	Temp_Char = malloc(2);
	Temp_Char[0] = lexer->c;
	Temp_Char[1] = '\0';
	
	if(lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
	{
		text[0] = lexer->c;
		AgrimNextToken(lexer);
		Temp_Char[0] = lexer->c;
		text = ft_strjoin(text,Temp_Char);
		*type = TYPE_DLredirection;
		AgrimNextToken(lexer);
	}
	else if(lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
	{
		text[0] = lexer->c;
		AgrimNextToken(lexer);
		Temp_Char[0] = lexer->c;
		text = ft_strjoin(text,Temp_Char);
		*type = TYPE_DRredirection;
		AgrimNextToken(lexer);
	}
	else if(lexer->c == '|')
		*type = TYPE_PIPE;
	else if(lexer->c == '<')
		*type = TYPE_Lredirection;
	else if(lexer->c == '>')
		*type = TYPE_Rredirection;
	else
		string_join(lexer, &text, type);
	if(text[0] == '\0')
	{
		text[0] = lexer->c;
		if(lexer->i <= lexer->size)
			AgrimNextToken(lexer);
	}
	if(text[0] == '\0')
	{
		*type = TYPE_EOF;
		free(text);
		text = NULL;
	}
	free(Temp_Char);
	return(text);
}

t_token *GetNextToken(t_lexer *lexer)
{
	t_token *token;
	char* temp_text;
	int type;

	type = TYPE_TEXT;
	temp_text = token_type(lexer, &type);
	token = init_token(temp_text,type);
	free(temp_text);
	return(token);
}
