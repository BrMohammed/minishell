#include "lexer.h"
# include "libft/libft.h"

void AgrimNextToken(t_lexer* lexer)
{
	lexer->i++;
	lexer->c = lexer->src[lexer->i];
}


void string_join(t_lexer *lexer, char **text)
{
	char quat;
	while(lexer->i <= lexer->size)
	{
		if((quat == '\'' && lexer->c == '\'') || (quat == '"' && lexer->c == '"'))
		{
			*text = ft_strjoin(*text,&lexer->c);
			AgrimNextToken(lexer);
			break;
		}
		if(lexer->c == '\'' && quat == '\0')
			quat = '\'';
		else if(lexer->c == '"' && quat == '\0')
			quat = '"';
		*text = ft_strjoin(*text,&lexer->c);
		AgrimNextToken(lexer);
		if((lexer->c == '(' || lexer->c == ')' || lexer->c == '&' ||lexer->c == '|' || lexer->c == '>' || lexer->c == '<') || ((lexer->c == '\n' || lexer->c  == '\t' || lexer->c  == 32) && ( quat == '\0')))
			break;
	}
	
}

char* token_type(t_lexer *lexer, int *type)
{
	char* text;
	char *Temp_Char;

	text = malloc(1);
	Temp_Char = malloc(2);
	Temp_Char[0] = lexer->c;
	Temp_Char[1] = '\0';
	while((lexer->i <= lexer->size ) && (lexer->c == '\n' || lexer->c  == '\t' || lexer->c  == 32))
		AgrimNextToken(lexer);
	if(lexer->c == '(')
		*type = TYPE_LPARENT;
	else if(lexer->c == ')')
		*type = TYPE_RPARENT;
	else if(lexer->c == '&')
		*type = TYPE_AND;
	else if(lexer->c == '|')
		*type = TYPE_PIPE;
	else if(lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
	{
		AgrimNextToken(lexer);
		text = ft_strjoin(Temp_Char,&lexer->c);
		*type = TYPE_DLredirection;
		AgrimNextToken(lexer);
	}
	else if(lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
	{
		AgrimNextToken(lexer);
		*type = TYPE_DRredirection;
		text = ft_strjoin(Temp_Char,&lexer->c);
		AgrimNextToken(lexer);
	}
	else if(lexer->c == '<')
		*type = TYPE_Lredirection;
	else if(lexer->c == '>')
		*type = TYPE_Rredirection;
	else
	{
		string_join(lexer, &text);
		*type = TYPE_TEXT;
	}
	if(text[0] == '\0')
	{
		text = ft_strdup(&lexer->c);
		AgrimNextToken(lexer);
	}
	if(text[0] == '\0')
		*type = TYPE_EOF;
	return(text);
}

void GetNextToken(t_lexer *lexer)
{
	t_token *token;
	char* temp_text;
	int type;
	
	temp_text = token_type(lexer, &type);
	token = init_token(temp_text,type);
	if(type != TYPE_EOF)
		printf("%s , %d\n",token->value,token->type);
}

void PrintTokens(char* all)
{
	
	t_lexer *lexer;
	
	lexer = init_lexer(all);
	while(lexer->i <= lexer->size)
		GetNextToken(lexer);
	free(lexer);
}
int main(int argc, char** argv, char** envp)
{
	char    *all;

	(void)argv;
	(void) envp;
	if(argc == 1)
	{
		while (1)
		{
			all = readline("minishell ");
			PrintTokens(all);
			free(all);
		}
	}
	return (0);
}