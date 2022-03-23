#ifndef __EXPR_HPP___
#define __EXPR_HPP___
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::ostringstream ans;
    ans << num;
    return ans.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    return "(" + l->toString() + " + " + r->toString() + ")";
  }
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};

#endif
