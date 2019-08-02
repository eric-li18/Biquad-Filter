#include <stdio.h>

#define HEADERSIZE 44

int main(void)
{
  float x;
  unsigned char header[HEADERSIZE];

  if (fread(header, sizeof(unsigned char), HEADERSIZE, stdin)
      != sizeof(unsigned char) * HEADERSIZE) {
    fprintf(stderr, "unwav: Problem when reading WAV header.\n");
    return 1;
  }
  if (header[20] != 3 || header[22] != 1) {
    fprintf(stderr, "unwav: Sorry, I only understand mono audio with float data.\n");
    return 1;
  }
  while (fread(&x, sizeof(float), 1, stdin) == 1) {
    printf("%g\n", x);
  }
  return 0;
}
