#include "sh42.h"

void init_assign_analyze(t_anal analyze)
{
	analyze[A_ASSIGN][P_NEWLINE] = separator_analyze;
	analyze[A_ASSIGN][P_ANDIF] = separator_analyze;
	analyze[A_ASSIGN][P_AND] = separator_analyze;
	analyze[A_ASSIGN][P_ORIF] = separator_analyze;
	analyze[A_ASSIGN][P_PIPE] = separator_analyze;
	analyze[A_ASSIGN][P_DSEMI] = error_analyze;
	analyze[A_ASSIGN][P_SEMICOLON] = separator_analyze;
	analyze[A_ASSIGN][P_DLESSDASH] = redirect_analyze;
	analyze[A_ASSIGN][P_DLESS] = redirect_analyze;
	analyze[A_ASSIGN][P_LESSGREAT] = redirect_analyze;
	analyze[A_ASSIGN][P_LESS] = redirect_analyze;
	analyze[A_ASSIGN][P_DGREAT] = redirect_analyze;
	analyze[A_ASSIGN][P_GREATAND] = redirect_analyze;
	analyze[A_ASSIGN][P_GREAT] = redirect_analyze;
	analyze[A_ASSIGN][P_IONUMBER] = error_analyze;
	analyze[A_ASSIGN][P_ASSIGN] = assign_analyze;
	analyze[A_ASSIGN][P_WORD] = cmd_analyze;
	analyze[A_ASSIGN][P_DBPARENT] = expansion_analyze;
	analyze[A_ASSIGN][P_PARENT] = expansion_analyze;
	analyze[A_ASSIGN][P_BRACKET] = expansion_analyze;
	analyze[A_ASSIGN][P_HOOK] = expansion_analyze;
	analyze[A_ASSIGN][P_DOLLAR] = expansion_analyze;
	analyze[A_ASSIGN][P_TILDE] = expansion_analyze;
	analyze[A_ASSIGN][P_END] = end_analyze;
}

void init_ionumber_analyze(t_anal analyze)
{
	analyze[A_IONUMBER][P_NEWLINE] = error_analyze;
	analyze[A_IONUMBER][P_ANDIF] = error_analyze;
	analyze[A_IONUMBER][P_AND] = error_analyze;
	analyze[A_IONUMBER][P_ORIF] = error_analyze;
	analyze[A_IONUMBER][P_PIPE] = error_analyze;
	analyze[A_IONUMBER][P_DSEMI] = error_analyze;
	analyze[A_IONUMBER][P_SEMICOLON] =  error_analyze;
	analyze[A_IONUMBER][P_DLESSDASH] = redirect_analyze;
	analyze[A_IONUMBER][P_DLESS] = redirect_analyze;
	analyze[A_IONUMBER][P_LESSGREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_LESS] = redirect_analyze;
	analyze[A_IONUMBER][P_DGREAT] = redirect_analyze;
	analyze[A_IONUMBER][P_GREATAND] = redirect_analyze;
	analyze[A_IONUMBER][P_GREAT] =	redirect_analyze;
	analyze[A_IONUMBER][P_IONUMBER] = error_analyze;
	analyze[A_IONUMBER][P_ASSIGN] = error_analyze;
	analyze[A_IONUMBER][P_WORD] = cmd_analyze;
	analyze[A_IONUMBER][P_DBPARENT] = error_analyze;
	analyze[A_IONUMBER][P_PARENT] = error_analyze;
	analyze[A_IONUMBER][P_BRACKET] = error_analyze;
	analyze[A_IONUMBER][P_HOOK] = error_analyze;
	analyze[A_IONUMBER][P_DOLLAR] = error_analyze;
	analyze[A_IONUMBER][P_TILDE] = error_analyze;
	analyze[A_IONUMBER][P_END] = end_analyze;
}

