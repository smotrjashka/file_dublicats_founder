#include "cmd_options_helper.h"
#include <string>
#include <iostream>

void print_system_delimeter_options_info() {

    std::cout << "`-w` or `-u` options are used for implicit indication of OS" << std::endl <<
              "`-w` for windows OS or `-u` for Linux or Mac" << std::endl;

}

void print_general_commands_info(){
    std::cout << "`-d` directories for scan" << std::endl <<
              "`-ds` directories for skip" << std::endl <<
              "`-l 1` or `-l 0`" << std::endl <<
              "`-s` min file size" << std::endl <<
              "`-fn` file names mask " << std::endl <<
              "`-x` extension of desired files "<< std::endl <<
              "`-e` extension of skipped files" << std::endl <<
              "`-n` size of read block" << std::endl <<
              "`-hs` hash function" << std::endl <<
              "`-w` или `-u` используется для прямого указания системы в которой запускается утилита" << std::endl;
}




void print_l_info(){
    std::cout <<
              "`-l 1` or `-l 0`" << std::endl <<
              "    0 means only current directory (default value)" << std::endl <<
              "    1 mean scan subdirectories too" << std::endl;
}


void print_d_info(){
    std::cout << "`-d` directories for scan" << std::endl <<
              "'-d \"path_to_scanned_directory\"'" << std::endl <<
              "'-d \"path_to_scanned_directory1\" \"path_to_scanned_directory2\"'" << std::endl <<
              "if you no indicate any directory program will be finished with error message!" << std::endl <<
              "Wrong/unexisting paths just provoke no scan" << std::endl;
}

//TODO test case with несколькими уровнями вложенности папок саму работу программы
void print_ds_info(){
    std::cout << "`-ds` subdirectories will be skipped during scan process" << std::endl <<
              "only works with '-l 1' option, otherwise this option will be ignored" << std::endl <<
              "Proper usage: '-ds \"subdirectory_name_or_path_to_skip\"'" << std::endl;
}

void print_hs_info(){

    std::cout << "-hs hash_function" << std::endl << "by default used md5" << std::endl;
    std::cout << "Supported algorithms: "
                 " - md5\n"
                 " - sha1\n"
                 " - sha2\n"
                 " - sha224\n"
                 " - sha256\n"
                 " - sha384\n"
                 " - sha512" << std::endl;

}

void print_n_info(){

    std::cout <<  "-n size_of_read_block_number_in_bytes" << std::endl;

}

void print_e_info(){

    std::cout << "-e extension_of_skipped_files" << std::endl <<
              "Can be with or without dot" << std::endl
              << "You can exclude more than one extension by '-e first_extension second_one'" << std::endl;


}

void print_x_info(){

    std::cout << "-x extension_of_desired_files "<< std::endl <<
              "Can be with or without dot" << std::endl
              << "You can include more than one extension by '-x first_extension second_one'" << std::endl;

}

void print_fn_info(){

    std::cout << "-fn \"file_names_mask\" " << std::endl;

    std::cout <<"'start_name*' выберет все файлы начинающиеся со 'start_name'" << std::endl <<
              "например 'start_name_of_some_video.mp4' или 'start_name_of_book.pdf'" << std::endl <<


              "`*contains_simbols*` выберет все файлы в имени которых содержится `*contains_simbols*`" << std::endl <<
              "например `contains_simbols_vidosik.mkv` или `other_contains_simbols_text.txt` или `selfie_contains_simbols_image.png`" << std::endl <<

              "`*final_simbols` тут я решила подразвлечься и выбрать все файлы заканчивающиеся на данные символы не учитывая расширения и \"присваиваний повторения\"" << std::endl <<
              "Маска файла без указания звездочки будет искаться as it is " << std::endl <<
              " маски указываются строго в \" \" иначе маски и скиппед сабдиректории просто отбрасываются" << std::endl;

}

void print_s_info(){


    std::cout << "-s min_file_size_for_scan" << std::endl <<
              "Specify only number. In bytes. By default used 1 byte. 0 byte will be accepted." << std::endl <<
              "Number less than zero will be treated without sign. Wrong argument or float numbers will be ignored and used default size!"
              << std::endl;

}

void print_unexisting_command_info(){
    std::cout << "This command option is not exist yet!" << std::endl;
    std::cout << "You can suggest this one by creating issue for this github  project!" << std::endl;
    print_d_info();
}


void print_command_info(const char* str) {

    ///TODO I dont like this version but switch version I hate more -> maybe I will change to map with st::string <-> function somehow
    if(str == std::string("-l").c_str()){
        print_l_info();
    } else if(str == std::string("-d").c_str()){
        print_d_info();
    } else if(str == std::string("-ds").c_str()){
        print_ds_info();
    } else  if(str == std::string("-s").c_str()){
        print_s_info();
    } else if(str == std::string("-fn").c_str()){
        print_fn_info();
    } else  if(str == std::string("-x").c_str()){
        print_x_info();
    } else if(str == std::string("-e").c_str()){
        print_e_info();
    } else if(str == std::string("-n").c_str()){
        print_n_info();
    } else if(str == std::string("-hs").c_str()){
        print_hs_info();
    } else if(str == std::string("-w").c_str() || str == std::string("-u").c_str()){
        print_system_delimeter_options_info();
    } else {
        print_unexisting_command_info();
    }

}



void cmd_options_helper::help(int argc, char* argv[]){
    if (argc == 2){
        print_general_commands_info();
    } else {
        print_command_info(argv[2]);
    }
}
