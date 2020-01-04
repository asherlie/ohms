#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/un.h>

int handle_conn(int sock){
      listen(sock, 0);
      int peer;
      while(1){
            int peer = accept(sock, NULL, NULL);
            if(peer == -1)continue;
            printf("gotty\n");
      }
}

int main(){
      int sock = socket(SOCK_STREAM, AF_UNIX, 0);
      struct sockaddr_un sun;

      sun.sun_family = AF_UNIX;
      strcpy(sun.sun_path, "booboo");

      bind(sock, (struct sockaddr*)&sun, sizeof(struct sockaddr_un));

      handle_conn(sock);
}
