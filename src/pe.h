/**
** @file        pe.h
** @brief       All necessary declarations for manipulating PE file
** @date        27/02/2011
** @author      Samuel CHEVET (w4kfu)
*/


#ifndef PE_H_
# define PE_H_

typedef unsigned char		t_uint8;
typedef unsigned short		t_uint16;
typedef unsigned int		t_uint32;

# define IMAGE_DOS_SIGNATURE			0x5A4D
# define IMAGE_NT_SIGNATURE			0x00004550
# define IMAGE_NUMBEROF_DIRECTORY_ENTRIES	16


# define image_dos_header_length	sizeof(t_image_dos_header)
# define image_file_header_length	sizeof(t_image_file_header)
# define image_data_directory_length	sizeof(t_image_data_directory)
# define image_optional_header_length	sizeof(t_image_optional_header)
# define image_section_header_length	sizeof(t_image_section_header)
# define image_import_by_name_length	sizeof(t_image_import_by_name)
# define image_thunk_data_length	sizeof(t_image_thunk_data)
# define image_import_descriptor_length	sizeof(t_image_descriptor)

typedef struct
{
  t_uint16	e_magic;
  t_uint16	e_cblp;
  t_uint16	e_cp;
  t_uint16	e_crlc;
  t_uint16	e_cparhdr;
  t_uint16	e_minalloc;
  t_uint16	e_maxalloc;
  t_uint16	e_ss;
  t_uint16	e_sp;
  t_uint16	e_csum;
  t_uint16	e_ip;
  t_uint16	e_cs;
  t_uint16	e_lfarlc;
  t_uint16	e_ovno;
  t_uint16	e_res[4];
  t_uint16	e_oemid;
  t_uint16	e_oeminfo;
  t_uint16	e_res2[10];
  t_uint32	e_lfanew;
}		t_image_dos_header;


typedef struct
{
  t_uint16	Machine;
  t_uint16	NumberOfSections;
  t_uint32	TimeDateStamp;
  t_uint32	PointerToSymbolTable;
  t_uint32	NumberOfSymbols;
  t_uint16	SizeOfOptionalHeader;
  t_uint16	Characteristics;
}		t_image_file_header;

typedef struct
{
  t_uint32	VirtualAddress;
  t_uint32	Size;
}		t_image_data_directory;

typedef struct
{
  t_uint16			Magic;
  t_uint8			MajorLinkerVersion;
  t_uint8			MinorLinkerVersion;
  t_uint32			SizeOfCode;
  t_uint32			SizeOfInitializedData;
  t_uint32			SizeOfUninitializedData;
  t_uint32			AddressOfEntryPoint;
  t_uint32			BaseOfCode;
  t_uint32			BaseOfData;
  t_uint32			ImageBase;
  t_uint32			SectionAlignment;
  t_uint32			FileAlignment;
  t_uint16			MajorOperatingSystemVersion;
  t_uint16			MinorOperatingSystemVersion;
  t_uint16			MajorImageVersion;
  t_uint16			MinorImageVersion;
  t_uint16			MajorSubsystemVersion;
  t_uint16			MinorSubsystemVersion;
  t_uint32			Win32VersionValue;
  t_uint32			SizeOfImage;
  t_uint32			SizeOfHeaders;
  t_uint32			CheckSum;
  t_uint16			Subsystem;
  t_uint16			DllCharacteristics;
  t_uint32			SizeOfStackReserve;
  t_uint32			SizeOfStackCommit;
  t_uint32			SizeOfHeapReserve;
  t_uint32			SizeOfHeapCommit;
  t_uint32			LoaderFlags;
  t_uint32			NumberOfRvaAndSizes;
  t_image_data_directory	DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
}				t_image_optional_header;

typedef struct
{
  t_uint8	Name[8];
  union
  {
    t_uint32	PhysicalAddress;
    t_uint32	VirtualSize;
  } u;
  t_uint32	VirtualAddress;
  t_uint32	SizeOfRawData;
  t_uint32	PointerToRawData;
  t_uint32	PointerToRelocations;
  t_uint32	PointerToLinenumbers;
  t_uint16	NumberOfRelocations;
  t_uint16	NumberOfLinenumbers;
  t_uint32	Characteristics;
}		t_image_section_header;

typedef struct
{
  t_uint16	Hint;
  t_uint8	Name[1];
}		t_image_import_by_name;

typedef struct IMAGE_THUNK_DATA
{
  union
  {
    t_uint8			*ForwarderString;
    t_uint32			*Function;
    t_uint32			Ordinal;
    t_image_import_by_name	*AddressOfData;
  } u;
}				t_image_thunk_data;


typedef struct
{
  union
  {
    t_uint32		Characteristics;
    t_image_thunk_data	*OriginalFirstThunk;
  } u;
  t_uint32		TimeDateStamp;
  t_uint32		ForwarderChain;
  t_uint32		Name;
  t_image_thunk_data	*FirstThunk;
}			t_image_import_descriptor;

#endif /* !PE_H_ */
