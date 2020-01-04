#if 0
============================
|  o    h    m      s      |
| ohm helps manage strings |
============================
#endif
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>

_Bool copy_text(int sock, char* str, int len){
      /* mktemp */
      struct sockaddr_un sun;
      sun.sun_family = AF_UNIX;
      strcpy(sun.sun_path, "booboo");

      if(connect(sock, (struct sockaddr*)&sun, sizeof(struct sockaddr_un)) == -1){
            perror("connect");
            return 0;
      }
      send(sock, &len, sizeof(int), 0);
      send(sock, str, sizeof(char)*len, 0);

      return 1;
}

int main(int a, char** b){
      int sock = socket(SOCK_STREAM, AF_UNIX, 0);
      copy_text(sock, b[1], strlen(b[1]));
}
