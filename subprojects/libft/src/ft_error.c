#include "libft.h"
#include <stdlib.h>
#include <sys/errno.h>

void	ft_error(int status, int errnum, const char *format, ...)
{
	extern char	*__progname;
	va_list		ap;

	if (format != NULL) {
		va_start(ap, format);
		ft_dprintf(2, "%s: ", __progname);
		ft_vdprintf(2, format, &ap);
		va_end(ap);
	}

	if (errnum != 0) {
		ft_dprintf(2, ": %s", strerror(errnum));
	}

	ft_putchar_fd('\n', 2);

	if (status != 0) {
		exit(status);
	}
}