enum msgtype {
              INSERT = 0,
             };

struct clip_entry{
      int len;
      char* entry;
};

struct clipboard{
      int cap, n;
      struct clip_entry* clips;
};
