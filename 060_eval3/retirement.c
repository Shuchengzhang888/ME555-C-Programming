#include "retirement.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


#define SP 2
#define BOND 1
#define monthly_deposit 100
#define annual_increasing_deposit 0.025
#define annual_decreasing_rate 0.02
#define file_name "portfolio.csv"

size_t check_file(const char * name){
  /*
  This function is to test if the file is sp or bond.
  Input:
    name: file name we want to read from command line
  Output:
    count: show if the file is sp or bond
  */
  FILE * f = fopen(name, "r");
  if (f == NULL) {
    fprintf(stderr,"Cannot read the input file.\n");
    exit(EXIT_FAILURE);
  }
  size_t sz = 0;
  char * line = NULL;
  //Jump first line
  getline(&line, &sz, f);
  getline(&line, &sz, f);
  //Count the ',' in a line; if there are 2 ',', the file is sp; if there is 1 ',', the file is bond 
  size_t count = 0;
  for(size_t i = 0; line[i] != '\n'; i++){
    if (line[i] == ','){
      count++;
    }
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr,"Cannot close the input file.\n");
    exit(EXIT_FAILURE);
  }
  return count;
}

void check_year(char * text){
  /*
  This function is to check if the input year is legal.
  Input: 
    text: each line starts with year
  */
  size_t i = 0;
  while(text[i] != '.'){
    //Check if the every input digit is number. 
    if(!isdigit(text[i])){
      fprintf(stderr,"Illegal input year in csv.\n");
      exit(EXIT_FAILURE);
    }
    //Make sure it does not start with 0.
    if(i == 0 && text[i] == '0'){
      fprintf(stderr,"Illegal input year in csv.\n");
      exit(EXIT_FAILURE);
    }
    i++;
  }
  //Make sure it has 4 digits.
  if(i != 4){
    fprintf(stderr,"Illegal input year in csv.\n");
    exit(EXIT_FAILURE);
  }
}

void check_month(char * text){
  /*
  This function is to check if the input month is legal.
  Input: 
    text: each line starts with month
  */
  size_t i = 0;
  while(text[i] != ','){
    //Check if the every input digit is number. 
    if(!isdigit(text[i])){
      fprintf(stderr,"Illegal input month in csv.\n");
      exit(EXIT_FAILURE);
    }
    i++;
  }
  //Make sure it has 2 digits.
  if(i != 2){
    fprintf(stderr,"Illegal input month in csv.\n");
    exit(EXIT_FAILURE);
  }
}

void check_level(char * text){
  /*
  This function is to check if the input level(sp) is legal.
  Input:
    text: each line starts with level
  */
  //Make sure it does not start with 0.
  if(text[0] == '0'){
    if(text[1] != '.'){
      fprintf(stderr,"Illegal input level in csv.\n");
      exit(EXIT_FAILURE);
    }
  }
  size_t i = 0;
  while(text[i] != ','){
    //Check if the every input digit is number or '.'. 
    if(!(isdigit(text[i]) || text[i] == '.')){
      fprintf(stderr,"Illegal input level in csv.\n");
      exit(EXIT_FAILURE);
    }
    i++;
  }
}

void check_last_value(char * text){
  /*
  This function is to check if the last input(dividend in sp & price in bond) is legal.
  Input:
    text: each line starts with last value
  */
  //Make sure it does not start with 0.
  if(text[0] == '0'){
    if(text[1] != '.'){
      fprintf(stderr,"Illegal input last value each line in csv.\n");
      exit(EXIT_FAILURE);
    }
  }
  size_t i = 0;
  while(text[i] != '\r' && text[i] != '\0'){
    //Check if the every input digit is number or '.'. 
    if(!(isdigit(text[i]) || text[i] == '.')){
      fprintf(stderr,"Illegal input last value each line in csv.\n");
      exit(EXIT_FAILURE);
    }
    i++;
  }
}

double save_sp_data(char * line, ror_t * ror, double index_level){
  /*
  This function is to convert string(sp) in line to number and save them into array.
  Input:
    line: each data line in document
    ror: a struct to save date and interest
    index_level: the level of last month
  Output:
    new_index_level: the level of this month
  */
  //Find the start address of each data (year, month, level, dividend)
  if (line == NULL){
    fprintf(stderr,"There is no line in csv.");
    exit(EXIT_FAILURE);
  }
  char * date_dot = strchr(line, '.');
  if (date_dot == NULL){
    fprintf(stderr,"Illegal input date in csv.");
    exit(EXIT_FAILURE);
  }
  char * first_comma = strchr(line, ',');
  if (first_comma == NULL){
    fprintf(stderr,"There is no comma.");
    exit(EXIT_FAILURE);
  }
  char * second_comma = strchr(first_comma + 1, ',');
  if (second_comma == NULL){
    fprintf(stderr,"There is no second comma.");
    exit(EXIT_FAILURE);
  }
  //Convert string to number and save them in ror
  char * endptr;
  check_year(line);
  ror->dates.year = strtoul(line, &endptr, 10);
  check_month(date_dot + 1);
  ror->dates.month = strtoul(date_dot + 1, &endptr, 10);
  //Make sure month value is legal
  assert(ror->dates.month > 0 && ror->dates.month < 13);
  check_level(first_comma + 1);
  double new_index_level = strtod(first_comma + 1, &endptr);
  check_last_value(second_comma + 1);
  double dividend = strtod(second_comma + 1, &endptr);
  //Calculate the interest
  ror->interest = new_index_level / index_level -1 + dividend / 12 / new_index_level;
  return new_index_level;
}

