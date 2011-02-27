/**
** @file        main.c
** @brief       Main file for Pe Reader
** @date        27/02/2011
** @author      Samuel CHEVET (w4kfu)
*/

#include "pe_reader.h"

/*
** @brief       Function for filling the structure peconf
** @param	argv	Ptr to the list of arguments
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
void		check_binary(char **argv, s_peconf *conf)
{
  if ((conf->sb = malloc(sizeof (struct stat))) == NULL)
    {
      perror("malloc()");
      exit(EXIT_FAILURE);
    }
  if ((conf->fd = open (argv[1], O_RDONLY)) == -1)
    manage_error (OPEN_FAILED, conf);
  if (stat (argv[1], conf->sb) == -1)
    manage_error (STAT_FAILED, conf);
  if ((conf->p = mmap (NULL, conf->sb->st_size, PROT_READ, MAP_PRIVATE,
		       conf->fd, 0)) == MAP_FAILED)
    manage_error (MMAP_FAILED, conf);
}

/*
** @brief       Function for checking if the user gived a pe_file
** @param       argc	Number of arguments passed to main
** @param	argv	Ptr to the list of arguments
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
static void	check_opt(int argc, char **argv, s_peconf *conf)
{
  if (argc != 2)
    {
      printf ("Usage : %s <pe_file>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  check_binary(argv, conf);
}


int		main(int argc, char **argv)
{
  s_peconf	conf;

  check_opt (argc, argv, &conf);
  return (0);
}
