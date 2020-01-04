#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/un.h>

#include "shared.h"

struct clip_entry* insert_text(struct clipboard* cb, char* str, int len){
      (void)cb;
      (void)str;
      (void)len;
      return NULL;
}

int handle_conn(int sock){
      listen(sock, 0);
      int peer, len;
      while(1){
            int peer = accept(sock, NULL, NULL);
            if(peer == -1)continue;

            read(peer, &len, sizeof(int));
            char* str = malloc(sizeof(char)*len);
            read(peer, str, sizeof(char)*len);

            printf("\"%s\"\n", str);
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
