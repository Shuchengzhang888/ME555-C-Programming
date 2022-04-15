#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <exception>

//#define output_name "output.txt"


class invalid_input : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid Input Words.";
    }
};
class invalid_type : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid Type.";
    }
};

void split_line(const std::string & line, std::vector<std::string> & vec){
    std::string colon = ":";
    size_t colon_index = line.find(colon);
    try{
        if(colon_index == line.npos){
            throw invalid_input();
        }
    }
    catch (invalid_input & e){
        std::cerr << e.what()<< std::endl;
        exit(EXIT_FAILURE);
    }
    vec.push_back(line.substr(0, colon_index));
    vec.push_back(line.substr(colon_index + 1, line.size()));
}


std::map<std::string, std::vector<std::string> > read_words(std::ifstream & f_words){
    std::map<std::string, std::vector<std::string> > words;
    std::string line;
    while(std::getline(f_words, line)){
        std::vector<std::string> vec;
        split_line(line, vec);
        words[vec[0]].push_back(vec[1]);
    }
    return words;
}

void replace_words(std::string & line, std::map<std::string, std::vector<std::string> > & words, std::vector<std::string> & used_words){
    std::string underscore = "_";
 
    while(line.find(underscore) != line.npos){
        std::string::size_type pos1, pos2;
        std::string type;
        std::string rand_words;

        pos1 = line.find(underscore);
        pos2 = line.find(underscore, pos1 + 1);
        type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        //std::string.c_str() returns const char *
        if(atoi(type.c_str()) == 0){
            //type situation
            try{
                if(words.find(type) == words.end()){
                    throw invalid_type();
                }
                else{
                    int r = rand() % words[type].size();
                    rand_words = words[type][r];
                }
            }
            catch (invalid_type & e){
                std::cerr << e.what()<< std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else{
            //number situation
            try{
                size_t num = atoi(type.c_str());
                if(num < 1 || num > used_words.size()){
                    throw invalid_type();
                }
                rand_words = used_words[used_words.size() - num];
            }
            catch (invalid_type & e){
                std::cerr << e.what()<< std::endl;
                exit(EXIT_FAILURE);
            }
        }
        line = line.replace(pos1, pos2 - pos1 + 1, rand_words);
        used_words.push_back(rand_words);
    }
}


std::vector<std::string> write_story(std::ifstream & f_story, std::map<std::string, std::vector<std::string> > words){
    std::vector<std::string> story;
    std::string line;
    std::vector<std::string> used_words;

    while(std::getline(f_story, line)){
        replace_words(line, words, used_words);
        story.push_back(line);
    }
    return story;
}

void print_story(std::vector<std::string> story){
  //std::ofstream OutFile(output_name);
    std::vector<std::string>::iterator iter;
    for(iter = story.begin(); iter != story.end(); ++iter){
        if(iter == story.end() - 1){
	  std::cout << *iter << std::endl;
        }
        else{
	  std::cout << *iter << "\n";
        }
    }
    
    //OutFile.close();
}

int main(int argc, char ** argv){
       if(argc != 4){
            fprintf(stderr, "Invalid command line arguments\n");
            return EXIT_FAILURE;
        }
        std::ifstream f_story(argv[1]);
        std::ifstream f_words(argv[2]);
        if(!(f_story.is_open() && f_words.is_open())){
            fprintf(stderr, "Invalid file name\n");
            return EXIT_FAILURE;
        }
        //set random seed
        int r = atoi(argv[3]);
        if(r <= 0){
            fprintf(stderr, "Invalid seed number\n");
            return EXIT_FAILURE;
        }
        //For every different seed value used in a call to srand, the pseudo-random number generator 
        // can be expected to generate a different succession of results in the subsequent calls to rand.
        //srand(r)会影响rand()的值
        srand(r);
        std::map<std::string, std::vector<std::string> > words;
        words = read_words(f_words);
        std::vector<std::string> story;
        story = write_story(f_story, words);
        print_story(story);
        f_story.close();
        f_words.close();
	
    return EXIT_SUCCESS;
}
