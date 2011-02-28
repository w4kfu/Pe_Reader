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

/*
** @brief       Function for converting Rva value to offset
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
t_uint32	rvatooffset(t_uint32 rva, s_peconf	*conf)
{
  int		i;

  for (i = 0; i < conf->file_header.ifh->NumberOfSections; i++)
    if (conf->section_header[i].ish->VirtualAddress <= rva)
      if ((conf->section_header[i].ish->VirtualAddress +
	   conf->section_header[i].ish->u.VirtualSize) > rva)
	{
	  rva -= conf->section_header[i].ish->VirtualAddress;
	  rva += conf->section_header[i].ish->PointerToRawData;
	  return (rva);
	}
  return (0);
}

/*
** @brief       Function for computing how much dll use the pe file
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
int				count_nb_dll(s_peconf	*conf)
{
  u_image_import_descriptor	iid;
  int				i = 0;
  char				*p = NULL;

  p = conf->p + rvatooffset(conf->optional_header.ioh->DataDirectory[1].VirtualAddress,
			    conf);
  do
    {
      i++;
      iid.p = p;
      p += image_import_descriptor_length;
    } while ((iid.iid->u.OriginalFirstThunk != 0) ||
	     (iid.iid->TimeDateStamp != 0) ||
	     (iid.iid->ForwarderChain != 0) ||
	      (iid.iid->FirstThunk != 0));
  return (i - 1);
}

int			count_nb_api(s_peconf	*conf)
{
  int			i;
  int			j;
  u_image_thunk_data	itd;
  int			offset;
  char			*p = NULL;

  for (i = 0; i < conf->nb_dll; i++)
    {
      j = 0;
      if (conf->import_descriptor[i].iid->FirstThunk != 0)
	offset = rvatooffset((int)conf->import_descriptor[i].iid->FirstThunk,
			     conf);
      else
	offset = rvatooffset((int)conf->import_descriptor[i].iid->u.OriginalFirstThunk,
			     conf);
      p = conf->p + offset;
      do
	{
	  j++;
	  itd.p = p;
	  p += image_thunk_data_length;
	  if (itd.itd->u.AddressOfData != 0)
	    printf("Nom api = %s\n", conf->p + rvatooffset((int)itd.itd->u.ForwarderString, conf) + 2);
	} while ((itd.itd->u.AddressOfData != 0) ||
		 (itd.itd->u.ForwarderString != 0) ||
		 (itd.itd->u.Function != 0) ||
		 (itd.itd->u.Ordinal != 0));
    }
  return (0);
}

/*
** @brief       Function for filling all the ptr to the good offset
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
static void	fill_info(s_peconf	*conf)
{
  int		i;

  conf->dos_header.p = conf->p;
  conf->file_header.p = conf->p + conf->dos_header.idh->e_lfanew + 4;
  if (conf->file_header.ifh->SizeOfOptionalHeader)
    conf->optional_header.p = conf->file_header.p + image_file_header_length;
  if (!(conf->section_header = malloc(sizeof(u_image_section_header) *
				      conf->file_header.ifh->NumberOfSections)))
    {
      perror("malloc()");
      exit(EXIT_FAILURE);
    }
  for (i = 0; i < conf->file_header.ifh->NumberOfSections; i++)
    {
      conf->section_header[i].p = conf->optional_header.p +
	image_optional_header_length + i * image_section_header_length;
    }
  conf->nb_dll = count_nb_dll(conf);
  if (!(conf->import_descriptor = malloc(sizeof(u_image_import_descriptor) *
				      conf->nb_dll)))
    {
      perror("malloc()");
      exit(EXIT_FAILURE);
    }
  if (!(conf->name_dll = malloc(sizeof(char*))))
    {
      perror("malloc()");
      exit(EXIT_FAILURE);
    }
  for (i = 0; i < conf->nb_dll; i++)
    {
      conf->import_descriptor[i].p = conf->p +
	rvatooffset(conf->optional_header.ioh->DataDirectory[1].VirtualAddress,
		    conf) + i * image_import_descriptor_length;
      conf->name_dll[i] =
	strdup(conf->p + rvatooffset(conf->import_descriptor[i].iid->Name, conf));
      printf("Name = %s\n", conf->name_dll[i]);
    }
  count_nb_api(conf);
}

int		main(int argc, char **argv)
{
  s_peconf	conf;

  check_opt (argc, argv, &conf);
  fill_info(&conf);
  print_info(&conf);
  free(conf.sb);
  close(conf.fd);
  return (0);
}
