#include "lsc_file_util.h"

HANDLE lsc_file_create(const char* file_name) {
    return CreateFile(
            file_name,
            GENERIC_READ,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
}

int lsc_file_get_size(HANDLE file_handle, DWORD *file_size_output) {
    return GetFileSizeEx(file_handle, file_size_output);
}

int lsc_file_read_full_to_buffer(HANDLE file_handle, char* buffer_output, DWORD buffer_size) {
    return ReadFile(file_handle, &buffer_output, buffer_size, 0, NULL);
}

void lsc_file_close_file(HANDLE file_handle) {
    CloseHandle(file_handle);
}