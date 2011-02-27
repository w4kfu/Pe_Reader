/**
** @file        print_info.c
** @brief       Function for printing information about the pe file
** @date        27/02/2011
** @author      Samuel CHEVET (w4kfu)
*/

# include "print_info.h"

static void		print_image_dos_header(s_peconf *conf)
{
  int			i;
  t_image_dos_header	*idh = NULL;

  idh = (t_image_dos_header*)conf->p;
  if (conf->hex)
    {
	#define FORMAT "%x"
	#include "image_dos_header.def"
	#undef FORMAT
    }
  else
    {
	#define FORMAT "%d"
	#include "image_dos_header.def"
	#undef FORMAT
    }
}

static void		print_image_file_header(s_peconf *conf)
{
  t_image_dos_header	*idh = NULL;
  t_image_file_header	*ifh = NULL;

  idh = (t_image_dos_header*)conf->p;
  ifh = (t_image_file_header*)(conf->p + idh->e_lfanew + 4);
  if (conf->hex)
    {
	#define FORMAT "%x"
	#include "image_file_header.def"
	#undef FORMAT
    }
  else
    {
	#define FORMAT "%d"
	#include "image_file_header.def"
	#undef FORMAT
    }
}

void		print_info(s_peconf	*conf)
{
  printf("SIZE = %d\n", sizeof (t_image_dos_header));
  print_image_dos_header(conf);
  print_image_file_header(conf);
}