void save_bond_data(char * line, ror_t * ror){
  /*
  This function is to convert string(bond) in line to number and save them into array.
  Input:
    line: each data line in document
    ror: a struct to save date and interest
  */
  //Find the start address of each data (year, month, price)
  if (line == NULL){
    fprintf(stderr,"There is no line in csv.");
    exit(EXIT_FAILURE);
  }
  char * date_dot = strchr(line, '.');
  if (date_dot == NULL){
    fprintf(stderr,"Illegal input date in csv.");
    exit(EXIT_FAILURE);
  }
  char * first_comma = strchr(line, ',');
  if (first_comma == NULL){
    fprintf(stderr,"There is no comma.");
    exit(EXIT_FAILURE);
  }
  //Convert string to number and save them in ror
  char * endptr;
  check_year(line);
  ror->dates.year = strtoul(line, &endptr, 10);
  check_month(date_dot + 1);
  ror->dates.month = strtoul(date_dot + 1, &endptr, 10);
  //Make sure month value is legal
  assert(ror->dates.month > 0 && ror->dates.month < 13);
  check_last_value(first_comma + 1);
  double bond = strtod(first_comma + 1, &endptr);
  //Calculate the interest
  ror->interest = (bond / 12) / 100;
}


ror_arr_t * read_data(FILE * f, size_t index){
  /*
  This function is to read data from file, allocate memory to them and save all of them to a array struct.
  Input:
    f: file name we want to read
    index: show if the file is sp or bond
  Output:
    ror_arr: an array struct including all data(the data from each line will be saved in a 'ror' struct)
  */
  //Allocate a space for the array struct
  ror_arr_t * ror_arr = malloc (sizeof(*ror_arr));
  ror_arr->ror = NULL;
  ror_arr->len = 0;
  size_t sz = 0;
  char * line = NULL;
  double index_level = 0;
  //Jump the first line (not include data)
  getline(&line, &sz, f);
  //Get line from file, and save into a 'ror' struct in 'ror_arr' struct
  while(getline(&line, &sz, f) > 2){
    ror_arr->len ++;
    //Reallocate space for 'ror' according to the number of line
    ror_arr->ror = realloc(ror_arr->ror, ror_arr->len * sizeof(* ror_arr->ror));
    //Choose related method to save data according to file type
    if(index == SP){
      index_level = save_sp_data(line, &ror_arr->ror[ror_arr->len - 1], index_level);
    }
    else{
      save_bond_data(line, &ror_arr->ror[ror_arr->len - 1]);
    }
  }
  free(line);
  //Make sure there is content in file
  if(ror_arr->len == 0){
    fprintf(stderr,"There is nothing in the input file.\n");
    exit(EXIT_FAILURE);
  }
  return ror_arr;
}

ror_arr_t * read_file(const char * name, size_t index){
  /*
  This function is to open, read and close file.
  Input:
    name: file name we want to read from command line
    index: show if the file is sp or bond
  Output:
    ror_arr: an array struct including all data 
  */
  //Check and open file 
  FILE * f = fopen(name, "r");
  if (f == NULL) {
    fprintf(stderr,"Cannot read the input file.\n");
    exit(EXIT_FAILURE);
  }
  //Read file and save data
  ror_arr_t * ror_arr = read_data(f, index);
  //Check and close file
  if (fclose(f) != 0) {
    fprintf(stderr,"Cannot close the input file.\n");
    exit(EXIT_FAILURE);
  }
  return ror_arr;
}

