#ifndef BOOST_OPTIONS_DEMO_FILE_LIST_FILTER_H
#define BOOST_OPTIONS_DEMO_FILE_LIST_FILTER_H

#include <string>
#include <vector>
#include <map>
#include "file_info.h"

namespace file_list_filter {

   void filter_extensions(std::map<std::string, file_info>& into_dir_map, std::vector<std::string>& extensions_to_scan,
                          std::vector<std::string>& extensions_to_skip);

   void filter_file_name_by_masks(std::map<std::string, file_info>& into_dir_map, std::vector<std::string>& file_masks,
                                  const std::string& system_delimiter);


   void filter_extensions_dot(std::vector<std::string>& extensions);

   void filter_duplicate_extension(std::vector<std::string>& extensions);

    void remove_skipped_from_desired(std::vector<std::string> &extensions_desired, std::vector<std::string> &extensions_skipped);

    void to_lower_case(std::vector<std::string>& extensions);

    std::string to_lower_case(std::string extension);

    bool vector_contains(const std::vector<std::string> &vec_str, const std::string& str_for_search);
};


#endif //BOOST_OPTIONS_DEMO_FILE_LIST_FILTER_H
