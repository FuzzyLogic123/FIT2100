  if ((outfile = open("recordfile", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0) { // checks if the file open failed (returned a code of -1). The number represents the file permissions
    exit(1); // exit with error code
  }