#include "ls.h"
#include "libft.h"
#include <sys/errno.h>
#include <stdlib.h>

extern int errno;

static int	failed_cmp(const void *a, const void *b)
{
	return ft_strcmp(((struct failed_file_info *)a)->name,((struct failed_file_info *)b)->name);
}

static void	print_failed_files(struct failed_file_info *failed, int count)
{
	qsort(failed, count, sizeof(failed[0]), failed_cmp);
	for (int i = 0; i < count; i++)	{
		ft_error(0, failed[i].error_code, "%s", failed[i].name);
	}
}

static void	sort_passed_files_by_type(
				char **file_names,
				struct failed_file_info *failed, int *failed_count,
				struct file_info *files, int *files_count,
				struct file_info *directories, int *directories_count)
{
	char		*name;
	struct stat	info;

	while ((name = *file_names) != NULL) {
		if (lstat(name, &info) == 0) {
			if (S_ISDIR(info.st_mode)) {
				directories[*directories_count].name = name;
				directories[*directories_count].stat = info;
				(*directories_count)++;
			} else {
				files[*files_count].name = name;
				files[*files_count].stat = info;
				(*files_count)++;
			}
		} else {
			failed[*failed_count].name = name;
			failed[*failed_count].error_code = errno;
			(*failed_count)++;
		}
		file_names++;
	}
}

void	process_passed_files(char **file_names, int file_names_count, struct ls_flags flags)
{
	struct failed_file_info	*failed;
	int			failed_count = 0;
	struct file_info	*files;
	int			files_count = 0;
	struct file_info	*directories;
	int			directories_count = 0;

	failed = ft_memalloc(sizeof(struct failed_file_info) * file_names_count);
	files = ft_memalloc(sizeof(struct file_info) * file_names_count);
	directories = ft_memalloc(sizeof(struct file_info) * file_names_count);
	sort_passed_files_by_type(file_names, failed, &failed_count, files, &files_count,
					directories, &directories_count);

	if (failed_count > 0) {
		print_failed_files(failed, failed_count);
	}
	free(failed);

	if (files_count > 0) {
		process_files(files, files_count, flags);
		if (directories_count > 0) {
			ft_putchar('\n');
		}
	}
	free(files);

	if (directories_count > 0) {
		process_directories(directories, directories_count, flags, file_names_count > 1);
	}
	free(directories);
}

int main(int argc, char **argv)
{
	static char	*dotav[] = { "." };
	struct ls_flags	flags;

	argv++;
	argc--;
	parse_flags(&argv, &argc, &flags);
	if (*argv == NULL) {
		process_passed_files(dotav, 1, flags);
	} else {
		process_passed_files(argv, argc, flags);
	}
	return (0);
}
