#include "file_info.h"
#include <iostream>

file_info::file_info() : extension_(""), file_size_(){

}
file_info::file_info(std::string extension): extension_(std::move(extension)), file_size_(){}

file_info::file_info(std::string extension, off_t file_size): extension_(std::move(extension)), file_size_(file_size){}

std::string file_info::Extension(){
    return extension_;
}

bool file_info::operator==(file_info& other){
        return (other.extension_== extension_)&&(file_size_ == other.file_size_);

}

void file_info::print_size() {
    std::cout << file_size_ ;
};

off_t file_info::Size() {
  return file_size_;
};
