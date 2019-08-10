#include "ls.h"
#include "libft.h"
#include <dirent.h>
#include <sys/errno.h>

extern int	errno;

static void	process_directory(struct file_info directory, struct ls_flags *flags)
{
	(void)flags;
	DIR		*dirp;
	struct dirent	*dp;
	
	dirp = opendir(directory.name);
	if (dirp == NULL) {
		ft_error(0, errno, "%s", directory.name);
		return ;
	}
	while ((dp = readdir(dirp))) {
		if (ft_strcmp(dp->d_name, ".") == 0 || ft_strcmp(dp->d_name, "..") == 0) {
			continue;
		}
		ft_printf("%s\n", dp->d_name);
	}
	closedir(dirp);
}

void		process_directories(struct file_info *directories, int directories_count,
				struct ls_flags flags, bool print_dir_name)
{
	for (int i = 0; i < directories_count; i++) {
		if (print_dir_name) {
			ft_printf("%s:\n", directories[i].name);
		}
		process_directory(directories[i], &flags);
		if (i != directories_count - 1) {
			ft_putchar('\n');
		}
	}
}