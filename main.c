/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:59:32 by ybereshc          #+#    #+#             */
/*   Updated: 2019/02/02 18:59:33 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_readdir(char *dir)
{
	DIR			*dfd;
	char		*path;
	t_ary_finfo	*res;

	res = ft_array(1);
	ft_bzero(g_ls.width, sizeof(g_ls.width));
	if (!(dfd = opendir(dir)))
	{
		if (!((path = ft_strrchr(dir, '/') + 1) - 1))
			path = dir;
		ERROR(path);
		ft_array_free(res);
		return ;
	}
	while ((g_tmp.dirent = readdir(dfd)))
	{
		if (!(g_f & a) && g_tmp.dirent->d_name[0] == '.')
			continue;
		path = ft_format("%s/%s", dir, g_tmp.dirent->d_name);
		ls_width(ft_array_push(res, ls_get_info(path)));
	}
	closedir(dfd);
	ls_sort(res->finfo, res->len);
	ls_print(dir, res);
	ls_recursion(res, 0);
}

void		ls_recursion(t_ary_finfo *rec, int8_t a)
{
	int		i;
	char	*name;

	i = -1;
	while (++i < rec->len)
	{
		name = rec->finfo[i]->name;
		if (rec->finfo[i]->attr[0] == 'd' && (g_f & R || a))
			if ((ft_strcmp(name, ".") && ft_strcmp(name, "..")) || a)
			{
				g_ls.total = 0;
				ls_readdir(rec->finfo[i]->path);
			}
		ls_free(rec->finfo[i]);
	}
	ft_array_free(rec);
}

void		ls_sort_av(int ac, char **av)
{
	int			i;
	t_finfo		*finfo;
	t_ary_finfo	*res;

	res = ft_array(ac);
	if (!res)
		EXIT(__func__);
	i = -1;
	while (++i < ac)
	{
		if (!(finfo = ls_get_info(ft_strdup(av[i]))))
			continue ;
		ft_array_push(res, finfo);
		if (finfo->attr[0] != 'd')
			ls_width(finfo);
	}
	ls_sort(res->finfo, res->len);
	i = -1;
	while (++i < res->len)
		if (res->finfo[i]->attr[0] != 'd')
			ls_print_row(res->finfo[i]);
	ls_recursion(res, 1);
}

static void	ls_flags(char *s)
{
	while (*s)
	{
		IF(*s == 'l', g_f |= l);
		EF(*s == 'R', g_f |= R);
		EF(*s == 'a', g_f |= a);
		EF(*s == 'r', g_f |= r);
		EF(*s == 't', g_f |= t);
		EF(*s == 'u', g_f |= u);
		EF(*s == 'S', g_f |= S);
		EF(*s == 'i', g_f |= i);
		EF(*s == 'G', g_f |= G);
		EF(*s == 'c', g_f |= c);
		EF(*s == 'f', g_f |= f);
		EF(*s == 'g', g_f |= g | l);
		EF(*s == 'o', g_f |= o | l);
		EF(*s == '1', g_f |= 0);
		EL(exit(ft_dprintf(2, "%s: illegal option -- %c\n", g_name, *s)));
		s++;
	}
}

int			main(int ac, char **av)
{
	int		i;

	i = 0;
	if (!((g_name = ft_strrchr(av[0], '/') + 1) - 1))
		g_name = av[0];
	while (++i < ac)
	{
		if (av[i][0] == '-')
			ls_flags(&av[i][1]);
		else
			break ;
	}
	if (!(g_ac = ac - i))
		ls_readdir(".");
	else
		ls_sort_av(ac - i, av + i);
	return (0);
}
