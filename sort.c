/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhrypko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:22:51 by ikhrypko          #+#    #+#             */
/*   Updated: 2019/02/04 17:22:53 by ikhrypko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_by_ascii(t_finfo **ary, int n)
{
	int		i;
	int		j;
	t_finfo	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = i;
		while (++j < n)
		{
			if (!(g_f & r) && ft_strcmp(ary[i]->name, ary[j]->name) > 0)
			{
				tmp = ary[j];
				ary[j] = ary[i];
				ary[i] = tmp;
			}
			else if (g_f & r && ft_strcmp(ary[i]->name, ary[j]->name) < 0)
			{
				tmp = ary[j];
				ary[j] = ary[i];
				ary[i] = tmp;
			}
		}
	}
}

void	sort_by_time(t_finfo **ary, int n)
{
	int		i;
	int		j;
	t_finfo	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = n;
		while (i < --j)
		{
			if (!(g_f & r) && ary[j]->s_date > ary[j - 1]->s_date)
			{
				tmp = ary[j - 1];
				ary[j - 1] = ary[j];
				ary[j] = tmp;
			}
			else if (g_f & r && ary[j]->s_date < ary[j - 1]->s_date)
			{
				tmp = ary[j - 1];
				ary[j - 1] = ary[j];
				ary[j] = tmp;
			}
		}
	}
}

void	sort_by_size(t_finfo **ary, int n)
{
	int		i;
	int		j;
	t_finfo	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = n;
		while (i < --j)
		{
			if (!(g_f & r) && ary[j]->s_size > ary[j - 1]->s_size)
			{
				tmp = ary[j - 1];
				ary[j - 1] = ary[j];
				ary[j] = tmp;
			}
			else if (g_f & r && ary[j]->s_size < ary[j - 1]->s_size)
			{
				tmp = ary[j - 1];
				ary[j - 1] = ary[j];
				ary[j] = tmp;
			}
		}
	}
}
