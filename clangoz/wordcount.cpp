#include <iostream>
#include <numeric>
#include <execution>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <chrono>
#include <cctype> // std::isspace

// Based on CppCon 2016:
// Bryce Adelstein Lelbach "The C++17 Parallel Algorithms Library and Beyond"
// https://www.youtube.com/watch?v=Vck6kzWjY88

template <typename P>
constexpr std::size_t word_count(std::string_view s, P pol)
{
  if (s.empty())
    return 0;    // otherwise the "s.begin() + 1" leads to a segfault

  auto is_word_beginning = [](char curr, char next)
  {
    return std::isspace(curr) && !std::isspace(next);
  };

  return
    std::transform_reduce(
      pol,
      s.begin(),
      s.end() - 1,
      s.begin() + 1,
      !std::isspace(s.front()) ? 1U : 0U,
      std::plus{},
      is_word_beginning
    );
}

#define XSTR(S) STR(S)
#define STR(S)  #S

constexpr bool run_wordcount()
{
#ifdef WORDSFILEPATH
  std::string txt =
#include XSTR(WORDSFILEPATH)
;
#endif

#ifdef CONSTEXPR_TRACK_TIME
  __GetTimeStampStart(); // this begins after the lengthy string construction
#endif

  std::size_t wc = word_count(txt, std::execution::par);

#ifdef CONSTEXPR_TRACK_TIME
  __GetTimeStampEnd();
  __PrintTimeStamp();
#endif

  return wc == 10000;
}

int main(int argc, char *argv[])
{
#ifdef WORDSFILEPATH
#pragma message "words file is loading..."
  static_assert(run_wordcount());
#endif

  if (argc != 2) {
    return -1;
  }

  std::ifstream t(argv[1]);
  std::stringstream buffer;
  buffer << t.rdbuf();
  std::string txt = buffer.str();

  std::size_t wc{0};
  auto t1 = std::chrono::system_clock::now();
  wc = word_count(txt, std::execution::seq);
  auto t2 = std::chrono::system_clock::now();
  float ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
  std::cout << ms << " milliseconds.\n" << wc << " words." << std::endl;

  return 0;
}
