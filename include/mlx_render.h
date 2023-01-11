/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:11:07 by abossel           #+#    #+#             */
/*   Updated: 2023/01/08 16:16:46 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_RENDER_H
# define MLX_RENDER_H

# define SCR_WIDTH 1280
# define SCR_HEIGHT 720

typedef struct s_image
{
	void	*image;
	char	*addr;
	int		bpp;
	int		bpl;
	int		endian;
}	t_image;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_image		*screen;
	int			width;
	int			height;
	int			render;
	void		*data;
}	t_app;

int		argb(int a, int r, int g, int b);
int		rgb(int r, int g, int b);
int		get_r(int argb);
int		get_g(int argb);
int		get_b(int argb);

int		render(t_app *app);
int		mouse(int button, int x, int y, t_app *app);
int		keypress(int keycode, t_app *app);
int		destroy(t_app *app);

void	pixel_put(t_image *img, int x, int y, int colour);
int		gfx_init(t_app *app, t_image *screen);
void	gfx_free(t_app *app, t_image *screen);
int		gfx_main(t_app *app);

#endif
