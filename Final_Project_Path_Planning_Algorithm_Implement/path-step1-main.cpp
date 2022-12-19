#include "path-step1.cpp"

int main(int argc, char ** argv){
    try{
        //Check if there are 2 command lines
        if(argc != 2){
            throw invalid_command_line();
        }
        std::ifstream f(argv[1]);
        //Check if the file can be open
        if(!f.is_open()){
            throw invalid_file();
        }
        //Build map g with nodes, edge
        Graph g; 
        if(read_file(f, g) == EXIT_FAILURE){return EXIT_FAILURE;}
        //Print map
        std::cout << g;
    }
    catch (invalid_command_line & e){
        std::cerr << e.what()<< std::endl;
        return EXIT_FAILURE;
    }
    catch (invalid_file & e){
        std::cerr << e.what()<< std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
