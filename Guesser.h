#ifndef GUESSER_H
#define GUESSER_H

#include <string>

using std::string;

class Guesser
{
private:
  string m_secret;
  unsigned int m_remaining;
  bool m_locked;


public:
  unsigned int distance(string guess);

  Guesser(string secret);

  bool match(string guess);

  unsigned int remaining();
};
#endif
