  if ((outfile = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0664)) < 0) {
    exit(1);
  }