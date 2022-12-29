/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:46:16 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/29 17:33:41 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# include "vector.h"
# include "libft.h"

typedef struct s_env
{

}	t_env;

//utils
int		put_err(char *str, char *arg);
void	exit_err(char *str, char *arg);

//params
void	params(char *file, t_env *env);



#endif
