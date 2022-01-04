#ifndef BOOST_OPTIONS_DEMO_FILE_INFO_H
#define BOOST_OPTIONS_DEMO_FILE_INFO_H

#include <string>

struct file_info{

public:

    file_info();
    file_info(std::string extension);
    file_info(std::string extension, off_t  file_size);

    std::string Extension();

    bool operator==(file_info& other);

    void print_size();

    off_t Size();

private:
    std::string extension_;
    off_t  file_size_;
};


#endif //BOOST_OPTIONS_DEMO_FILE_INFO_H
