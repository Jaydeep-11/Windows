#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void edit_line(char* buffer, int current_line) {
    for (int i = 0; i < current_line; i++) {
        buffer = strchr(buffer, '\n') + 1;
    }

    char* line_end = strchr(buffer, '\n');
    char saved[1024] = { 0 };
    strcpy(saved, line_end);
    scanf("%s", buffer);
    strcpy(buffer + strlen(buffer), saved);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    HANDLE hFile = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    char buffer[1024] = { 0 };
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL)) {
        fprintf(stderr, "Error reading file\n");
        CloseHandle(hFile);
        return 1;
    }

    printf("Contents:\n%s\n", buffer);

    int current_line = 0;
    printf("Enter the line number to edit: ");
    scanf("%d", &current_line);

    edit_line(buffer, current_line);

    DWORD bytesWritten;
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    if (!WriteFile(hFile, buffer, strlen(buffer), &bytesWritten, NULL)) {
        fprintf(stderr, "Error writing to file\n");
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);
    return 0;
}
