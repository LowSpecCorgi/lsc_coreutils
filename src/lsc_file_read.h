#ifndef  LSC_FILE_UTIL_H
#define LSC_FILE_UTIL_H

#include "stdio.h"
#include "Windows.h"
#include "stdlib.h"
#include <errhandlingapi.h>
#include <fileapi.h>
#include <handleapi.h>
#include <winbase.h>
#include <winnt.h>
/*
We cann use the CreateFile function from WinAPI to open the file

Files are securable objects so we need to follow the access-control model

We will be using the security descriptor FILE_GENERIC_READ, giving us:
    - FILE_READ_ATTRIBUTES
    - FILE_READ_DATA
    - FILE_READ_EA
    - STANDARD_RIGHTS_READ
    - SYNCHRONISE

We also need to set a sharing mode. I will be using 0. Maybe (?) this will mitigate TOCTOU?

lpSecurityAttributes is NULL so file_handle cannot be inherited by any child processes.

dwCreationDisposition is OPEN_EXISTING meaning that the file will ONLY be opened if it exists.

dwFlagsAndAttributes is FILE_ATTRIBUTE_NORMAL

hTemplateFile is NULL as we don't have or need a template file with attributes to use

*/
HANDLE lsc_file_create(const char* file_name);

int lsc_file_get_size(HANDLE file_handle, DWORD *file_size_output);
int lsc_file_read_full_to_buffer(HANDLE file_handle, char* buffer_output, DWORD buffer_size);
void lsc_file_close_file(HANDLE file_handle);

#endif