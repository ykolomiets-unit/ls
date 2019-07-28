#include "libft.h"
#include <stdlib.h>

#define USAGE_STR "usage: ls [-alrtR] [file ...]\n"

#define TRUE	1
#define FALSE	0

#define SORT_BY_NAME					0
#define SORT_BY_TIME_MODIFIED	1
#define SORT_BY_TIME_ACCESS		2
#define SORT_BY_TIME_CREATION	3

typedef char	t_bool;
typedef char	t_sort_type;

typedef struct	s_flags
{
	t_bool			list;
	t_bool			recursive;
	t_bool			show_hidden;
	t_bool			reverse;
	t_sort_type	sort_by_time;
}								t_flags;

void	illegal_option(char option)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", option);
	ft_dprintf(2, USAGE_STR);
	exit(1);
}

void	parse_flags(char ***argv, t_flags *flags)
{
	const char	*argument;

	while ((argument = **argv) && argument[0] == '-')
	{
		(*argv)++;

		if (ft_strcmp(argument, "--") == 0)
			break ;
		argument++;
		while (*argument)
		{
			if (*argument == 'l')
				flags->list = TRUE;
			else if (*argument == 'R')
				flags->recursive = TRUE;
			else if (*argument == 'a')
				flags->show_hidden = TRUE;
			else if (*argument == 'r')
				flags->reverse = TRUE;
			else if (*argument == 't')
				flags->sort_by_time = SORT_BY_TIME_MODIFIED;
			else
				illegal_option(*argument);
			argument++;
		}
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	t_flags	flags;

	argv++;
	parse_flags(&argv, &flags);
	return (0);
}
