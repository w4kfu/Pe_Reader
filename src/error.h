/**
** @file        error.h
** @brief       Header file for error.c
** @date        27/02/2011
** @author      Samuel CHEVET (w4kfu)
*/

#ifndef ERROR_H_
# define ERROR_H_

# include "pe_reader.h"

# define	OPEN_FAILED	1

# define	STAT_FAILED	2

# define	MMAP_FAILED	3

void	manage_error(int	error, s_peconf	*conf);

#endif /* !ERROR_H_ */