void check_array_date(ror_arr_t * array){
  /*
  This function is to make sure every date in array is consecutive.
  Input:
    array: an array struct including all data of an investment
  */
  for(int i = 0; i < array->len - 1; i++){
    if(array->ror[i].dates.month != 12){
      if ((array->ror[i].dates.month + 1) != array->ror[i+1].dates.month){
        fprintf(stderr,"Non-consecutive month.\n");
        exit(EXIT_FAILURE);
      }
      if (array->ror[i].dates.year != array->ror[i+1].dates.year){
        fprintf(stderr,"Non-consecutive year.\n");
        exit(EXIT_FAILURE);
      }
    }
    else{
      if (array->ror[i+1].dates.month != 1){
        fprintf(stderr,"Non-consecutive month.\n");
        exit(EXIT_FAILURE);
      }
      if ((array->ror[i].dates.year + 1) != array->ror[i+1].dates.year){
        fprintf(stderr,"Non-consecutive year.\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

date_t read_date(char * str){
  /*
  This function is to read date from command line.
  Input:
    str: a command line express the start or end date
  Output:
    date: a struct including year and month
  */
  date_t date;
  //Find delimiter between year and month
  char * date_dot = strchr(str, '.');
  if (date_dot == NULL){
    fprintf(stderr,"Illegal input date in csv.");
    exit(EXIT_FAILURE);
  }
  //Convert year and month from string to number
  char * endptr;
  date.year = strtoul(str, &endptr, 10);
  date.month = strtoul(date_dot + 1, &endptr, 10);
  return date;
}

int find_date(ror_arr_t * array, date_t date){
  /*
  This function is to find start or end date in the data array.
  Input:
    sp_array: an array struct including all data of sp
    sta_date: start calcualte date from command line
  Output:
    i: order number of the date in array struct
  */
  for(int i = 0; i < array->len; i++){
    if (array->ror[i].dates.year == date.year && array->ror[i].dates.month == date.month){
      return i;
    }
  }
  fprintf(stderr,"Start or end date is illegal.\n");
  exit(EXIT_FAILURE);
}

ret_portfolio_t * cal_invest(ror_arr_t * array, date_t sta_date, date_t end_date, double deposit, double increase){
  /*
  This function is to calculate equities and bonds investment result and save them to an array struct.
  Input:
    array: An array struct including all data of dates and interest
    sta_date: start investment date
    end_date: end investment date
    deposit: monthly deposit
    increase: monthly deposit increasment
  Output:
    ret_array: an array struct including dates and accumulated investment of each month
  */
  //Find start and end date of investment and check if them are legal
  int i = find_date(array, sta_date) + 1;
  int j = find_date(array, end_date);
  if (i > j){
    fprintf(stderr,"Start date is later than end date.\n");
    exit(EXIT_FAILURE);
  }
  //Build an array struct to save monthly accumulated investment
  ret_portfolio_t * ret_array = malloc (sizeof(*ret_array));
  ret_array->cum_invest = malloc (sizeof(*ret_array->cum_invest));
  ret_array->dates = malloc (sizeof(*ret_array->dates));
  ret_array->n = 0;
  double money = 0;
  //Calcualte the investment results
  while (i <= j){
    ret_array->n ++;
    ret_array->dates = realloc (ret_array->dates, ret_array->n * sizeof(*ret_array->dates));
    ret_array->cum_invest = realloc (ret_array->cum_invest, ret_array->n * sizeof(*ret_array->cum_invest));
    ret_array->dates[ret_array->n - 1].year = array->ror[i].dates.year;
    ret_array->dates[ret_array->n - 1].month = array->ror[i].dates.month;
    //Increase monthly deposit in every January
    if(ret_array->n > 1 && ret_array->dates[ret_array->n - 1].month == 1){
      deposit *= (1 + increase);
    }
    //Calculate monthly accumulated investment
    money = money * (1 + array->ror[i].interest) + deposit;
    ret_array->cum_invest[ret_array->n - 1] = money;
    i++;
  }
  return ret_array;
}

ret_portfolio_t * cal_invest_lifecycle(ror_arr_t * sp_array, ror_arr_t * bond_array, date_t sta_date, date_t end_date, double deposit, double increase, double decrease){
  /*
  This function is to calculate lifecycle investment result and save them to an array struct.
  Input:
    sp_array: An array struct including all data of sp
    bond_array: An array struct including all data of bond
    sta_date: start investment date
    end_date: end investment date
    deposit: monthly deposit
    increase: monthly deposit increasement
    decrease: lifecycle allocation decreasement
  Output:
    ret_array: an array struct including dates and accumulated investment of each month
  */
  //Find start and end date of investment and check if them are legal
  int i = find_date(bond_array, sta_date) + 1;
  int j = find_date(bond_array, end_date);
  if (i > j){
    fprintf(stderr,"Start date is later than end date.\n");
    exit(EXIT_FAILURE);
  }
  //Build an array struct to save monthly accumulated investment
  ret_portfolio_t * ret_array = malloc (sizeof(*ret_array));
  ret_array->cum_invest = malloc (sizeof(*ret_array->cum_invest));
  ret_array->dates = malloc (sizeof(*ret_array->dates));
  ret_array->n = 0;
  double money = 0;
  double percent = 1;
  //Calcualte the investment results
  while (i <= j){
    ret_array->n ++;
    ret_array->dates = realloc (ret_array->dates, ret_array->n * sizeof(*ret_array->dates));
    ret_array->cum_invest = realloc (ret_array->cum_invest, ret_array->n * sizeof(*ret_array->cum_invest));
    ret_array->dates[ret_array->n - 1].year = sp_array->ror[i].dates.year;
    ret_array->dates[ret_array->n - 1].month = sp_array->ror[i].dates.month;
    //Increase monthly deposit and decrease allocation in every January
    if(ret_array->n > 1 && ret_array->dates[ret_array->n - 1].month == 1){
      deposit *= (1 + increase);
      percent -= decrease;
    }
    //Calculate monthly accumulated investment
    money = money * (1 + sp_array->ror[i].interest) * percent + money * (1 + bond_array->ror[i].interest) * (1 - percent) + deposit;
    ret_array->cum_invest[ret_array->n - 1] = money;
    i++;
  }
  return ret_array;
}

void write_file(ret_portfolio_t * equities, ret_portfolio_t * bonds, ret_portfolio_t * lifecycles){
  /*
  This function is to write investment results into file.
  Input:
    equities: monthly accumulated investment of sp method
    bonds: monthly accumulated investment of bonds method
    lifecycles: monthly accumulated investment of lifecycles method
  */
  FILE * f = fopen(file_name, "w");
  //Make sure those three arraries have same length size
  assert(equities->n == bonds->n && bonds->n == lifecycles->n);
  //Write results into file
  for (int i = 0; i < equities->n; i++){
    fprintf(f, "%u.%02u,%.2f,%.2f,%.2f\n", equities->dates[i].year, equities->dates[i].month, equities->cum_invest[i], bonds->cum_invest[i], lifecycles->cum_invest[i]);
  }
  if (fclose(f) != 0) {
    fprintf(stderr,"Cannot close the output file.\n");
    exit(EXIT_FAILURE);
  }
}

void free_interest_array(ror_arr_t * sp_array, ror_arr_t * bond_array){
  /*
  This function is to free memery of investment information.
  Input:
    sp_array: An array struct including all data of sp
    bond_array: An array struct including all data of bond
  */
  free(sp_array->ror);
  free(sp_array);
  free(bond_array->ror);
  free(bond_array);
}

void free_results(ret_portfolio_t * equities_results, ret_portfolio_t * bonds_results, ret_portfolio_t * lifecycle_results){
  /*
  This function is to free memery of investment result.
  Input:
    equities: monthly accumulated investment of sp method
    bonds: monthly accumulated investment of bonds method
    lifecycles: monthly accumulated investment of lifecycles method
  */
  free(equities_results->dates);
  free(bonds_results->dates);
  free(lifecycle_results->dates);
  free(equities_results->cum_invest);
  free(bonds_results->cum_invest);
  free(lifecycle_results->cum_invest);
  free(equities_results);
  free(bonds_results);
  free(lifecycle_results);
}

int main(int argc, char ** argv) {
  //Make sure we have 5 command line arguments
  if (argc != 5) {
    fprintf(stderr,"Command line arguments are not enough.\n");
    exit(EXIT_FAILURE);
  }
  //Check CSV file type (sp or bonds), read and save data from it, and check data's legality
  size_t i = 1;
  ror_arr_t * sp_array = NULL;
  ror_arr_t * bond_array = NULL;
  while(i == 1 || i == 2){
    size_t index = check_file(argv[i]);
    if (index == SP){
      sp_array = read_file(argv[i], SP);
      check_array_date(sp_array);
    }
    else{
      bond_array = read_file(argv[i], BOND);
      check_array_date(bond_array);
    }
    i++;
  }
  if (sp_array == NULL || bond_array == NULL){
    fprintf(stderr,"Illegal input in CSV.\n");
    exit(EXIT_FAILURE);
  }
  //Read start and end investment date
  date_t sta_date = read_date(argv[3]);
  date_t end_date = read_date(argv[4]);
  //Calculate investment results
  ret_portfolio_t * equities_results = cal_invest(sp_array, sta_date, end_date, monthly_deposit, annual_increasing_deposit);
  ret_portfolio_t * bonds_results = cal_invest(bond_array, sta_date, end_date, monthly_deposit, annual_increasing_deposit);
  ret_portfolio_t * lifecycle_results = cal_invest_lifecycle(sp_array, bond_array, sta_date, end_date, monthly_deposit, annual_increasing_deposit, annual_decreasing_rate);
  //Write results to file
  write_file(equities_results, bonds_results, lifecycle_results);
  //Free memery
  free_interest_array(sp_array, bond_array);
  free_results(equities_results, bonds_results, lifecycle_results);
  return EXIT_SUCCESS;
}
