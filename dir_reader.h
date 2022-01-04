#ifndef BOOST_OPTIONS_DEMO_DIR_READER_H
#define BOOST_OPTIONS_DEMO_DIR_READER_H

#include <string>
#include <vector>
#include <map>
#include "file_info.h"

namespace dir_reader {

    void get_file_names_from_dir(std::string dir_name, std::map<std::string, file_info>& file_names_extensions,
                                 std::string system_delimiter, std::vector<std::string>& dirs, unsigned long min_size_byte);

    void treat_non_dirs(const std::string& file_name, struct stat& sb, const std::string& complete_filepath,
                         std::map<std::string, file_info>& file_names_extensions, unsigned long min_size_byte );
};


#endif //BOOST_OPTIONS_DEMO_DIR_READER_H
