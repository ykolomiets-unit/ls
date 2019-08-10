#ifndef LS_H
# define LS_H

# include <stdbool.h>
# include <sys/stat.h>

enum sort_type {
	SORT_BY_NAME,
	SORT_BY_TIME_MODIFIED,
	SORT_BY_TIME_ACCESS,
	SORT_BY_TIME_CREATION,
};

struct ls_flags {
	bool	list;
	bool	recursive;
	bool	show_hidden;
	bool	reverse;
	bool	sort_type;
};

struct	file_info {
	char		*name;
	struct stat	stat;
};

struct	failed_file_info {
	char	*name;
	int	error_code;
};

void	parse_flags(char ***argv, int *argc, struct ls_flags *flags);
void	process_files(struct file_info *files, int files_count, struct ls_flags flags);
void	process_directories(struct file_info *directories, int directories_count,
				struct ls_flags flags, bool print_dir_name);

#endif