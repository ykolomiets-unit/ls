#ifndef LS_H
# define LS_H

enum boolean {
	FALSE,
	TRUE,
};

enum sort_type {
	SORT_BY_NAME,
	SORT_BY_TIME_MODIFIED,
	SORT_BY_TIME_ACCESS,
	SORT_BY_TIME_CREATION,
};

struct ls_flags {
	int	list;
	int	recursive;
	int	show_hidden;
	int	reverse;
	int	sort_type;
};

void	parse_flags(char ***argv, int *argc, struct ls_flags *flags);

#endif