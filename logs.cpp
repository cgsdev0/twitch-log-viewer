#include <iostream>
#include <cassert>
#include <iomanip>
#include <ranges>
#include <string_view>

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
unsigned hash_str(const char* s)
{
   unsigned h = FIRSTH;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h; // or return h % C;
}

int main() {
  std::string str;
  using std::operator""sv;
  constexpr auto delim{";"sv};
  constexpr auto word_delim{" "sv};
  while(std::getline(std::cin, str)) {
    /* std::cerr << str << std::endl; */
    std::string name;
    std::string color;
    std::string msg;
    int privmsg = -1;
    bool tags = false;
    for (const auto word : std::views::split(str, word_delim)) {
      auto wordsv = std::string_view(word);
      if(!tags) {
        tags = true;
        for (const auto section : std::views::split(wordsv, delim)) {
          auto sectionsv = std::string_view(section);
          if (sectionsv.starts_with("display-name"sv)) {
            sectionsv.remove_prefix(13);
            name = sectionsv;
          }
          else if (sectionsv.starts_with("color"sv)) {
            sectionsv.remove_prefix(6);
            color = sectionsv;
          }
        }
        continue;
      }
      if (wordsv.compare("PRIVMSG"sv) == 0 || privmsg == 0) {
        privmsg += 1;
        continue;
      }
      if(privmsg > 0) {
        if (msg.size()) {
          msg += " ";
        }
        else {
          wordsv.remove_prefix(1);
        }
        if (wordsv.size()) {
          msg += wordsv;
        }
      }
    }
    if (privmsg > 0) {
      unsigned int r, g, b;
      if (color.size()) {
        assert(sscanf(color.c_str(), "#%2x%2x%2x", &r, &g, &b) == 3);
      }
      else {
        auto colorhash = hash_str(name.c_str());
        r = colorhash & 0xff;
        g = (colorhash >> 8) & 0xff;
        b = (colorhash >> 16) & 0xff;
      }
      std::cout << "\x1b[38;2;" << r << ";"<< g << ";" << b << "m";
      std::cout << name << "\033[0m" << ": " << msg << std::endl;
    }
  }
}
