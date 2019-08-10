#include "ls.h"
#include "libft.h"
#include <stdlib.h>

#define USAGE_STR "usage: ls [-alrtR] [file ...]\n"

void	parse_flags(char ***argv, int *argc, struct ls_flags *flags)
{
	const char	*argument;

	while ((argument = **argv) && argument[0] == '-') {
		(*argv)++;
		(*argc)--;

		if (ft_strcmp(argument, "--") == 0)
			return ;
		argument++;
		while (*argument) {
			switch(*argument) {
			case 'l':
				flags->list = TRUE;
				break;
			case 'R':
				flags->recursive = TRUE;
				break;
			case 'a':
				flags->show_hidden = TRUE;
				break;
			case 'r':
				flags->reverse = TRUE;
				break;
			case 't':
				flags->sort_type = SORT_BY_TIME_MODIFIED;
				break;
			default:
				ft_dprintf(2, "ls: illegal option -- %c\n%s", *argument, USAGE_STR);
				exit(1);
			}
			argument++;
		}
	}
}