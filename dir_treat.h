#ifndef BOOST_OPTIONS_DEMO_DIR_TREAT_H
#define BOOST_OPTIONS_DEMO_DIR_TREAT_H

#include <string>
#include <vector>
#include "file_info.h"
#include <map>

namespace dir_treat {

   void files_first_treat(std::map<std::string, file_info>& into_dir_map, std::vector<std::vector<std::string>>& suspects);

   void confirm_dublicatizm(std::vector<std::vector<std::string>>& suspects,
                            std::vector<std::vector<std::string>>& confirmed_dublicats, int read_step, std::string& hash_algorithm);

   void treat_one_line_suspect(std::vector<std::string>& one_line_of_suspects,
                               std::vector<std::vector<std::string>>& confirmed_dublicats, int read_step, std::string hash_algorithm);
};


#endif //BOOST_OPTIONS_DEMO_DIR_TREAT_H
