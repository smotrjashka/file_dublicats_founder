#include "dir_treat.h"
#include <set>
#include <cstdio>
#include "file_list_filter.h"
#include "md5.h"
#include "sha1.h"
#include "sha2.h"
#include <iostream>

void dir_treat::files_first_treat(std::map<std::string, file_info>& into_dir_map,
                       std::vector<std::vector<std::string>>& suspects) {


    for (auto it = into_dir_map.begin(); it != into_dir_map.end(); it++) {

        auto it2 = it;
        it2++;
        std::vector<std::string> potential_suspect;
        potential_suspect.emplace_back(it->first);
        for (; it2 != into_dir_map.end();) {
            if (it->second == it2->second) {
                potential_suspect.emplace_back(it2->first);
                auto it_t =it2++;
                into_dir_map.erase(it_t->first);

            } else {
                it2++;
            }
        }
        if (potential_suspect.size() > 1) {
            suspects.emplace_back(potential_suspect);
        }

    }

    std::cout << "files_first_treat end" << std::endl;
}

    void dir_treat::confirm_dublicatizm(std::vector<std::vector<std::string>>& suspects,
                                        std::vector<std::vector<std::string>>& confirmed_dublicats, int read_step, std::string& hash_algorithm){
      std::cout << "confirm dubl start" << std::endl;
        for(std::vector<std::string> one_line : suspects){
            treat_one_line_suspect(one_line, confirmed_dublicats, read_step, hash_algorithm);
        }
        std::cout << "confirm dubl finish" << std::endl;
    };


    void remove_elems_with_unique_value(std::map<std::string, std::string>& map){
        std::map<std::string, int> value_frequency_map;
        std::cout << "!!remove elems with unique value!!!" << std::endl;
        //TODO test this
        for (auto it = map.begin(); it != map.end(); it++) {
            value_frequency_map[it->second] += 1;
        }

        for (auto it = map.begin(); it != map.end(); ) {
           if ((value_frequency_map.find(it->second))->second==1){
              auto temp_it =  it++;
              std::cout << "erase " << temp_it->first << " ";
               map.erase(temp_it);
           } else {
               it++;
           }
        }

    }



