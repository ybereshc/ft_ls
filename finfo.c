/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finfo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:56:32 by ybereshc          #+#    #+#             */
/*   Updated: 2019/02/06 10:56:33 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*ls_link(char *path)
{
	ssize_t	n;
	char	link[1024];

	n = readlink(path, link, sizeof(link));
	if (n < 1)
		return (0);
	return (ft_strndup(link, n));
}

static void		ls_date(t_finfo *res)
{
	int	i;

	if (g_f & u)
	{
		res->date = ft_strdup(ctime(&g_tmp.stat.st_atime) + 4);
		res->s_date = g_tmp.stat.st_atimespec.tv_sec;
	}
	else if (g_f & c)
	{
		res->date = ft_strdup(ctime(&g_tmp.stat.st_ctime) + 4);
		res->s_date = g_tmp.stat.st_ctimespec.tv_sec;
	}
	else
	{
		res->date = ft_strdup(ctime(&g_tmp.stat.st_mtime) + 4);
		res->s_date = g_tmp.stat.st_mtimespec.tv_sec;
	}
	if (!res->date)
		EXIT(__func__);
	i = time(0) - res->s_date;
	if (i > 15768000 || i < 0)
		ft_memcpy(res->date + 7, res->date + 15, 5);
}

t_finfo			*ls_get_info(char *path)
{
	t_finfo	*res;

	if (!lstat(path, &g_tmp.stat))
	{
		res = malloc(sizeof(t_finfo));
		res->path = path;
		res->name = ft_strrchr(res->path, '/');
		res->name = ft_strdup((res->name && res->name[1])
			? res->name + 1 : res->path);
		ls_date(res);
		res->ino = ft_uint_to_str(g_tmp.stat.st_ino, 10);
		res->attr = ls_get_attr(path, g_tmp.stat.st_mode);
		res->links = ft_uint_to_str(g_tmp.stat.st_nlink, 10);
		res->user = ft_strdup(((t_passwd)getpwuid(g_tmp.stat.st_uid))->pw_name);
		res->group = ft_strdup(((t_group)getgrgid(g_tmp.stat.st_gid))->gr_name);
		res->s_size = g_tmp.stat.st_size;
		res->size = ft_uint_to_str(g_tmp.stat.st_size, 10);
		res->color = (g_f & G) ? ls_color(res->attr) : 0;
		res->perent = ls_link(path);
		g_ls.total += g_tmp.stat.st_blocks;
		return (res);
	}
	ERROR(path);
	return (ft_free(1, path));
}
