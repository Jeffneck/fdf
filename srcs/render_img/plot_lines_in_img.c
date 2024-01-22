/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_lines_in_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:19:01 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 15:21:35 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	put_pixel(t_imgstruct *p_img, int col, int line, int color)
{
	int	offset;

	offset = (p_img->line_len * line) + (p_img->bits_per_pixel * col / 8);
	if (col >= 0 && col < WIDTH && line >= 0 && line < HEIGHT)
		*((int *)(p_img->p_img_pixels + offset)) = color;
}

void	plot_low_slope(t_imgstruct *p_img, t_plot plt,
	t_map_elem p0, t_map_elem p1)
{
	int	nb_steps;
	int	gradient;

	nb_steps = 0;
	while (p0.proj_x != p1.proj_x)
	{
		if (p0.color != p1.color)
			gradient = process_color(nb_steps, plt.x_diff, p0.color, p1.color);
		else
			gradient = p0.color;
		if (p0.proj_x >= 0 && p0.proj_x < WIDTH
			&& p0.proj_y >= 0 && p0.proj_y < HEIGHT)
			put_pixel(p_img, p0.proj_x, p0.proj_y, gradient);
		p0.proj_x += plt.x_step;
		if (plt.decision <= 0)
			plt.decision += 2 * plt.y_diff;
		else
		{
			p0.proj_y += plt.y_step;
			plt.decision += 2 * (plt.y_diff - plt.x_diff);
		}
		nb_steps++;
	}
}

void	plot_high_slope(t_imgstruct *p_img, t_plot plt,
	t_map_elem p0, t_map_elem p1)
{
	int	nb_steps;
	int	gradient;

	nb_steps = 0;
	while (p0.proj_y != p1.proj_y)
	{
		if (p0.color != p1.color)
			gradient = process_color(nb_steps, plt.y_diff, p0.color, p1.color);
		else
			gradient = p0.color;
		if (p0.proj_x >= 0 && p0.proj_x < WIDTH
			&& p0.proj_y >= 0 && p0.proj_y < HEIGHT)
			put_pixel(p_img, p0.proj_x, p0.proj_y, gradient);
		p0.proj_y += plt.y_step;
		if (plt.decision <= 0)
			plt.decision += 2 * plt.x_diff;
		else
		{
			p0.proj_x += plt.x_step;
			plt.decision += 2 * (plt.x_diff - plt.y_diff);
		}
		nb_steps++;
	}
}

void	init_ploting_utils(t_plot *p_plt, t_map_elem p0, t_map_elem p1)
{
	p_plt->x_diff = abs(p1.proj_x - p0.proj_x);
	p_plt->y_diff = abs(p1.proj_y - p0.proj_y);
	if (p1.proj_x > p0.proj_x)
		p_plt->x_step = 1;
	else
		p_plt->x_step = -1;
	if (p1.proj_y > p0.proj_y)
		p_plt->y_step = 1;
	else
		p_plt->y_step = -1;
}

void	plot_line(t_imgstruct *p_img, t_map_elem p0, t_map_elem p1)
{
	t_plot	plt;

	init_ploting_utils(&plt, p0, p1);
	if (plt.x_diff >= plt.y_diff)
	{
		plt.decision = 2 * plt.y_diff - plt.x_diff;
		plot_low_slope(p_img, plt, p0, p1);
	}
	else
	{
		plt.decision = 2 * plt.x_diff - plt.y_diff;
		plot_high_slope(p_img, plt, p0, p1);
	}
}
