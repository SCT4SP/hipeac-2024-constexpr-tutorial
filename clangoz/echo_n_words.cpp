#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Please enter the number of words to generate.\n";
    std::cout << "e.g. echo_n_words 200\n";
    return 0;
  }

  const int nwords = std::atoi(argv[1]);

  int i = 0, w = 0;

  std::random_device rdev;
  std::mt19937 gen(rdev());
  std::vector words = {"egg", "pear", "apple", "banana", "apricot", "turnip"};

  do
  {
    std::cout << words[w];
    if (++w == words.size())
    {
      w = 0;
      std::shuffle(words.begin(), words.end(), gen);
      std::cout << std::endl;
    }
    else
    {
      std::cout << ' ';
    }
  }
  while (++i < nwords);
  std::cout << std::endl;

  return 0;
}
