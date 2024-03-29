#include <stdio.h>

#define HEADERSIZE 44
//Credited to Professor Albert Lai
const unsigned char header[HEADERSIZE] = {
  0x52, 0x49, 0x46, 0x46, 0x24, 0x0, 0xff, 0x7f,
  0x57, 0x41, 0x56, 0x45, 0x66, 0x6d, 0x74, 0x20,
  0x10, 0x0, 0x0, 0x0, 0x3, 0x0, 0x1, 0x0,
  0x22, 0x56, 0x0, 0x0, 0x88, 0x58, 0x1, 0x0,
  0x4, 0x0, 0x20, 0x0, 0x64, 0x61, 0x74, 0x61,
  0x0, 0x0, 0xff, 0x7f
};

int main(void)
{
  float x;

  fwrite(header, sizeof(unsigned char), HEADERSIZE, stdout);
  while (scanf("%f", &x) == 1) {
    if (x > 1) {
      x = 1;
    } else if (x < -1) {
      x = -1;
    }
    fwrite(&x, sizeof(float), 1, stdout);
  }
  return 0;
}
