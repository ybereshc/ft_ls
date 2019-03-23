/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybereshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:50:03 by ybereshc          #+#    #+#             */
/*   Updated: 2018/10/23 19:50:05 by ybereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROCESS_H
# define FT_PROCESS_H

typedef struct	s_process
{
	char	*name;
	char	**argv;
	int		argc;
}				t_process;

# define _INIT_PROGRAN_NAME_ g_process.name = argv[0]
# define _INIT_ARGV_ g_process.argv = argv
# define _INIT_ARGC_ g_process.argc = argc
# define _INIT_ _INIT_PROGRAN_NAME_, _INIT_ARGV_, _INIT_ARGC_

t_process g_process;

#endif
