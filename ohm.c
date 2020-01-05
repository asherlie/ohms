#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/un.h>

#include "shared.h"

void init_clipboard(struct clipboard* cb){
      cb->cap = 100;
      cb->n = 0;
      cb->clips = malloc(sizeof(struct clip_entry)*cb->cap);
}

struct clip_entry* insert_text(struct clipboard* cb, char* str, int len){
      if(cb->n == cb->cap){
            cb->cap *= 2;
            struct clip_entry* tmp_c = malloc(sizeof(struct clip_entry)*cb->cap);
            memcpy(tmp_c, cb->clips, sizeof(struct clip_entry)*cb->n);
            free(cb->clips);
            cb->clips = tmp_c;
      }
      cb->clips[cb->n].entry = str;
      cb->clips[cb->n].len = len;
      return &cb->clips[cb->n++];
}

int handle_conn(int sock, struct clipboard* cb){
      listen(sock, 0);
      int peer, len;
      while(1){
            int peer = accept(sock, NULL, NULL);
            if(peer == -1)continue;

            read(peer, &len, sizeof(int));
            char* str = malloc(sizeof(char)*len);
            read(peer, str, sizeof(char)*len);

            insert_text(cb, str, len);

            printf("\"%s\"\n", str);
      }
}

int main(){
      int sock = socket(SOCK_STREAM, AF_UNIX, 0);
      struct sockaddr_un sun;

      sun.sun_family = AF_UNIX;
      strcpy(sun.sun_path, "booboo");

      bind(sock, (struct sockaddr*)&sun, sizeof(struct sockaddr_un));

      struct clipboard cb;
      init_clipboard(&cb);

      handle_conn(sock, &cb);
}
