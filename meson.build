project('ft_ls', 'c', default_options:['buildtype=plain'])

src = [
	'src/main.c',
]

inc = include_directories('include')

c_args = [
	'-Wall',
	'-Wextra',
	'-Werror'
]

libft = subproject('libft')
libft_dep = libft.get_variable('libft_dep')

executable('ft_ls', src,
	include_directories: inc,
	dependencies: libft_dep,
	c_args: c_args)
