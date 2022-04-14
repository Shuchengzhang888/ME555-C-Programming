#include "profile.hpp"

#include <iostream>

//provided
Qualities::Qualities(int a_min,
                     int a_max,
                     double h_min,
                     double h_max,
                     int at_min,
                     int at_max,
                     const std::set<std::string> & i_req) :
    age_min(a_min),
    age_max(a_max),
    height_min(h_min),
    height_max(h_max),
    attr_min(at_min),
    attr_max(at_max),
    inter_req(i_req) {
}

//provided
std::ostream & operator<<(std::ostream & os, const Profile & rhs) {
  os << "Username: " << rhs.username << std::endl;
  os << "  Age: " << rhs.age << std::endl;
  os << "  Height: " << rhs.height << std::endl;
  os << "  Attractiveness: " << rhs.attractiveness << std::endl;
  os << "  Interests: ";
  for (std::set<std::string>::iterator it = rhs.interests.begin();
       it != rhs.interests.end();
       ++it) {
    os << *it << " ";
  }
  os << std::endl;
  return os;
}
Profile::Profile(const std::string & un, int a, double h, int at) : username(un), age(a), height(h), attractiveness(at){}

void Profile::addInterest(const std::string & inter){
    //std::set.inset(element) 
    interests.insert(inter);
}

bool Profile::operator==(const Profile & rhs) const{
    if (username == rhs.username && age == rhs.age && height == rhs.height && attractiveness == rhs.attractiveness && interests == rhs.interests){
        return true;
    }
    else{
        return false;
    }
}

bool Profile::isMatch(const Qualities & q) const{
    if(age > q.age_max || age < q.age_min || height > q.height_max || height < q.height_min || attractiveness > q.attr_max || attractiveness < q.attr_min){
        return false;
    }
    std::set<std::string>::iterator iter = q.inter_req.begin();
    while(iter != q.inter_req.end()){
        //set.count: returns the number of elements matching specific key
        //*iter, key
        if(interests.count(*iter) == 0){
            return false;
        }
        ++iter;
    }
    return true;

}
