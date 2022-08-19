/* task1.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> 		/* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// this creates a struct and an array of unit codes
// it then opens a file with write privilliages or it will create the file if
// it does not exist. If this process fails then it will exit the program with a -1 error code
// It will then move the file offset to the beginging, and then write the value of the struct to the file
// It then closes the file

struct Record { // create a Record data structure
  int unitid;
  char unitcode[8];
};

char *unitcodes[] = {"FIT2100", "FIT3159", "FIT3142","FIT3165"}; // record a set of unit codes

int main(int argc, char *argv[])
{
  int i, outfile; // initliase variables
  struct Record eachrec; //initliase struct

  // opens a file called recordfile with flags that:
  // create the file if it does not exist
  // opens with write only permissions
  // will truncate the file length to 0
  if ((outfile = open("recordfile", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0) { // checks if the file open failed (returned a code of -1). The number represents the file permissions
    exit(1); // exit with error code
  }

  for (i = 3; i >= 0; i -=2) {
    eachrec.unitid = i; // defines the unit id of the current record to be the iterator
    strcpy(eachrec.unitcode, unitcodes[i]); // set the value of the current record unit code from the array already defined

    // with parameters
    // outfile: the file to write to
    // 
    lseek(outfile, (long) i * sizeof(struct Record), SEEK_SET); // repositions the file offset at the begining and then sets it to the correct number of bytes to store more data
    write(outfile, &eachrec, sizeof(struct Record)); // writes the value of eachrec

    if (i == 1) {
      i = 4;
    }
  }

  close(outfile);
  exit(0);
}