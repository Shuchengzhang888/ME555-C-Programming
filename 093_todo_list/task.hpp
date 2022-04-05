#include <list>
#include <string>

typedef std::string task_t;

class TaskDep {
 private:
  const task_t task;
  std::list<task_t> pres;

 public:
  // write these
  TaskDep(const task_t & t);
  const task_t & getTask() const;
  void addPredecessor(const task_t & t);
  std::list<task_t> getPredecessors() const;
};
