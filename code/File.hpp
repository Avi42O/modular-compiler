#ifndef FILE_H
#define FILE_H

#include <string>
#include <cstdio>
#include <functional>

#define _CRT_SECURE_NO_WARNINGS

class File{

  std::FILE *data;
  std::FILE *buffer;

  public:

    std::string file_name;

    File() : file_name() {
      buffer = std::tmpfile();
    }
    File(std::string str) : file_name(str) {
      buffer = std::tmpfile();
    }

    ~File(){
      finalize();
    }

    void commit(){
      if (buffer!=nullptr){
        if (data!=nullptr){
          std::fclose(data);
        }
        data = buffer;
        std::fflush(data);
        std::fseek(data, 0, SEEK_SET);
        buffer = std::tmpfile();
      }
    }

    void finalize(){
      if (data!=nullptr){
        if (buffer!=nullptr){
          std::fclose(buffer);
        }
        buffer = std::fopen(file_name.c_str(), "wb");
        if (buffer!=nullptr){
          std::fseek(data, 0, SEEK_SET);
          for (char chr=fgetc(data); chr!=EOF; chr=fgetc(data)){
            std::fputc(chr, buffer);
          }
        }
      }
    }

    bool isValid(){
      return buffer != nullptr;
    }

    void seek(long offset, int origin){
      std::fseek(data, offset, origin);
    }

    std::string read(std::function<bool(char)> stop_con){
      std::string temp;
      char chr;
      while ((chr=std::fgetc(data))!=EOF && !stop_con(chr)){
        temp += chr;
      }
      return temp;
    }

    std::string read(int size){
      return read([size](char) mutable -> bool{return size-- == 0;});
    }

    std::string read(std::string until){
      std::string curr="";
      curr.reserve(until.size());
      std::size_t start=0;
      return read([&](char chr) -> bool {
        if (curr.size() < until.size()){
          curr += chr;
        } else {
          curr[start] = chr;
          start = (start+1) % curr.size();
        }

        if (curr.size() == until.size()){
          return until == curr.substr(start) + curr.substr(0, start);
        }
        return false;
      });
    }

    char read(){
      return std::fgetc(data);
    }

    void write(char chr){
      std::fputc(chr, buffer);
    }

    void write(std::string str){
      for (std::size_t i=0; i<str.size(); i++){
        std::fputc(str[i], buffer);
      }
    }

    void del(){
      fclose(buffer);
      buffer = std::tmpfile();
    }

    void rewind(long offset){
      std::fseek(buffer, offset, SEEK_CUR);
    }


};

#endif //FILE_H