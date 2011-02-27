/**
** @file        error.c
** @brief       File for managing different types of error
** @date        27/02/2011
** @author      Samuel CHEVET (w4kfu)
*/

# include "error.h"

/*
** @brief       Function for closing and free correctly the structure conf
** @param	error	Type of error
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
void	manage_error(int	error, s_peconf	*conf)
{
  if (error == OPEN_FAILED)
    perror("open ()");
  else if (error == STAT_FAILED)
    perror("stat()");
  else if (error == MMAP_FAILED)
    perror("mmap()");
  close(conf->fd);
  free(conf->sb);
  exit(EXIT_FAILURE);
}
