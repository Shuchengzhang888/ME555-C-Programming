#include "path-step4.cpp"


int main(int argc, char ** argv){
    try{
        //Check if there are 5 or 6 command lines
        if(argc != 5 && argc != 6){
            throw invalid_command_line();
        }
        std::ifstream f_map(argv[1]);
        std::ifstream f_obs(argv[2]);
        //Check if the file can be open
        if(!(f_map.is_open() && f_obs.is_open())){
            throw invalid_file();
        }
        //Build map g with nodes, edge, and obstacles
        Graph g; 
        if(read_file(f_map, g) == EXIT_FAILURE){return EXIT_FAILURE;}
        if(read_obs(f_obs, g)  == EXIT_FAILURE){return EXIT_FAILURE;}
        if(g.apply_obs() == EXIT_FAILURE){return EXIT_FAILURE;}

        size_t start = atoi(argv[3]);
        size_t goal = atoi(argv[4]);
        //Check if the start and end nodes are legal
        if(start < 0 || goal < 0 || start > goal || start > g.get_num_nodes() - 1 || goal > g.get_num_nodes() - 1){
            throw invalid_command_line();
        }
        //Implement path planning according to the method we choose
        std::string flag;
        if(argc == 6){
            flag = argv[5];
            if(flag != "-a") {
                throw invalid_command_line();
            }
        }
        std::pair<std::vector<size_t>, double> pat = g.find_path(start, goal, flag);
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
