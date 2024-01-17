#include <algorithm>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <string>

constexpr bool doit()
{
  using namespace std;

  list<int> l{1, 2, 3};
  forward_list<int> fl{2, 3, 4};
  deque<int> dq(fl.begin(), fl.end());
  set<int> s;

  set_intersection(dq.begin(), dq.end(), l.begin(), l.end(),
                   inserter(s, s.end()));
  function<int()> f = [&] { return accumulate(s.begin(), s.end(), 0); };
  auto x = f();

  map<string, int> m{{"five", 5}, {"World ", 6}};
  auto p = make_shared<int>(m["five"]);

  istringstream iss("Hello ");
  cout << iss.str() << begin(m)->first << *p << ' ' << x << endl;

  return *p == x;
}

int main(int argc, char *argv[])
{
  static_assert(doit());
  return doit() ? 0 : 1;
}
