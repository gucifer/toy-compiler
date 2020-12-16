gcc -fno-asynchronous-unwind-tables -s -c -fPIE -o hello.o hello.c
objconv -fnasm hello.o   #this creates hello.asm