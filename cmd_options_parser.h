#ifndef FILE_DUBLICATS_FOUNDER_CMD_OPTIONS_PARSER_H
#define FILE_DUBLICATS_FOUNDER_CMD_OPTIONS_PARSER_H


#include <string>
#include <vector>

namespace cmd_options_parser {

    int parse_cmd_command(int argc, char* argv[], bool& include_directories, bool& have_skipped_dirs,
                          bool& is_flag_extensions_to_find_on, bool& is_flag_extensions_prohibited_on,
                          bool& is_file_mask_on, unsigned int& portion, unsigned long& byte,
                          std::string& hash_algorithm, std::string& system_delimiter,
                          std::vector<std::string>& directories_to_scan, std::vector<std::string>& directories_skipped,
                          std::vector<std::string>& extensions_to_scan, std::vector<std::string>& extensions_to_skip,
                          std::vector<std::string>& file_masks);
};


#endif //FILE_DUBLICATS_FOUNDER_CMD_OPTIONS_PARSER_H
