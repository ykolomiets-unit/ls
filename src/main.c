#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/errno.h>

#define USAGE_STR "usage: ls [-alrtR] [file ...]\n"

#define TRUE	1
#define FALSE	0

#define SORT_BY_NAME			0
#define SORT_BY_TIME_MODIFIED	1
#define SORT_BY_TIME_ACCESS		2
#define SORT_BY_TIME_CREATION	3

extern int	errno;

typedef char		t_bool;
typedef char		t_sort_type;

typedef struct		s_flags
{
	t_bool			list;
	t_bool			recursive;
	t_bool			show_hidden;
	t_bool			reverse;
	t_sort_type		sort_type;
}					t_flags;

typedef struct stat	t_stat;


void	illegal_option(char option)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", option);
	ft_dprintf(2, USAGE_STR);
	exit(1);
}

void	parse_flags(char ***argv, int *argc, t_flags *flags)
{
	const char	*argument;

	while ((argument = **argv) && argument[0] == '-')
	{
		(*argv)++;
		(*argc)--;

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
				flags->sort_type = SORT_BY_TIME_MODIFIED;
			else
				illegal_option(*argument);
			argument++;
		}
	}
}

typedef struct	s_file
{
	char		*name;
	t_stat		stat;
}				t_file;

typedef struct	s_failed_file
{
	char		*name;
	int			error_code;
}				t_failed_file;



void	process_passed_files(char **file_names, int file_names_count, t_flags flags)
{
	(void)flags;
	t_stat	info;
	char	*filename;
	t_failed_file	*failed;
	int				failed_count;
	t_file			*files;
	int				files_count;
	t_file			*directories;
	int				directories_count;

	failed = (t_failed_file*)ft_memalloc(sizeof(t_failed_file) * file_names_count);
	failed_count = 0;
	files = (t_file*)ft_memalloc(sizeof(t_file) * file_names_count);
	files_count = 0;
	directories = (t_file*)ft_memalloc(sizeof(t_file) * file_names_count);
	directories_count = 0;
	while ((filename = *file_names) != NULL)
	{
		if (lstat(filename, &info) == 0)
		{
			if (S_ISDIR(info.st_mode))
				directories[directories_count++] = (t_file){ filename, info };
			else
				files[files_count++] = (t_file){ filename, info };
		}
		else
		{
			failed[failed_count++] = (t_failed_file){ filename, errno };
		}
		file_names++;
	}
	ft_printf("FAILED: %d\n", failed_count);
	ft_printf("FILES: %d\n", files_count);
	ft_printf("DIRS: %d\n", directories_count);
	free(failed);
	free(files);
	free(directories);
}

int main(int argc, char **argv)
{
	(void)argc;
	static char	*default_files[] = { "." };
	t_flags	flags;

	argv++;
	argc--;
	parse_flags(&argv, &argc, &flags);
	if (*argv == NULL)
		process_passed_files(default_files, 1, flags);
	else
		process_passed_files(argv, argc, flags);
	return (0);
}
