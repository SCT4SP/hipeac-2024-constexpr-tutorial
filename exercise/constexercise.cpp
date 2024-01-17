#include <cstdlib>
#include <cassert>
#include <memory>

// clang++ -std=c++26 -Winvalid-constexpr -fsanitize=address -Wpedantic constexercise.cpp

// g++ -std=c++26 -fsanitize=address -static-libasan constexercise.cpp

int* incr_int(void* vp)
{
  int *p = reinterpret_cast<int*>(vp);
  if (p)
    (*p)++;
  return p;
}

bool doit()
{
  void *vp = malloc(sizeof(int)*1024);
  int *p = reinterpret_cast<int*>(vp);
  *p = 42;
  p = incr_int(p);
  bool b = (*p==43);
  free(vp);
  return b;
}

int main()
{
  assert(doit());
  // static_assert(doit());
}
