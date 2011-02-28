/**
** @file        print_info.c
** @brief       Function for printing information about the pe file
** @date        27/02/2011
** @author      Samuel CHEVET (w4kfu)
*/

# include "print_info.h"

/*
** @brief       Function for printing image dos header information
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
static void		print_image_dos_header(s_peconf *conf)
{
  int			i;

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

/*
** @brief       Function for printing data directory information
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
static void	print_directory(t_image_data_directory *idd)
{
  int		i;
  char		*name[16] = {"Export Table",
			     "Import Table",
			     "Resource Table",
			     "Exception Table",
			     "Certificate Table",
			     "Base Relocation Table",
			     "Debug Directory",
			     "Architecture Specific Data",
			     "Global Pointer Register",
			     "Thread Local Storage Table",
			     "Load Configuration Table",
			     "Bound Import Table",
			     "Import Address Table",
			     "Delay Load Import Descriptors",
			     "COM Runtime Descriptor",
			     "Reserved"};
  printf("\t\t\t\tType\t| Virtual Adress |\tSize\t | Present\n");
  printf("\t\t\t----------------|----------------|---------------|--------\n");
  for (i = 0; i < 16; i++)
    {
      printf("\t%31s | \t%08x | \t%08x | ", name[i], idd[i].VirtualAddress, idd[i].Size);
      printf("%s\n", (idd[i].Size) ? "True" : "False");
    }
}

/*
** @brief       Function for printing image optional header information
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
static void		print_image_optional_header(s_peconf	*conf)
{
  if (conf->hex)
    {
  	#define FORMAT "%x"
  	#include "image_optional_header.def"
  	#undef FORMAT
    }
  else
    {
  	#define FORMAT "%d"
  	#include "image_optional_header.def"
  	#undef FORMAT
    }
}

/*
** @brief       Function for printing image file header information
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
static void		print_image_file_header(s_peconf *conf)
{
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


/*
** @brief       Function printing section header information
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
static void		print_section_header(s_peconf *conf)
{
  int			i;

  for (i = 0; i < conf->file_header.ifh->NumberOfSections; i++)
    {
      printf("Name = %s\n", conf->section_header[i].ish->Name);
      printf("Virtual Address = %08X\n",
	     conf->section_header[i].ish->VirtualAddress);
      printf("Virtual Size = %08X\n",
	     conf->section_header[i].ish->u.VirtualSize);
      printf("Raw Data Offset = %08X\n",
	     conf->section_header[i].ish->PointerToRawData);
      printf("Raw Data Size = %08X\n",
	     conf->section_header[i].ish->SizeOfRawData);
      printf("Flag = %08X\n",
	     conf->section_header[i].ish->Characteristics);
    }
}

/*
** @brief       Function for printing all information about the pe file
** @param	conf	Structure for the configuration of pe_reader
** @return      Void.
*/
void			print_info(s_peconf	*conf)
{
  print_image_dos_header(conf);
  print_image_file_header(conf);
  if (conf->file_header.ifh->SizeOfOptionalHeader)
    print_image_optional_header(conf);
  print_section_header(conf);
}
