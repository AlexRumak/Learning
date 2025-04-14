#include <unistd.h>
#include <stdio.h>

int main(void)
{
  int page_size = getpagesize();
  printf("Page size: %d bytes\n", page_size);
  return 0;
}
