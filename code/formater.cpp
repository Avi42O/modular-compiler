#include "CodeFile.hpp"
#include <unordered_map>

void format_ascii(File &file);

std::unordered_map<std::string, void (*)(File&)> formaters = {
    {"ascii", format_ascii}
};

void CodeFile::format(std::string format){
  auto it = formaters.find(format);
  if (it != formaters.end())
    (it->second)(file);
}

void format_ascii(File &file){
  
}
