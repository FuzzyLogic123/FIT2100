#include "main.h"

int main(int argc, char *argv[])
{
    char *filename = get_file_name(argc, argv);
    read_from_file(filename);
    return 0;
}
