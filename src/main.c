#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>

void execute_blob(char *blob);
void *map_file_to_blob(char *filename);

int main(int argc, char **argv)
{
    char *blob_buffer = NULL;
    char *filename    = NULL;

    if (argc != 2)
    {
        printf("usage: a.out <filename>\r\n");
        return 1;
    }
    filename    = argv[1];
    blob_buffer = map_file_to_blob(filename);

    // execute out pic blob
    execute_blob(blob_buffer);

    return 0;
}

/**
 * @brief maps the contents of a file into an executable buffer.
 * @param filename: the filename containing data to map into a buffer.
 * @return a ptr to the executable buffer.
 */
void *map_file_to_blob(char *filename)
{
    char *blob_buffer = NULL;
    int   pagesize    = getpagesize();
    long  fsize       = 0;
    FILE *f           = NULL;
    long  bytes_read  = 0;

    // read the PIC blob
    f = fopen(filename, "rb");
    if (!f)
    {
        printf("unable to open file.\r\n");
        return NULL;
    }

    // calculate file size
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    printf("mapping %ld bytes of PIC blob into executable memory...\r\n",
           fsize);
    blob_buffer = mmap(0, fsize, PROT_WRITE | PROT_EXEC | PROT_READ,
                       MAP_PRIVATE | MAP_ANON, -1, 0);
    if (blob_buffer == MAP_FAILED)
    {
        printf("mmap failed: %d\r\n", errno);
        fclose(f);
        return NULL;
    }

    // read the file into the mmap'd memory
    bytes_read = fread(blob_buffer, fsize, 1, f);
    if (bytes_read == fsize)
    {
        printf("Unable to read entire file: %d\r\n", errno);
        fclose(f);
        return NULL;
    }
    fclose(f);
    return blob_buffer;
}

/**
 * @brief executes a PIC blob, makes assumptions about the blob entry point's
 * signature
 * (int <name>(int);)
 * @param blob: the blob to execute.
 */
void execute_blob(char *blob)
{
    int ret = 0;
    int (*blob_fptr)(int);

    blob_fptr = (int (*)(int))blob;

    printf("executing PIC blob...\r\n");
    ret = blob_fptr(0xdeadbeef);
    printf("return was: %d\r\n", ret);
}
