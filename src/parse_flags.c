#include "ls.h"
#include "libft.h"

#define USAGE_STR "usage: ls [-alrtR] [file ...]"

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
				flags->list = true;
				break;
			case 'R':
				flags->recursive = true;
				break;
			case 'a':
				flags->show_hidden = true;
				break;
			case 'r':
				flags->reverse = true;
				break;
			case 't':
				flags->sort_type = SORT_BY_TIME_MODIFIED;
				break;
			default:
				ft_error(1, 0, "illegal option -- %c\n%s", *argument, USAGE_STR);
			}
			argument++;
		}
	}
}