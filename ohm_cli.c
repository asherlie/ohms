#if 0
============================
|  o    h    m      s      |
| ohm helps manage strings |
============================
#endif
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(){
      int sock = socket(SOCK_STREAM, AF_UNIX, 0);
      
      struct sockaddr_un sun;
      sun.sun_family = AF_UNIX;
      strcpy(sun.sun_path, "booboo");

      if(connect(sock, (struct sockaddr*)&sun, sizeof(struct sockaddr_un)) == -1)
            perror("connect");
}
