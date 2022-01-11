#include "file_list_filter.h"
#include <set>
#include <iostream>
#include <algorithm>
#include <regex>

void file_list_filter::filter_extensions(std::map<std::string, file_info>& into_dir_map,
                                         std::vector<std::string>& extensions_to_scan,
                                         std::vector<std::string>& extensions_to_skip) {

    filter_extensions_dot(extensions_to_skip);
    filter_extensions_dot(extensions_to_scan);
    if (!extensions_to_scan.empty()){

        if (!extensions_to_skip.empty()){
            remove_skipped_from_desired(extensions_to_scan, extensions_to_skip);
        }

        for (auto it = into_dir_map.begin(); it != into_dir_map.end(); ) {
            std::string current_extension = it->second.Extension();
            if(!vector_contains(extensions_to_scan, current_extension) ){
                auto tem_it = it++;
                into_dir_map.erase(tem_it);
            } else{
                it++;
            }
        }

    }else if (!extensions_to_skip.empty()){


        for (auto it = into_dir_map.begin(); it != into_dir_map.end(); ) {
            std::string current_extension = it->second.Extension();
            if(vector_contains(extensions_to_skip, current_extension) ){
                auto tem_it = it++;
                into_dir_map.erase(tem_it);
            } else{
                it++;
            }
        }


    }


}

bool file_list_filter::vector_contains(const std::vector<std::string> &vec_str, const std::string& str_for_search) {

    //?? std::any_of
    for (const std::string& str : vec_str) {
        if (str == str_for_search)
            return true;
    }


    return false;
}

void file_list_filter::remove_skipped_from_desired(std::vector<std::string> &extensions_desired, std::vector<std::string> &extensions_skipped){
    for (auto it = extensions_desired.begin(); it != extensions_desired.end(); ) {

        if (vector_contains(extensions_skipped, *it)){
            auto temp_it = it++;
            extensions_desired.erase(temp_it);
        } else{
            it++;
        }

    }
}

void file_list_filter::filter_extensions_dot(std::vector<std::string> &extensions) {
    if (!extensions.empty()) {
        for (auto &extension: extensions) {
            if (extension[0] == '.') {
                extension = extension.substr(1);
            }
        }


        to_lower_case(extensions);

        filter_duplicate_extension(extensions);

    }
}

void file_list_filter::to_lower_case(std::vector<std::string>& extensions){

    filter_duplicate_extension(extensions);

    for (std::string &extension: extensions) {
        to_lower_case(extension);
    }

    ///может оставить одну??? эту вторую???
    filter_duplicate_extension(extensions);
}

void file_list_filter::to_lower_case(std::string& extension) {
    for (auto &ext_c : extension) {
        ext_c = tolower(ext_c);
    }
}


void file_list_filter::filter_duplicate_extension(std::vector<std::string>& extensions) {
    if (extensions.size()>1) {
        for (std::vector<std::string>::iterator it = extensions.begin(); it != extensions.end();) {
            std::string current_string(*it);
            std::cout << current_string << std::endl;
            bool is_dublicat = false;
            for (auto it2 = ++it; it2 != extensions.end(); it2++) {
                if (current_string == *it2) {
                    extensions.erase(it2);
                    is_dublicat = true;
                    break;
                }
            }
            if (!is_dublicat) {
                it++;
            }
        }
    }
}

std::string file_mask_to_regexp(std::string& f_mask){

    std::string reg("");
    for (char c : f_mask) {
        if (c == '*'){
            reg += '.';
        }
        reg += c;
    }

    if (reg.at(reg.size()-1) == '*'){
        reg += "(\\([0-9]+\\))*\\.[a-zA-Z0-9]+";
    }
    
    return reg;
}

std::regex create_regexp_mask(std::vector<std::string>& file_masks){

    std::string reg("");

    for (std::string& f_mask : file_masks) {
        reg += file_mask_to_regexp(f_mask) + "|";
    }

    reg.erase(reg.size()-1);

    return std::regex(reg);
}


void file_list_filter::filter_file_name_by_masks(std::map<std::string, file_info> &into_dir_map,
                                                 std::vector<std::string> &file_masks, const std::string& system_delimiter) {


    if (file_masks.size() > 0) {


        std::regex regexp = create_regexp_mask(file_masks);

        for (auto it = into_dir_map.begin(); it != into_dir_map.end();) {
            std::string cur_file_name = it->first;

            if (std::regex_match(cur_file_name.substr(cur_file_name.find_last_of(system_delimiter)+1), regexp)) {
                std::cout << "file name {" << cur_file_name << "} match with file mask!";
                it++;
            } else {

                it++;
                into_dir_map.erase(cur_file_name);
            }

        }


    }

}