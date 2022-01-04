#include <iostream>
#include "dir_reader.h"
#include <string>
#include "dir_treat.h"
#include "file_list_filter.h"
#include "cmd_options_parser.h"
// #include <boost/program_options.hpp>


int main(int argc, char* argv[]) {
    std::cout << "Hello, We will found dublicats!" << std::endl;



    bool include_directories = false;
    bool have_skipped_dirs = false;
    bool is_flag_extensions_to_find_on = false;
    bool is_flag_extensions_prohibited_on = false;
    bool is_file_mask_on = false;
    unsigned int N_portion = 5;
    unsigned long min_size_byte = 1;
    std::string hash_alg = "md5";

    std::vector<std::string> directories_to_scan;
    std::vector<std::string> directories_skipped;
    std::vector<std::string> extensions_to_scan;
    std::vector<std::string> extensions_to_skip;
    std::vector<std::string> file_masks;


    std::string system_delimiter;

#ifdef _WIN32
    std::cout << "in Windows";
    system_delimiter = "\\";
#endif

#ifdef linux
    std::cout <<  "In Linux";
    system_delimiter = "/";
#endif

    int is_all_right_with_command_options = cmd_options_parser::parse_cmd_command(argc, argv, include_directories, have_skipped_dirs, is_flag_extensions_to_find_on,
                                          is_flag_extensions_prohibited_on, is_file_mask_on, N_portion, min_size_byte,
                                          hash_alg, system_delimiter, directories_to_scan, directories_skipped, extensions_to_scan,
                                          extensions_to_skip, file_masks);

    if (argc < 2){
        std::cout << "You forget to pass arguments!!!" << std::endl
        << "Please, read README.md file in order to familiarize yourself with options!" << std::endl
        << "Also you can use help by passing -h";
        return -1;
    }

    if (is_all_right_with_command_options==0){
        return is_all_right_with_command_options;
    }

    if (is_all_right_with_command_options==-1){
        std::cout << "You not specified the directory to scan, we cant proceed like this!!";
        return -1;
    }


    //debug code
   /*
      std::string  directory_to_scan = "D:\\arm_courses";
    std::string subdirectory_to_scan = "D:\\arm_courses\\arm_course_start";
    extensions_to_scan.emplace_back("pdf");
    extensions_to_scan.emplace_back(".pdf");
    extensions_to_scan.emplace_back("tXt");
   // extensions_to_scan.emplace_back("png");
    extensions_to_skip.emplace_back("mp4");

    file_masks.emplace_back("*embed*");

   // std::string other_subdir = "D:\\arm_courses\\start_hardware";
    std::string other_subdir = "start_hardware";
    directories_skipped.emplace_back(other_subdir);*/

    std::map<std::string, file_info> into_dir_map;

    std::vector<std::string> dirs;
    for (std::string& directory_to_scan : directories_to_scan) {
        std::cout << "directory: {" << directory_to_scan << std::endl;
        dir_reader::get_file_names_from_dir(directory_to_scan, into_dir_map, system_delimiter, dirs, min_size_byte);
    }


    for (auto it = into_dir_map.begin(), end = into_dir_map.end(); it != end; it++) {

        std::cout<< "name:{" << it->first << "} ext:{" << (it->second).Extension()  << " size = " << (it->second).Size() << "}" << std::endl;

    }

    std::cout << "size" << dirs.size() << "dirs:" << std::endl;

    for (std::string dir : dirs) {
        std::cout << dir << std::endl;
    }

    if (include_directories){
        while (!dirs.empty()){

            std::vector<std::string> temporal_dirs;
            for ( auto it = dirs.begin(); it != dirs.end(); it++) {
                bool is_in_black_list = false;
                if (have_skipped_dirs && directories_skipped.size()>0){

                    for (auto it_black = directories_skipped.begin(); it_black!=directories_skipped.end(); it_black++) {
                        if (*it == *it_black){
                            is_in_black_list = true;
                            directories_skipped.erase(it_black);
                            break;
                        } else if ((*it).substr(((*it).find_last_of(system_delimiter))+1) ==  *it_black){
                            std::cout << *it << " is " << *it_black << " we got it" << std::endl;
                            is_in_black_list = true;
                            // if subdirectory for skip has "short" name I would left it because for example both dir for scan can have subdir with name "temp"
                            break;
                        }
                    }
                }
                if (!is_in_black_list) {
                    dir_reader::get_file_names_from_dir(*it, into_dir_map, system_delimiter, temporal_dirs, min_size_byte);
                }
            }

            dirs.clear();
            for (std::string di : temporal_dirs) {
                dirs.push_back(di);
            }

        }

    }

    if(is_flag_extensions_to_find_on || is_flag_extensions_prohibited_on) {
        file_list_filter::filter_extensions(into_dir_map, extensions_to_scan, extensions_to_skip);
    }

    if (is_file_mask_on){
        file_list_filter::filter_file_name_by_masks(into_dir_map, file_masks, system_delimiter);
    }



    std::cout << "filelist after all filtering processes done:" << std::endl;
    for (auto it = into_dir_map.begin(); it!=into_dir_map.end(); it++) {
        std::cout << it->first << " " << it->second.Extension() << " " << it->second.Size() << std::endl;
    }

    std::cout << "file list finished" << std::endl;


    std::vector<std::vector<std::string>> suspects;
    std::vector<std::vector<std::string>> dublicats;


    dir_treat::files_first_treat(into_dir_map, suspects);

    ///TODO debug and fix !!!!
    std::cout << "size of suspects=" << suspects.size() << std::endl ;

    dir_treat::confirm_dublicatizm(suspects, dublicats, N_portion, hash_alg);

    std::cout << "RESULT: "<< "size=" << dublicats.size() << std::endl ;

    for (const std::vector<std::string>& ve : dublicats) {

        std::cout << "duplicats: ";
        for (const std::string& file : ve) {

            std::cout << file << " ";

        }

        std::cout << std::endl;
    }


    return 0;
}