void init_redirect_analyze(t_anal analyze)
{
	analyze[A_REDIRECT][P_NEWLINE] = redirect_analyze;
	analyze[A_REDIRECT][P_ANDIF] = error_analyze;
	analyze[A_REDIRECT][P_AND] = error_analyze;
	analyze[A_REDIRECT][P_ORIF] = error_analyze;
	analyze[A_REDIRECT][P_PIPE] = separator_analyze;
	analyze[A_REDIRECT][P_DSEMI] = error_analyze;
	analyze[A_REDIRECT][P_SEMICOLON] =  end_analyze;
	analyze[A_REDIRECT][P_DLESSDASH] = redirect_analyze;
	analyze[A_REDIRECT][P_DLESS] = redirect_analyze;
	analyze[A_REDIRECT][P_LESSGREAT] = redirect_analyze;
	analyze[A_REDIRECT][P_LESS] = redirect_analyze;
	analyze[A_REDIRECT][P_DGREAT] = redirect_analyze;
	analyze[A_REDIRECT][P_GREATAND] = redirect_analyze;
	analyze[A_REDIRECT][P_GREAT] =	redirect_analyze;
	analyze[A_REDIRECT][P_IONUMBER] = ionbr_analyze;
	analyze[A_REDIRECT][P_ASSIGN] = assign_analyze;
	analyze[A_REDIRECT][P_WORD] = cmd_analyze;
	analyze[A_REDIRECT][P_DBPARENT] = error_analyze;
	analyze[A_REDIRECT][P_PARENT] = error_analyze;
	analyze[A_REDIRECT][P_BRACKET] = error_analyze;
	analyze[A_REDIRECT][P_HOOK] = error_analyze;
	analyze[A_REDIRECT][P_DOLLAR] = error_analyze;
	analyze[A_REDIRECT][P_TILDE] = error_analyze;
	analyze[A_REDIRECT][P_END] = end_analyze;
}

void init_end_analyze(t_anal analyze)
{
	analyze[A_END][P_NEWLINE] = end_analyze;
	analyze[A_END][P_ANDIF] = separator_analyze;
	analyze[A_END][P_AND] = separator_analyze;
	analyze[A_END][P_PIPE] = redirect_analyze;
	analyze[A_END][P_ORIF] = separator_analyze;
	analyze[A_END][P_DSEMI] = error_analyze;
	analyze[A_END][P_SEMICOLON] = separator_analyze;
	analyze[A_END][P_DLESSDASH] = redirect_analyze;
	analyze[A_END][P_DLESS] = redirect_analyze;
	analyze[A_END][P_LESSGREAT] = redirect_analyze;
	analyze[A_END][P_LESS] = redirect_analyze;
	analyze[A_END][P_DGREAT] = redirect_analyze;
	analyze[A_END][P_GREATAND] = redirect_analyze;
	analyze[A_END][P_GREAT] = redirect_analyze;
	analyze[A_END][P_IONUMBER] = ionbr_analyze;
	analyze[A_END][P_ASSIGN] = assign_analyze;
	analyze[A_END][P_WORD] = cmd_analyze;
	analyze[A_END][P_DBPARENT] = expansion_analyze;
	analyze[A_END][P_PARENT] = expansion_analyze;
	analyze[A_END][P_BRACKET] = expansion_analyze;
	analyze[A_END][P_HOOK] = expansion_analyze;
	analyze[A_END][P_DOLLAR] = expansion_analyze;
	analyze[A_END][P_TILDE] = expansion_analyze;
	analyze[A_END][P_END] = end_analyze;
}

void	init_separator_analyze(t_anal analyze)
{
	analyze[A_SEPARATOR][P_AND] = separator_analyze;
	analyze[A_SEPARATOR][P_PIPE] = separator_analyze;
	analyze[A_SEPARATOR][P_GREAT] = redirect_analyze;
	analyze[A_SEPARATOR][P_GREATAND] = redirect_analyze;
	analyze[A_SEPARATOR][P_LESS] = redirect_analyze;
	analyze[A_SEPARATOR][P_LESSAND] = redirect_analyze;
	analyze[A_SEPARATOR][P_DGREAT] = redirect_analyze;
	analyze[A_SEPARATOR][P_DLESS] = redirect_analyze;
	analyze[A_SEPARATOR][P_DLESSDASH] = redirect_analyze;
	analyze[A_SEPARATOR][P_SEMICOLON] = separator_analyze;
	analyze[A_SEPARATOR][P_NEWLINE] = end_analyze;
	analyze[A_SEPARATOR][P_IONUMBER] = ionbr_analyze;
	analyze[A_SEPARATOR][P_ASSIGN] = assign_analyze;
	analyze[A_SEPARATOR][P_WORD] = cmd_analyze;
	analyze[A_SEPARATOR][P_DBPARENT] = expansion_analyze;
	analyze[A_SEPARATOR][P_PARENT] = expansion_analyze;
	analyze[A_SEPARATOR][P_BRACKET] = expansion_analyze;
	analyze[A_SEPARATOR][P_HOOK] = expansion_analyze;
	analyze[A_SEPARATOR][P_DOLLAR] = expansion_analyze;
	analyze[A_SEPARATOR][P_TILDE] = expansion_analyze;
	analyze[A_SEPARATOR][P_END] = end_analyze;
}
