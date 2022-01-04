#include <iostream>
#include "cmd_options_parser.h"
#include "cmd_options_helper.h"
#include <exception>

bool is_command_option(const char* arg){
    //TODO test
    return ('-' == *arg);
}

void change_l(std::string &option, bool &include_directories, bool &have_skipped_dirs) {

    include_directories = (option=="1");
    if(!include_directories){
        have_skipped_dirs = false;
    }
}

int change_d(std::vector<std::string> &command_option_args, std::vector<std::string> &directories) {
    //TODO for future make directory names checking procedure хотя бы элементарный трим шоли или чё там ещё проверять то можно? надо подумать
    for(std::string& option_arg: command_option_args){
        //TODO test
        directories.emplace_back(option_arg);
    }
    return 0;
}

void change_system(std::string& command, std::string& system_delimiter){
    if (command == "-w"){
        system_delimiter = "\\";
    } else {
        system_delimiter = "/";
    }
}

void change_ds(std::vector<std::string> &command_option_args, std::vector<std::string> &vector, bool &have) {

    change_d(command_option_args, vector);
    if (!vector.empty()){
        have = true;
    }
}

//TODO make pretty both
void change_size(std::string& string_number, unsigned long& portion){
    try {
        portion = std::abs(std::stol(string_number));
    } catch (std::exception& exception){
        portion = 1;
    }
}
void change_size(std::string& string_number, unsigned int& portion){
    try {
        portion = std::abs(std::stoi(string_number));
    } catch (std::exception& exception){
        portion = 5;
    }
}

void change_hs(std::string & option, std::string & hash) {

    //TODO need some enum or similar sings!!!!!!
    if (option == "md5" || option == "sha1" || option == "sha224" || option == "sha256"
    || option == "sha384" || option == "sha512" ) {
        hash = option;
    } else if ( option == "sha2") {
        hash = "sha224";
    }else
        hash = "md5";
}

int treat_command_with_options(std::string& command, std::vector<std::string>& command_option_args,
                               bool& include_directories, bool& have_skipped_dirs, bool& is_flag_extensions_to_find_on,
                               bool& is_flag_extensions_prohibited_on, bool& is_file_mask_on,
                               unsigned int& portion, unsigned long& byte, std::string& hash_algorithm, std::string& system_delimiter,
                               std::vector<std::string>& directories_to_scan, std::vector<std::string>& directories_skipped,
                               std::vector<std::string>& extensions_to_scan, std::vector<std::string>& extensions_to_skip,
                               std::vector<std::string>& file_masks){

    //TODO test: -l need to change have skipped dirs but if we have them after??? test this!!
    //same as above
    if(command == "-l"){
        change_l(command_option_args[0], include_directories, have_skipped_dirs);
    } else if(command == "-d"){
        if(change_d(command_option_args, directories_to_scan)==-1){
            return -1;
        }
    } else if(command == "-ds"){
        change_ds(command_option_args, directories_skipped, have_skipped_dirs);
    } else  if(command == "-s"){
        change_size(command_option_args[0], byte);
    } else if(command == "-fn"){
        change_ds(command_option_args, file_masks, is_file_mask_on);
    } else  if(command == "-x"){
        change_ds(command_option_args, extensions_to_scan, is_flag_extensions_to_find_on);
    } else if(command == "-e"){
        change_ds(command_option_args, extensions_to_skip, is_flag_extensions_prohibited_on);
    } else if(command == "-n"){
        change_size(command_option_args[0], portion);
    } else if(command == "-hs"){
        change_hs(command_option_args[0], hash_algorithm);
    } else if(command == "-w" ||command == "-u"){
        change_system(command, system_delimiter);
    } else {
        return -1;
    }

    return 0;
}

//1 - ok 0 - help was invoked -1 - error
int cmd_options_parser::parse_cmd_command(int argc, char* argv[], bool& include_directories, bool& have_skipped_dirs,
                                          bool& is_flag_extensions_to_find_on, bool& is_flag_extensions_prohibited_on,
                                          bool& is_file_mask_on, unsigned int& portion, unsigned long& byte,
                                          std::string& hash_algorithm, std::string& system_delimiter,
                       std::vector<std::string>& directories_to_scan, std::vector<std::string>& directories_skipped,
                       std::vector<std::string>& extensions_to_scan, std::vector<std::string>& extensions_to_skip,
                       std::vector<std::string>& file_masks){


    std::string help_invoke("-h");

    if (argv[1]==help_invoke.c_str()){

        cmd_options_helper::help(argc, argv);
        return 0;
    }

    for (int i = 1; i < argc; ) {

        std::vector<std::string> command_option_args;
        if (is_command_option(argv[i])){
            std::string command(argv[i]);
            while (++i < argc && !is_command_option(argv[i])){
                std::string new_arg(argv[i]);
                command_option_args.emplace_back(new_arg);
            }
            int is_ok = treat_command_with_options( command, command_option_args, include_directories, have_skipped_dirs,
                                       is_flag_extensions_to_find_on,is_flag_extensions_prohibited_on,
                                       is_file_mask_on, portion, byte, hash_algorithm, system_delimiter, directories_to_scan,
                                       directories_skipped, extensions_to_scan,extensions_to_skip, file_masks);
            if (is_ok == -1){
                return -1;
            }
        } else {
            //this line will never be used but just in case
            i++;
        }

    }

    return 1;

}