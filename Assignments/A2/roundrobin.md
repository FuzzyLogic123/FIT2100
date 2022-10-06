### PLAN: do round robin first - basically from scratch:
    ## once i figure out what im doing then i can try and implement that method into first come first serve.

# create an array of active processes
    iterate over these processes and do the required things
    if there is a test completed, set it to state quit in the loop
    then remove it and write to the file each with its information

    to remove a task shift all elements after it back one and realloc
    shrink the array