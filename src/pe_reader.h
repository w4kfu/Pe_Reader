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

typedef struct peconf s_peconf;

# include "pe.h"
# include "error.h"
# include "print_info.h"

struct		peconf
{
  char		*name;
  int		fd;
  struct stat	*sb;
  char		*p;
  int		hex;
};

#endif /* !PE_READER_H_ */
