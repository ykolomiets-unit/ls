#include "ls.h"
#include "libft.h"

void	process_files(struct file_info *files, int files_count, struct ls_flags flags)
{
	(void)flags;
	for (int i = 0; i < files_count; i++) {
		ft_printf("%s\n", files[i].name);
	}
}