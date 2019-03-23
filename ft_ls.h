/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 13:15:54 by ybereshc          #+#    #+#             */
/*   Updated: 2019/02/03 13:15:55 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "lib/libft.h"
# include "ls_typedef.h"
# include <uuid/uuid.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/dir.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <string.h>

# define ERROR(i) ft_dprintf(2, "%s: %s: %s\n", g_name, i, strerror(errno))
# define EXIT(m) exit(ft_dprintf(2,"%s: %s\n", g_name, m))
# define COLUMNS 6

/*
** Bonus uSiGc@
*/
enum	e_flags
{
	l = 1,
	R = 2,
	a = 4,
	r = 8,
	t = 16,
	u = 32,
	S = 64,
	i = 128,
	G = 256,
	c = 512,
	at = 1024,
	f = 2048,
	g = 4096,
	o = 8192
};

struct	s_ary_finfo
{
	t_finfo	**finfo;
	int		len;
	int		max;
};

struct	s_finfo
{
	char		*ino;
	char		*attr;
	char		*links;
	char		*user;
	char		*group;
	char		*size;
	char		*date;
	char		*name;
	char		*perent;
	char		*path;

	char		*color;
	intmax_t	s_date;
	intmax_t	s_size;
};

struct	s_tmp
{
	struct stat		stat;
	struct dirent	*dirent;
	char			*path;
};

struct	s_ls
{
	t_ary_finfo	*res;
	int			width[COLUMNS];
	int			total;
};

char	*g_name;
t_ls	g_ls;
t_tmp	g_tmp;
t_flags	g_f;
int		g_ln;
int		g_ac;

t_finfo	*ls_get_info(char *path);
char	*ls_get_attr(char *p, int m);
char	*ls_color(char *attr);
void	ls_width(t_finfo *row);
void	ls_sort(t_finfo **ary, int n);
void	sort_by_ascii(t_finfo **ary, int n);
void	sort_by_time(t_finfo **ary, int n);
void	sort_by_size(t_finfo **ary, int n);
void	ls_recursion(t_ary_finfo *rec, int8_t a);

t_finfo	*ls_print_row(t_finfo *finfo);
void	ls_print(char *path, t_ary_finfo *ary);
void	ls_free(t_finfo *finfo);

#endif
