#ifndef CODEFILE_H
#define CODEFILE_H

#include "File.hpp"

class CodeFile{
  File file;

  public:

    void open(std::string file_name, std::string extention=""){
      file.file_name = file_name + extention;
      file.clear();
      file.commit();
    }

    // the format of the source file
    void format(std::string format);

    void preProcess();

    void parse();
    
    void translate();
}



#endif //CODEFILE_H