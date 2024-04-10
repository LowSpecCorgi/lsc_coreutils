#include "stdio.h"
#include "Windows.h"
#include "stdlib.h"
#include <errhandlingapi.h>
#include <fileapi.h>
#include <handleapi.h>
#include <winbase.h>
#include <winnt.h>
#include "lsc_file_util.h"

/*
Windows file handling:

File = Unit of data in file system that a user can access and manage:
    - Must have a unique name.
    - One or more streams of bytes holding related data
        - Each stream associated with a file has:
            - Allocation size (reserved)
            - Actual size (what's used by caller)
            - Valid data length/VDL (N bytes initialized from allocation size of stream)

FilePointer = 64 bit value that is associated with the default stream of a file. This is an offset value specifying the next byte to be read or the location to recieve the next written byte
    - Each read+write advances it by n bytes read and written
*/

/*

File scope = Terminates at end of translation unit

Linkage = An identifier declared in different or same scope can be made to refer to the same object or function by linkage

Types of linkage:
    - External = In a **set** of translation units and libraries each declaration of an identifier with external linkage denotes same object or function
    - Internal = In **one** translation unit each declaration of an identifier with internal linkage denotes same object or function

Lifetime of an object = Portion of program execution during which storage is guaranteed to be reserved for it

Lifetimes:
    - Static:
        - Lifetime is entire execution. Value is initialised once.
        - Internal linkage in declaration of filescope identifier for object or function
*/
static void usage() {
    printf("\nlsc_cat [FILE_NAME]");
}

/*
C99 STD:
- argc: Non-negative int
- argv:
    - argc > 0: argv[0]-argv[argc-1] inclusive contains pointers to strings
        - argv[0][0] should represent the program name//null if not in program environment
        - argc > 1: argv[1]=argv[argc-1] represent program parameters
*/
int main(int argc, char** argv) {
    enum { MAX_ARGS = 1 };
    /*
    An integer constant expression with the value 0, or such an expression cast to type
void *, is called a null pointer constant. If a null pointer constant is converted to a
pointer type, the resulting pointer, called a null pointer, is guaranteed to compare unequal
to a pointer to any object or function.
    */
    if (!argc) {
        usage();
        return -1;
    } else if (argc != MAX_ARGS) {
        const char* file_name = argv[1];

        HANDLE file_handle = lsc_file_create(file_name);

        if (file_handle == INVALID_HANDLE_VALUE || !file_handle) {
            lsc_file_close_file(file_handle);

            printf("\nERROR when opening file. ERROR CODE (https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes): %lu", GetLastError());
            usage();
            return -1;
        }

        DWORD file_size;

        if (!lsc_file_get_size(file_handle, &file_size)) {
            lsc_file_close_file(file_handle);

            printf("\nERROR when polling file size. ERROR CODE (https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes): %lu", GetLastError());
            usage();
            return EXIT_FAILURE;
        }

        char buffer[file_size]= {};

        if (!lsc_file_read_full_to_buffer(file_handle, buffer, file_size)) {
            lsc_file_close_file(file_handle);

            printf("\nERROR when reading file. ERROR CODE (https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes): %lu", GetLastError());
            usage();
            return EXIT_FAILURE;
        }

        lsc_file_close_file(file_handle);

        printf("%s", buffer);
        

        return EXIT_SUCCESS;
        
    }

    usage();

    return EXIT_SUCCESS;
}