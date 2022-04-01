#include "parse.hpp"

#include <exception>
// any other headers you need
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

//Override std::exception::what() here
class invalid_input : public std::exception{
  public:
    const char * what() const throw(){
        return "Wrong Input Format. The wrong line is ";
    }
};
class invalid_command_line : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid Command Line.";
    }
};
class invalid_file : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid File.";
    }
};


void split_line(const std::string & line, std::vector<std::string> & vec){
    std::string colon = ":";
    std::string comma = ",";
    size_t colon_index = line.find(colon);
    size_t comma_index = line.find(comma);
    if(colon_index == line.size() - 1){
        vec.push_back(line.substr(0, colon_index));
        vec.push_back("");
        vec.push_back("");
    }
    else{
        if(comma_index == line.npos){
            vec.push_back(line.substr(0, colon_index));
            vec.push_back(line.substr(colon_index + 2, line.size()));
            vec.push_back("");
        }
        else{
            vec.push_back(line.substr(0, colon_index));
            vec.push_back(line.substr(colon_index + 2, comma_index - 4));
            vec.push_back(line.substr(comma_index + 2, line.size()));
        }
    }
}

item_t * parseLine(const std::string & line){
    item_t * item = new item_t;
    std::vector<std::string> vec;

    split_line(line, vec);
    //pair是将2个数据组合成一组数据，当需要这样的需求时就可以使用pair，如stl中的map就是将key和value放在一起来保存。
    //另一个应用是，当一个函数需要返回2个数据的时候，可以选择pair。
    //pair将一对值(T1和T2)组合成一个值，这一对值可以具有不同的数据类型（T1和T2），两个值可以分别用pair的两个公有函数first和second访问。
    item->first = vec[0];
    std::vector<std::string>::iterator it = vec.begin();
    vec.erase(it);
    item->second= vec;

    return item;
}

void print_item_t(std::vector<item_t *> & items){
    for(size_t i = 0; i < items.size(); i++){
    std::cout << "key = " << items[i]->first << std::endl;
    std::cout << "  values = ";
    if(items[i]->second[1] == ""){
      std::cout << items[i]->second[0] << std::endl;
    }
    else{
      std::cout << items[i]->second[0] << "; "<<items[i]->second[1] << std::endl;
    }
  }

}

int main(int argc, char ** argv){
    try{
        if(argc != 2){
            throw invalid_command_line();
        }
    }
    catch (invalid_command_line & e){
        std::cerr << e.what()<< std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream f(argv[1]);
    try{
        if(!f.is_open()){
            throw invalid_file();
        }
    }
    catch (invalid_file & e){
        std::cerr << e.what()<< std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<item_t *> items;
    std::string line;
    size_t count = 0;
    //Practice dynamic allocation by allocating an item_t *
    //for each line read, storing these pointers in a vector.
    while(std::getline(f, line)){
        count ++;
        try{
            //string::find
            //The position of the first character of the first match.
            //If no matches were found, the function returns string::npos.
            if(line.find(":") == line.npos){
                throw invalid_input();
            }
        }
        catch (invalid_input & e){
            std::cerr << e.what() << count << "."<< std::endl;
            continue;
        }
        item_t * item = parseLine(line);
        items.push_back(item);
    }

    print_item_t(items);
    for(size_t i = 0; i < items.size(); i++){
        delete items[i];
    }
    return EXIT_SUCCESS;
}

