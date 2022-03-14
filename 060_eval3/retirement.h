#ifndef __RETIREMENT_H__
#define __RETIREMENT_H__

#include <stdlib.h>

struct date_tag {
  unsigned year;
  unsigned month;
};
typedef struct date_tag date_t;

// struct to hold array of dates and cumulative investments
// (hint: can be used for any investment strategy)
struct ret_portfolio_tag {
  date_t * dates;
  double * cum_invest;
  size_t n;
};
typedef struct ret_portfolio_tag ret_portfolio_t;

struct ror_tag {
  // WRITE ME
  date_t dates;
  double interest;
};
typedef struct ror_tag ror_t;

struct ror_arr_tag {
  // WRITE ME
  ror_t * ror;
  size_t len;
};
typedef struct ror_arr_tag ror_arr_t;
#endif
