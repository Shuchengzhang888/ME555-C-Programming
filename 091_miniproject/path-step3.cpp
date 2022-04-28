#include "path-step2.cpp"

class no_obs : public std::exception{
  public:
    const char * what() const throw(){
        return "No Obstacles.\n";
    }
};


void Graph::add_obs(std::vector<size_t> ob){
    obs.push_back(ob);
}


std::vector<std::pair<size_t, size_t> >  Graph::make_obs_topair(){
    std::vector<std::pair<size_t, size_t> > couples;
    std::vector<std::vector<size_t> >::iterator it;
    std::vector<size_t>::iterator iter;
    std::vector<size_t>::iterator iterr;
    //Loop every node in each obstacle and find all possible combinations of two nodes
    // and save them to couples
    for(it = obs.begin(); it != obs.end(); ++it){
        for(iter = it->begin(); iter != it->end(); ++iter){
            size_t s = *iter;
            for(iterr = iter + 1; iterr != it->end(); ++iterr){
                couples.push_back(std::make_pair(s, *iterr));
            }
        }
    }
    return couples;
}


void Graph::del_obs_inmap(){
    std::vector<std::vector<size_t> >::iterator it_d;
    std::vector<size_t>::iterator iter_d;
    std::vector<std::map<size_t, double> >::iterator iterr_d;
    std::map<size_t, double>::iterator iterrr_d;
    //Delete all obstacle-related edges in map
    //Do not delete obstacle nodes here, if we delete all edges of the node, it means we cannot access the node
    for(it_d = obs.begin(); it_d != obs.end(); ++it_d){
        for(iter_d = it_d->begin(); iter_d != it_d->end(); ++iter_d){
            size_t j = 0;
            for(iterr_d = adj_list.begin(); iterr_d != adj_list.end(); ++iterr_d, j++){
                //If the node is obstacle, delete all its edges
                if(*iter_d == j){
                    iterr_d->clear();
                    continue;
                }
                //If not, delete its obstacle-related edges
                for(iterrr_d = iterr_d->begin(); iterrr_d != iterr_d->end();){
                    if(*iter_d == iterrr_d->first){
                        std::map<size_t, double>::iterator temp = iterrr_d;
                        ++iterrr_d;
                        iterr_d->erase(temp);
                        continue;
                    }
                    ++iterrr_d;
                }
            }
        }
    }
}

void Graph::del_intersect(std::vector<std::pair<size_t, size_t> > couples){
    std::vector<std::pair<size_t, size_t> >::iterator it_c;
    std::vector<std::map<size_t, double> >::iterator iter_c;
    std::map<size_t, double>::iterator iterr_c;
    for(it_c = couples.begin(); it_c != couples.end(); ++it_c){
        //Loop each obstacle pair in couples and set them to Node n1 n2
        Node n1(it_c->first, nodes[it_c->first].get_x(), nodes[it_c->first].get_y());
        Node n2(it_c->second, nodes[it_c->second].get_x(), nodes[it_c->second].get_y());
        size_t i = 0;
        for(iter_c = adj_list.begin(); iter_c != adj_list.end(); ++iter_c){
            //Loop each edge in adj_list and set two nodes in one edge to n3 n4
            Node n3(i, nodes[i].get_x(), nodes[i].get_y());
            i++;
            for(iterr_c = iter_c->begin(); iterr_c != iter_c->end();){
                Node n4(iterr_c->first, nodes[iterr_c->first].get_x(), nodes[iterr_c->first].get_y());
                //Compute intersect
                double z1 = (n2.get_y() - n1.get_y()) * (n3.get_x() - n2.get_x()) - (n2.get_x() - n1.get_x()) * (n3.get_y() - n2.get_y());
                double z2 = (n2.get_y() - n1.get_y()) * (n4.get_x() - n2.get_x()) - (n2.get_x() - n1.get_x()) * (n4.get_y() - n2.get_y());
                double z3 = (n4.get_y() - n3.get_y()) * (n1.get_x() - n4.get_x()) - (n4.get_x() - n3.get_x()) * (n1.get_y() - n4.get_y());
                double z4 = (n4.get_y() - n3.get_y()) * (n2.get_x() - n4.get_x()) - (n4.get_x() - n3.get_x()) * (n2.get_y() - n4.get_y());
                //If two z have different signs, their product is negative
                //If z1 and z2, z3 and z4 have different signs, mean they intersect, delete the edge
                if(z1 * z2 < 0 && z3 * z4 < 0){
                    std::map<size_t, double>::iterator temp = iterr_c;
                    ++iterr_c;
                    iter_c->erase(temp);
                    continue;
                }
                ++iterr_c;
            }
        }
    }
}

int Graph::apply_obs(){
    try{
        //Check if there are obstacles
        if(obs.size() == 0){
            throw no_obs();
        }
        //Delete obstacles in map
        this->del_obs_inmap();
        //Make the obstacles to pairs 
        std::vector<std::pair<size_t, size_t> > couples = this->make_obs_topair();
        //Delete those edges intersecting with obstacle edges
        this->del_intersect(couples);
        return EXIT_SUCCESS;
    }
    catch (no_obs & e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

}


int read_obs(std::ifstream & f, Graph & g){
    /*
    This function is to read obstacle file and save.
    Input:
      f: the input file
      g: map information
    */
    try{
        std::string line;
        std::string flag;
        std::string space = " ";
        std::vector<std::vector<size_t> > obs_list;
        while(std::getline(f, line)){
            //Skip empty line
            if(line == ""){ 
                continue;
            }
            if(line == "$obstacles"){
                flag = "$obstacles";
                continue;
            }

            if(flag == "$obstacles"){
                std::string::iterator it;
                std::vector<size_t> ob;
                for(it = line.begin(); it != line.end(); ++it){
                    //Check if the input has letter
                    if(isalpha(*it)){
                        throw invalid_input();
                    }
                    if(it == line.begin()){
                        ob.push_back(atoi((&*it)));
                    }
                    if(!isdigit(*it)){
                        ob.push_back(atoi((&*(it + 1))));
                    }
                }
                //Add obstacle to obs
                g.add_obs(ob);
            }
        }
        //Check if there is "$obstacles" in file
        if(flag != "$obstacles"){
            throw invalid_input();
        }
        return EXIT_SUCCESS;
    }
    catch (invalid_input & e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
