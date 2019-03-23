/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 18:07:53 by ybereshc          #+#    #+#             */
/*   Updated: 2019/02/09 18:07:54 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_ts(char *res, int m)
{
	if (m & S_ISUID)
		res[3] = (res[3] != 'x') ? 'S' : 's';
	if (m & S_ISGID)
		res[6] = (res[9] != 'x') ? 'S' : 's';
	if (m & S_ISVTX)
		res[9] = (res[9] != 'x') ? 'T' : 't';
}

static char		ls_xattr(char *p)
{
	ssize_t		xattr;
	acl_t		acl;
	int			acll;

	acll = 0;
	if ((acl = acl_get_link_np(p, 256)))
		acll = 1;
	acl_free(acl);
	if ((xattr = listxattr(p, 0, 0, 1)) < 0)
		xattr = 0;
	if (xattr > 0)
		return ('@');
	if (acll)
		return ('+');
	return (' ');
}

char			*ls_get_attr(char *p, int m)
{
	char	*res;

	if (!(res = ft_memset(malloc(SIZE(char, 12)), '-', SIZE(char, 11))))
		EXIT(__func__);
	res[11] = '\0';
	res[0] = ' ';
	IF(S_ISFIFO(m), res[0] = 'p');
	EF(S_ISCHR(m), res[0] = 'c');
	EF(S_ISDIR(m), res[0] = 'd');
	EF(S_ISBLK(m), res[0] = 'b');
	EF(S_ISREG(m), res[0] = '-');
	EF(S_ISLNK(m), res[0] = 'l');
	EF(S_ISSOCK(m), res[0] = 's');
	IF(m & S_IRUSR, res[1] = 'r');
	IF(m & S_IWUSR, res[2] = 'w');
	IF(m & S_IXUSR, res[3] = 'x');
	IF(m & S_IRGRP, res[4] = 'r');
	IF(m & S_IWGRP, res[5] = 'w');
	IF(m & S_IXGRP, res[6] = 'x');
	IF(m & S_IROTH, res[7] = 'r');
	IF(m & S_IWOTH, res[8] = 'w');
	IF(m & S_IXOTH, res[9] = 'x');
	res[10] = ls_xattr(p);
	ls_ts(res, m);
	return (res);
}
