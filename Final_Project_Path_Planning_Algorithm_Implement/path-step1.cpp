#include "path-planning.hpp"

class invalid_input : public std::exception{
  public:
    const char * what() const throw(){
        return "Wrong Input Format.\n";
    }
};
class invalid_command_line : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid Command Line.\n";
    }
};
class invalid_file : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid File.\n";
    }
};
class invalid_nodes : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid Input Nodes.";
    }
};

double Node::distance_from(const Node & p) const{
    //Compute the Euclidean distance from this to p
    return std::sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}



void Graph::add_node(size_t index, double x, double y){
    //Build a Node to save node information
    Node nod(index, x, y);
    num_node ++;
    //Add nod to nodes acoording to its index.
    // (The number of row we put nod in is equal to its index)
    if(nodes.size() <= index){
        nodes.resize(index);
        nodes.insert(nodes.begin() + index,nod);
    }
    else{
        nodes.insert(nodes.begin() + index,nod);
        nodes.erase(nodes.begin() + index + 1);
    }
    //Increase the adj_list size to save the information of new-adding node
    if(adj_list.size() < nodes.size()){
        adj_list.resize(nodes.size());
    }
}

int Graph::check_node(){
    std::vector<Node>::iterator it;
    size_t i = 0;
    //Check if the number of row we put nod in is equal to its index 
    try{
        for(it = nodes.begin(); it != nodes.end(); ++it){
            if(it->get_index() != i){
                return EXIT_FAILURE;
            }
            i++;
        }
        return EXIT_SUCCESS;
    }
    catch (invalid_input & e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

}

int Graph::add_edge(size_t u, size_t v){
    try{
        //Check if u and v is in nodes
        if(u > nodes.size() - 1 || u < 0 || v > nodes.size() - 1 || v < 0){
            throw invalid_nodes();
        }
    }
    catch (invalid_nodes & e){
        std::cerr << e.what()<< std::endl;
        return EXIT_FAILURE;
    }
    //Add the nodes of u and v to adj_list
    adj_list[u].insert(std::make_pair(v, nodes[v].distance_from(nodes[u])));
    adj_list[v].insert(std::make_pair(u, nodes[u].distance_from(nodes[v])));
    return EXIT_SUCCESS;
}

std::ostream & operator<<(std::ostream & s, Graph & g){
    //Print coordinates
    std::vector<Node>::iterator it;
    for(it = g.nodes.begin(); it != g.nodes.end(); ++it){
        s << "(" << it->get_x() << "," << it->get_y() <<")";
        if(it != g.nodes.end() - 1){
            s << " ";
        }
    }
    s << "\n";
    //Print edges
    std::vector<std::map<size_t, double> >::iterator iter;
    size_t i = 0;
    for(iter = g.adj_list.begin(); iter != g.adj_list.end(); ++iter){
      s << i << ": ";
      i++;
      std::map<size_t, double>::iterator it;
      size_t j = 0;
      for(it = iter->begin(); it != iter->end(); ++it){
        s << it->first << "," << it->second;
        if(j != iter->size() - 1){
          s << " ";
        }
        j++;
      }
      s << "\n";
    }
    s << std::endl;
    return s;
}

std::ostream & operator<<(std::ostream & s, Path & p){
    //Print path and its total distance
    std::vector<size_t>::iterator it;
    for(it = p.short_path.end() - 1; it != p.short_path.begin(); --it){
      s << *it << " ";
    }
    s << *it << " : " << p.dis << std::endl;
    return s;
}




int read_nodes(std::string & line, Graph & g){
    /*
    This function is to read node from file line and save it to nodes.
    Input:
      line: lines under the signal of "$nodes"
      g: map information
    */
    try{
        //Check if the input has letter
        std::string::iterator it;
        for(it = line.begin(); it != line.end(); ++it){
            if(isalpha(*it)){
                throw invalid_input();
            }
        }
        //Find the position of the two spaces and splite the line according to them
        std::string::size_type pos1, pos2;
        pos1 = line.find(" ");
        pos2 = line.find(" ", pos1 + 1);
        //Check if there are two spaces
        if(pos1 == line.npos || pos2 == line.npos){
            throw invalid_input();
        }
        g.add_node(atof(line.substr(0).c_str()), atof(line.substr(pos1).c_str()),atof(line.substr(pos2).c_str()));
        return EXIT_SUCCESS;
    }
    catch (invalid_input & e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int read_edges(std::string & line, Graph & g){
    /*
    This function is to read edge from file line and save it to adj_list.
    Input:
      line: lines under the signal of "$edges"
      g: map information
    */
    try{
        //Check if the input has letter
        std::string::iterator it;
        for(it = line.begin(); it != line.end(); ++it){
            if(isalpha(*it)){
                throw invalid_input();
            }
        }
        //Find the position of the space and splite the line according to it
        std::string::size_type pos1;
        pos1 = line.find(" ");
        //Check if there is space
        if(pos1 == line.npos){
            throw invalid_input();
        }
        if(g.add_edge(atof(line.substr(0).c_str()), atof(line.substr(pos1).c_str())) == EXIT_FAILURE){return EXIT_FAILURE;}
        return EXIT_SUCCESS;
    }
    catch (invalid_input & e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int check_file(size_t n_line_num, size_t e_line_num){
    /*
    This function is to check if the txt has two $ signs and $Node should be front of $Edge
    Input:
      n_line_num: the line number of $Nodes
      e_line_num: the line number of $Edges
    */
    try{
        if (n_line_num == 0 || e_line_num == 0 || n_line_num >= e_line_num){
            throw invalid_input();
        }
        return EXIT_SUCCESS;
    }
    catch (invalid_input & e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}


int read_file(std::ifstream & f, Graph & g){
    /*
    This function is to read file and save edges and nodes.
    Input:
      f: the input file
      g: map information
    */
    std::string line;
    std::string flag;
    size_t line_num = 0;
    size_t n_line_num = 0;
    size_t e_line_num = 0;
    while(std::getline(f, line)){
        line_num ++;
        //Skip empty line
        if(line == ""){ 
            continue;
        }
        if(line == "$nodes"){
            flag = "$nodes";
            n_line_num = line_num;
            continue;
        }
        if(line == "$edges"){
            if(g.check_node()== EXIT_FAILURE){return EXIT_FAILURE;}
            flag = "$edges";
            e_line_num = line_num;
            if(check_file(n_line_num, e_line_num) == EXIT_FAILURE){return EXIT_FAILURE;}
            continue;
        }

        if(flag == "$nodes"){
            if(read_nodes(line, g) == EXIT_FAILURE){return EXIT_FAILURE;}
        }
        if(flag == "$edges"){
            if(read_edges(line, g) == EXIT_FAILURE){return EXIT_FAILURE;}
        }
    }
    return EXIT_SUCCESS;
}
