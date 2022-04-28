#include "path-step3.cpp"

void Graph::a_star(size_t start, size_t goal){
    //Build a set to save the nodes we will visit
    std::set<size_t> open_set;
    //Initialize nodes information during a*
    a_node.resize(nodes.size());
    for(size_t i = 0; i < a_node.size(); i++){
        a_node[i].known = false;
        a_node[i].f = INFINITY;
        a_node[i].g = INFINITY;
        a_node[i].h = nodes[i].distance_from(nodes[goal]);
        //To check if the path exists
        a_node[i].pre = -1;
    }
    //Initialize start node
    a_node[start].pre = 0;
    a_node[start].g = 0;
    a_node[start].f = a_node[start].h;
    open_set.insert(start);

    while(!open_set.empty()){
        std::set<size_t>::iterator it;
        double min = INFINITY;
        size_t cur;
        //Find the node which has the lowest f in open_set, set it to current node
        for(it = open_set.begin(); it != open_set.end(); ++it){
            if(a_node[*it].f < min){
                cur = *it;
                min = a_node[*it].f;
            }
        }
        //If current node is goal, end loop
        if(cur == goal){
            break;
        }
        //Loop the adjacent nodes of current node
        std::map<size_t, double>::iterator iter;
        for(iter = adj_list[cur].begin(); iter != adj_list[cur].end(); ++iter){
            //If the adjacent node is not in open_set and is not visited, put it into open_set and initialize its value
            if(open_set.find(iter->first) == open_set.end() && a_node[iter->first].known == false){
                open_set.insert(iter->first);
                a_node[iter->first].pre = cur;
                a_node[iter->first].g = a_node[cur].g + iter->second;
                a_node[iter->first].f = a_node[iter->first].g + a_node[iter->first].h;
            }
            //If the adjacent node is in open_set, check if it has better f through the current node
            else{
                double add_g = a_node[cur].g + iter->second;
                if(add_g < a_node[iter->first].g){
                    a_node[iter->first].pre = cur;
                    a_node[iter->first].g = add_g;
                    a_node[iter->first].f = a_node[iter->first].g + a_node[iter->first].h;
                }
            }
        }
        //Set the current node to be visited, and delete it from open_set
        a_node[cur].known = true;
        open_set.erase(cur);
    }
}
