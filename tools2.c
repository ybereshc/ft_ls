/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:42:05 by ybereshc          #+#    #+#             */
/*   Updated: 2019/02/04 16:42:07 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_finfo	*ls_print_row(t_finfo *finfo)
{
	g_ln = 1;
	if (!finfo)
		return (0);
	if (g_f & i)
		ft_printf("%*s ", g_ls.width[0], finfo->ino);
	if (g_f & l)
	{
		ft_printf("%s ", finfo->attr);
		ft_printf("%*s ", g_ls.width[2], finfo->links);
		if (!(g_f & g))
			ft_printf("%-*s  ", g_ls.width[3], finfo->user);
		if (!(g_f & o))
			ft_printf("%-*s  ", g_ls.width[4], finfo->group);
		ft_printf("%*s ", g_ls.width[5], finfo->size);
		ft_printf("%.12s ", finfo->date);
	}
	if (finfo->color)
		ft_printf("%s%s\e[0m", finfo->color, finfo->name);
	else
		ft_printf("%s", finfo->name);
	if (finfo->perent)
		ft_printf(" -> %s", finfo->perent);
	ft_printf("\n");
	return (finfo);
}

void	ls_print(char *path, t_ary_finfo *ary)
{
	int			i;
	static int	ln;

	if (ln || g_ln)
		ft_printf("\n");
	if (g_ac > 1 || g_ln)
		ft_printf("%s:\n", path);
	if (ary->len)
	{
		if (g_f & l)
			ft_printf("total %d\n", g_ls.total);
		i = -1;
		while (++i < ary->len)
			ls_print_row(ary->finfo[i]);
	}
	ln = 1;
}
