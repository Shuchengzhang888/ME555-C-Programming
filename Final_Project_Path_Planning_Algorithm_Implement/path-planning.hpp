#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <exception>
#include <list>
#include <cmath>
#include <set>


class D_Node{
  /*
  This class is to save the nodes information during Dijkstra Algorithm
  Fields:
    known: sign if we have visited this point
    dist: the shortest distance from start to here
    pre: last node to this node we visit 
  */
  public:
    bool known; 
    double dist;
    double pre;
};
class A_Node{
  /*
  This class is to save the nodes information during A* Algorithm
  Fields:
    known: sign if we have visited this point
    pre: last node to this node we visit
    f: f = g + h choose the lowest f when find the next node 
    g: the shortest distance from start to here
    h: the distance from this point to goal
  */
  public:
    bool known;
    double pre;
    double f;
    double g;
    double h;
};

class Node{
  /*
  This class is to save the nodes information.
  Fields:
    index: node index
    x, y: x, y coordinate
  Methods:
    distance_from(const Node & p): compute the distance from this point to p.
  */
  private:
    size_t index;
    double x;
    double y;
  public:
    Node() : index(), x(), y() {}
    Node(size_t _index, double _x, double _y) : index(_index), x(_x), y(_y) {}
    size_t get_index(){return index;}
    double get_x(){return x;}
    double get_y(){return y;}

    double distance_from(const Node & p) const;
};


class Graph{
  /*
  This class is to save the map information, including edges, obstacles, and path-planing algorithm implement.
  Fields:
    num_node: the number of node
    nodes: a vector to save all nodes information
    adj_list: a vector to save all edges, each row means a node and the map in each row means all edges of this node
    d_node: a vector to save extra node information during Dijkstra
    a_node: a vector to save extra node information during A star
    obs: a 2D vector to save obstacles, each row means an obstacles and the colomn means the component of each obstacle
  Methods:
    add_node(size_t index, double x, double y): add node to nodes
    check_node(): check if the nodes are legal
    add_edge(size_t u, size_t v): add edge to adj_list
    dijkstra(size_t start, size_t goal): implement dijkstra algorithm
    find_path (size_t start, size_t goal, std::string flag): find the path and weight from start to goal
    add_obs(std::vector<size_t>): add obstacle to obs
    make_obs_topair(): make all nodes in each obstacle to pairs which will be used in delete intersect part
    del_obs_inmap(): delete obstacles(nodes and edges) in adj_list
    del_intersect(std::vector<std::pair<size_t, size_t> > couples): find and delete the edges intersecting with obstacles
    apply_obs(): apply obstacles
    a_star(size_t start, size_t goal): implement a* algorithm
  */
  private:
    size_t num_node;
    std::vector<Node> nodes;
    std::vector<std::map<size_t, double> > adj_list;
    std::vector<D_Node> d_node;
    std::vector<A_Node> a_node;
    std::vector<std::vector<size_t> > obs;
  public:
    Graph() : num_node(0), nodes(), adj_list(),obs() {}
    Graph(size_t n) : num_node(n), nodes(), adj_list(), obs() {}
    size_t get_num_nodes(){return num_node;}
    std::vector<Node> get_nodes() {return nodes;}
    std::vector<std::map<size_t, double> > get_adj_list() {return adj_list;}
    std::vector<std::vector<size_t> > get_obs() {return obs;}

    void add_node(size_t index, double x, double y);
    int check_node();
    int add_edge(size_t u, size_t v);

    void dijkstra(size_t start, size_t goal);
    std::pair<std::vector<size_t>, double> find_path (size_t start, size_t goal, std::string flag);

    void add_obs(std::vector<size_t>);
    std::vector<std::pair<size_t, size_t> > make_obs_topair();
    void del_obs_inmap();
    void del_intersect(std::vector<std::pair<size_t, size_t> > couples);
    int apply_obs();

    void a_star(size_t start, size_t goal);

    friend std::ostream & operator<<(std::ostream & s, Graph & g);
};


class Path{
  /*
  This class to read to path and print.
  Fields:
    short_path: the path from start to goal
    dis: the total distance of this path
  */
  private:
    std::vector<size_t> short_path;
    double dis;
  public:
    Path() : short_path(), dis(0) {}
    Path(std::pair<std::vector<size_t>, double> p) : short_path(p.first), dis(p.second) {}

    friend std::ostream & operator<<(std::ostream & s, Path & p);
};