void remove_elems_with_unique_value(std::map<std::string, std::string>& map, std::vector<std::string> vec){


    std::cout << "remove unique start map=" << map.size()  << " vec=" << vec.size() << std::endl;
    remove_elems_with_unique_value(map);

 /*   for (auto it = vec.begin(); it != vec.end(); ) {
        if ((deleted_key_vec.find(*it))->second==1){
            auto temp_it =  it++;
            vec.erase(temp_it);
        } else {
            it++;
        }
    }*/

    std::cout << "remove unique FINISH map=" << map.size()  << " vec=" << vec.size() << std::endl;
}

    std::string get_hash(std::string& buffered_symbols, int size_to_alignment, std::string& hash_algorithm){


        std::string hashed_symbols;

        std::cout << "buffered symbols: {" << buffered_symbols << "} ";

        if (buffered_symbols.size() < size_to_alignment){
            std::cout  << " ALIGMENT " << buffered_symbols.size() << " " << size_to_alignment;

   //         std::cout  << " WithOut last  {" << buffered_symbols << "} " << buffered_symbols.size() << std::endl;
            while (buffered_symbols.size() < size_to_alignment) {
                buffered_symbols += ('\u0000');
            }
        }
        std::cout << std::endl;



        //TODO куда-то эту хрень нужно перенести а то оно ж каждый раз проверяет
        if (hash_algorithm == "md5"){
            hashed_symbols = md5(buffered_symbols);
        } else if (hash_algorithm == "sha1"){

            hashed_symbols = sha1(buffered_symbols);
        } else if (hash_algorithm == "sha224"){

            hashed_symbols = sha224(buffered_symbols);
        } else if (hash_algorithm == "sha256"){
            hashed_symbols = sha256(buffered_symbols);
        } else if (hash_algorithm == "sha384"){
            hashed_symbols = sha384(buffered_symbols);
        } else if (hash_algorithm == "sha512"){
            hashed_symbols = sha512(buffered_symbols);
        }

        std::cout << "we have: " << hashed_symbols <<  std::endl;
        return hashed_symbols;

    }

    void compare_finished_files(std::vector<std::string>& finished_files, std::map<std::string, std::string>& map_filename_hash,
                                std::vector<std::vector<std::string>>& confirmed_dublicats){
        if (finished_files.size() == 1){
            map_filename_hash.erase(finished_files[0]);
            finished_files.clear();
            return;
        }
        std::cout << "!!!compare FINISHED FILES started" << std::endl;
        std::map<std::string, std::string> finished_files_hash;
        //DEBUG
        for(std::string& file_name : finished_files){
            std::cout << file_name << " " ;
        }
        std::cout << std::endl << map_filename_hash.size() << std::endl;
        for (std::map<std::string, std::string>::iterator it = map_filename_hash.begin(); it != map_filename_hash.end();) {
            if (file_list_filter::vector_contains(finished_files, it->first)){
                std::cout << "if" << std::endl;
                auto it_temp = it++;
                finished_files_hash[it_temp->first] = it_temp->second;
                map_filename_hash.erase(it_temp);
            } else {
                std::cout << "else" << std::endl;
                it++;
            }
        }
        std::cout << std::endl << "first for finished" << std::endl;

        //set&&
        std::vector<std::string> dubl_tripl_v_odnu_posudu;

        for (auto it = finished_files_hash.begin(); it != finished_files_hash.end();) {

            std::string current_file = it->first;
            dubl_tripl_v_odnu_posudu.emplace_back(current_file);
            auto temp_it = it++;
            for (auto it2 = it++; it2 != finished_files_hash.end();) {

                if (temp_it->second==it2->second){
                    if (it2 == it){
                        it++;
                    }
                    dubl_tripl_v_odnu_posudu.emplace_back(it2->first);
                    auto temp_it2 = it2++;

                    // чтоб не вписывать 2 раза один и тот же файл, но можно было сделать сет и уменьшить свои проблемы в 2 раза
                    finished_files_hash.erase(temp_it2);

                } else {
                    it2++;
                }

            }

            std::cout << "second for finished" << std::endl;

            if (dubl_tripl_v_odnu_posudu.size()>1){
                confirmed_dublicats.emplace_back(dubl_tripl_v_odnu_posudu);
            }
            dubl_tripl_v_odnu_posudu.clear();
        }

        std::cout << " compare f finished" << std::endl;
    }

    void dir_treat::treat_one_line_suspect(std::vector<std::string>& one_line_of_suspects,
                                std::vector<std::vector<std::string>>& confirmed_dublicats, int read_step,
                                std::string hash_algorithm){

        std::map<std::string, std::string> map_filename_hash;

        for (std::string& file_name : one_line_of_suspects) {
            map_filename_hash[file_name] = "";
        }

        // TODO test

        int start_position = 0;
        std::vector<std::string> finished_files;

        std::cout << "before while" << std::endl;
        while (map_filename_hash.size() > 0){


            std::cout << "for in while" << std::endl;
            for (std::map<std::string, std::string>::iterator it = map_filename_hash.begin(); it != map_filename_hash.end() ; it++) {

                std::string current_file_name = it->first;
                char buffer_char_array[read_step];
            // std::string buffer_char_array;

                FILE *pFile;

                ///«r»	Режим открытия файла для чтения. Файл должен существовать.
                pFile = fopen(current_file_name.c_str(), "r");

                //TODO test
                fseek(pFile, start_position, SEEK_SET);
                size_t red_bytes_number = fread(buffer_char_array, 1, read_step, pFile);

                if (red_bytes_number < read_step){
                    finished_files.emplace_back(current_file_name);
                }

                std::string  buff(buffer_char_array);
                std::cout << current_file_name << ": ";
                std::string hashed = get_hash(buff, read_step, hash_algorithm);
                map_filename_hash[current_file_name] += hashed;
            }
            std::cout << "before remove unique " << map_filename_hash.size() << std::endl;

            remove_elems_with_unique_value(map_filename_hash, finished_files);

            std::cout << "after remove " << map_filename_hash.size() << std::endl;
            if (!finished_files.empty()) {
                std::cout << "size : "  << finished_files.size() << std::endl;
                compare_finished_files(finished_files, map_filename_hash, confirmed_dublicats);
                //ideally we will empty compare finished files -> dublicats and we need to empty this vector for avoid unnecessary comparations
                finished_files.clear();
            }

            start_position+=read_step;
            std::cout << "AFTER inctrement" << std::endl;
        }


        std::cout << "one line finished" << std::endl;
    }



