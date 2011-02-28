/**
** @file        pe_reader.h
** @brief       Declarations for Pe Reader
** @date        27/02/2011
** @author      Samuel CHEVET (w4kfu)
*/

#ifndef PE_READER_H_
# define PE_READER_H_

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <string.h>

typedef struct peconf s_peconf;

# include "pe.h"
# include "error.h"
# include "print_info.h"

typedef union
{
  t_image_dos_header		*idh;
  char				*p;
}				u_image_dos_header;

typedef union
{
  t_image_optional_header	*ioh;
  char				*p;
}				u_image_optional_header;

typedef union
{
  t_image_file_header		*ifh;
  char				*p;
}				u_image_file_header;

typedef union
{
  t_image_section_header	*ish;
  char				*p;
}				u_image_section_header;

typedef union
{
  t_image_import_descriptor	*iid;
  char				*p;
}				u_image_import_descriptor;

typedef union
{
  t_image_thunk_data		*itd;
  char				*p;
}				u_image_thunk_data;

struct				peconf
{
  char				*name;
  int				fd;
  struct stat			*sb;
  char				*p;
  u_image_dos_header		dos_header;
  u_image_file_header		file_header;
  u_image_optional_header	optional_header;
  u_image_section_header	*section_header;
  u_image_import_descriptor	*import_descriptor;
  char				**name_dll;
  int				nb_dll;
  int				hex;
};

#endif /* !PE_READER_H_ */
