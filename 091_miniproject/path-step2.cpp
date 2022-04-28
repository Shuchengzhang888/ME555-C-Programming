
#include "path-step1.cpp"

class path_nonexist : public std::exception{
  public:
    const char * what() const throw(){
        return "No Path Exists.\n";
    }
};

void Graph::dijkstra(size_t start, size_t goal){
    //Initialize nodes information
    d_node.resize(nodes.size());
    for(size_t i = 0; i < d_node.size(); i++){
        d_node[i].known = false;
        d_node[i].dist = INFINITY;
        //To check if the path exists
        d_node[i].pre = -1;
    }
    //Set the dis of start point is 0
    d_node[start].dist = 0;
    
    while(true){
        //Find the lowest dis in all unknown nodes and make it to be current node
        size_t v = 0;
        double max = INFINITY;
        size_t flag = 0;
        for(size_t i = 0; i < d_node.size(); i++){
            if(!d_node[i].known && (max > d_node[i].dist)){
                max = d_node[i].dist;
                v = i;
                flag = 1;
            }
        }
        //If we cannot find, end the loop
        if(flag == 0){
            break;
        }
        //Set the current node be known
        d_node[v].known = true;
        //Update all unknown adjacent nodes information of the current node
        std::map<size_t, double>::iterator it;
        for(it = adj_list[v].begin(); it != adj_list[v].end(); ++it){
            if(!d_node[it->first].known){
                //If the distance to this adjacent node through the current node is smaller than
                // the distance of this adjacent node, update its parent node to the current node
                if(d_node[v].dist + it->second < d_node[it->first].dist){
                    d_node[it->first].dist = d_node[v].dist + it->second;
                    d_node[it->first].pre = v;
                }
            }
        }
    }
}

std::pair<std::vector<size_t>, double> Graph::find_path(size_t start, size_t goal, std::string flag){
    try{
        std::vector<size_t> path;
        //A star Algorithm
        if(flag == "-a"){
            this->a_star(start, goal);
            path.push_back(goal);
            //Find the path from the end to start using pre fields
            for(size_t i = goal; a_node[i].pre != start; i = a_node[i].pre){
                //If the pre value of node we pass is -1, means it is not connect to any other nodes,
                // which means there is no path.
                if(a_node[i].pre == -1){
                    throw path_nonexist();
                }
                else{
                    path.push_back(a_node[i].pre);
                }
            }
            path.push_back(start);
            return std::make_pair(path, a_node[goal].f);
        }
        //Dijstra Algorithm
        else{
            this->dijkstra(start, goal);
            path.push_back(goal);
            for(size_t i = goal; d_node[i].pre != start; i = d_node[i].pre){
                if(d_node[i].pre == -1){
                    throw path_nonexist();
                }
                else{
                    path.push_back(d_node[i].pre);
                }
            }
            path.push_back(start);
            return std::make_pair(path, d_node[goal].dist);
        }
    }
    catch (path_nonexist & e){
        std::cerr << e.what() << std::endl;
        std::vector<size_t> path;
        return std::make_pair(path, 0);
    }
}
