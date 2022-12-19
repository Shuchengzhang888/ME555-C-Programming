#include "path-step4.cpp"


int main(int argc, char ** argv){
    try{
        //Check if there are 4 command lines
        if(argc != 4){
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

        size_t start = atoi(argv[2]);
        size_t goal = atoi(argv[3]);
        //Check if the start and end nodes are legal
        if(start < 0 || goal < 0 || start > goal || start > g.get_num_nodes() - 1 || goal > g.get_num_nodes() - 1){
            throw invalid_command_line();
        }
        //Implement path planning according
        std::pair<std::vector<size_t>, double> pat = g.find_path(start, goal,"");
        if(pat.first.empty() && pat.second == 0){
            return EXIT_FAILURE;
        }
        else{
            Path p(pat);
            //Print path and weight
            std::cout << p;
        }
        
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
