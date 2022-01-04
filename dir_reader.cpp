#include "dir_reader.h"
///#include <io.h>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>

void dir_reader::get_file_names_from_dir(std::string dir_name, std::map<std::string, file_info>& file_names_extensions,
                                         std::string system_delimiter, std::vector<std::string>& dirs, unsigned long min_size_byte){

    DIR* dir_ = opendir(dir_name.c_str());


    std::string file_name("");
    struct dirent* file;
    struct stat sb;
    //#include <sys/stat.h>
   // struct stat64 file_info; give an error

    while ( (file= readdir(dir_)) != nullptr){

        file_name = "";
        unsigned short name_length = file->d_namlen;
        for (int i = 0; i < name_length; ++i) {
           file_name += (file->d_name)[i];
        }


        std::string complete_filepath = dir_name + system_delimiter + file_name;

        if(file->d_type == DT_DIR){
            std::cout << "is dir " << file_name << std::endl;
            if (file_name!="." && file_name!="..") {
                std::cout << "not dots!" << std::endl;
                dirs.emplace_back(complete_filepath);
            }
        }else {

            treat_non_dirs(file_name, sb, complete_filepath, file_names_extensions, min_size_byte);


        }
    }

    std::cout << "dir reader finished" << std::endl;

}

void  dir_reader::treat_non_dirs(const std::string& file_name, struct stat& sb, const std::string& complete_filepath,
        std::map<std::string, file_info>& file_names_extensions, unsigned long min_size_byte ){

    std::size_t dot_index = file_name.find_last_of('.');

    //no extension for directories (remember . and .. too)

    //   std::string extension =(dot_index!=std::string::npos) ? file_name.substr(dot_index+1) : "";
    std::string extension = file_name.substr(dot_index+1);


    //WHY its not find #include <filesystem> even with -lstdc++fs
    /*      std::uintmax_t fs = std::filesystem::file_size((dir_name + "\\").append(file_name));
          std::cout << "size: " << fs << std::endl; */

    /*    if (stat64((dir_name.append("\\").append(file_name)).c_str(), &file_info) == 0)
           std::cout << "filesize" <<  file_info.st_size << std::endl;
*/

    sb = {};
    off_t  file_size;

    if (!stat(complete_filepath.c_str(), &sb)) {

        file_size = sb.st_size ;

    }

    if(file_size > min_size_byte) {
        file_names_extensions[complete_filepath] = file_info(extension, file_size);
    }


}