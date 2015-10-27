/*
** gnl.h for e in /home/carens_p/rendu/PSU_2014_philo/inc
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Thu Feb 26 14:43:13 2015 Paul Carensac
** Last update Sun Mar  8 02:24:55 2015 Cyril La Valle
*/

#ifndef GNL_H_
#define GNL_H_

#define READ_SIZE 64

typedef struct	s_strs
{
  char		*line;
  char		*line_tmp;
}		t_strs;

char	*get_next_line(int fd);

#endif
