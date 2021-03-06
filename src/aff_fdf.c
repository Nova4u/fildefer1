/*
** aff_fdf.c for fdf
** 
** Made by marc brout
** Login   <brout_m@epitech.net>
** 
** Started on  Thu Nov 19 09:49:45 2015 marc brout
** Last update Sun Nov 22 07:08:57 2015 marc brout
*/

#include "../include/fdf.h"

void			map_trax(t_fdftab *fdf,
				 t_bunny_position *tab,
				 t_bunny_pixelarray *pix,
				 t_color *color)
{
  t_bunny_position	pos[2];
  int			i;
  int			j;
  int			k;

  k = 0;
  i = 0;
  while (i++ < (fdf->h))
    {
      j = 0;
      while (j++ < (fdf->w - 1) && k < (fdf->h * fdf->w - 1))
	{
	  pos[0].x = tab[k].x;
	  pos[1].x = tab[k + 1].x;
	  pos[0].y = tab[k].y;
	  pos[1].y = tab[k + 1].y;
	  tekline(pix, &pos[0], color);
	  k += 1;
	}
      k += 1;
    }
}

void			map_tray(t_fdftab *fdf,
				 t_bunny_position *tab,
				 t_bunny_pixelarray *pix,
				 t_color *color)
{
  t_bunny_position	pos[2];
  int			i;
  int			j;
  int			k;

  k = 0;
  i = 0;
  while (i++ < (fdf->h))
    {
      j = 0;
      while (j++ <= (fdf->w) && k < (fdf->h * fdf->w - fdf->w))
	{
	  pos[0].x = tab[k].x;
	  pos[1].x = tab[k + fdf->w].x;
	  pos[0].y = tab[k].y;
	  pos[1].y = tab[k + fdf->w].y;
	  tekline(pix, &pos[0], color);
	  k += 1;
	}
    }
}

void		map_calc(t_fdftab *fdf, t_bunny_position *tab)
{
  int		i;
  int		j;
  int		k;
  int		rot;
  int		basex;
  int		basey;

  i = 0;
  k = 0;
  basex = fdf->conf->offsetx;
  basey = fdf->conf->offsety;
  while (i++ < fdf->h)
    {
      j = 0;
      while (j < fdf->w)
	{
	  rot = (fdf->conf->pasx < 50) ? k : k * 8;
	  tab[k].x += fdf->conf->pasx * j++ + basex + rot;
	  tab[k].y = (tab[k].y * fdf->conf->pasy) + basey;
	  k++;
	}
      basex -= fdf->conf->pasx;
      basey += (fdf->conf->pasx * 2) / 5;
    }
}

void			my_fdf_back(t_bunny_pixelarray *pix,
				    t_color *color)
{
  t_bunny_position	pos;

  pos.y = 0;
  while (pos.y < HEIGHT)
    {
      pos.x = 0;
      while (pos.x < WIDTH)
	{
	  tekpixel(pix, &pos, color);
	  pos.x += 1;
	}
      pos.y += 1;
    }
}

void			my_fdf_aff(t_fdftab *fdf)
{
  t_bunny_key		keyesc;

  fdf->back[0].full = COLOR_BACK;
  fdf->back[1].full = COLOR_BACK;
  keyesc = &my_key;
  fdf->pix = bunny_new_pixelarray(WIDTH, HEIGHT);
  fdf->win = bunny_start(WIDTH, HEIGHT, 0, "fil de fer 1");
  map_calc(fdf, fdf->tab);
  map_calc(fdf, fdf->tabo);
  map_calc(fdf, fdf->tabw);
  bunny_set_key_response(keyesc);
  bunny_set_loop_main_function(main_loop);
  bunny_loop(fdf->win, 24, fdf);
  bunny_delete_clipable(&fdf->pix->clipable);
  bunny_stop(fdf->win);
}
