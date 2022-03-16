#include "retirement.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
// WRITE ME
double save_data(char * line, ror_t * ror, size_t index, double index_level){
  printf("%s",line);
  if(index == 1){
    //sp
    if (line == NULL){
      fprintf(stderr,"There is no line.");
      exit(EXIT_FAILURE);
    }
    char * date_dot = strchr(line, '.');
    if (date_dot == NULL){
      fprintf(stderr,"Illegal input.");
      exit(EXIT_FAILURE);
    }
    char * first_comma = strchr(line, ',');
    if (first_comma == NULL){
      fprintf(stderr,"There is no comma.");
      exit(EXIT_FAILURE);
    }
    //printf("%d",first_colon);
    char * second_comma = strchr(first_comma + 1, ',');
    //printf("%s",second_colon);
    if (second_comma == NULL){
      fprintf(stderr,"There is no second comma.");
      exit(EXIT_FAILURE);
    }
    char * endptr;
    ror->dates.year = strtoul(line, &endptr, 10);
    assert(ror->dates.year > 1000 && ror->dates.year < 10000);
    ror->dates.month = strtoul(date_dot + 1, &endptr, 10);
    assert(ror->dates.month > 0 && ror->dates.month < 13);
    double new_index_level = strtod(first_comma + 1, &endptr);
    assert(new_index_level > 0); 
    double dividend = strtod(second_comma + 1, &endptr);
    assert(dividend > 0);
    ror->interest = (new_index_level / index_level -1 + dividend / 12 / new_index_level);

    return new_index_level;
  }


  if(index == 2){
    //bond
    if (line == NULL){
      fprintf(stderr,"There is no line.");
      exit(EXIT_FAILURE);
    }
    char * date_dot = strchr(line, '.');
    if (date_dot == NULL){
      fprintf(stderr,"Illegal input.");
      exit(EXIT_FAILURE);
    }
    char * first_comma = strchr(line, ',');
    if (first_comma == NULL){
      fprintf(stderr,"There is no comma.");
      exit(EXIT_FAILURE);
    }
    char * endptr;
    ror->dates.year = strtoul(line, &endptr, 10);
    assert(ror->dates.year > 1000 && ror->dates.year < 10000);
    ror->dates.month = strtoul(date_dot + 1, &endptr, 10);
    assert(ror->dates.month > 0 && ror->dates.month < 13);
    double bond = strtod(first_comma + 1, &endptr);
    assert(bond > 0);
    ror->interest = (bond / 12) / 100;
    return 0; 
  }

  exit(EXIT_FAILURE);
}


ror_arr_t * read_data(FILE * f, size_t index){
  ror_arr_t * ror_arr = malloc (sizeof(*ror_arr));
  ror_arr->ror = NULL;
  ror_arr->len = 0;

  size_t sz = 0;
  char * line = NULL;
  double index_level = 0;
  //jump first line
  getline(&line, &sz, f);
  //line = NULL;
  //free(line);
  while( getline(&line, &sz, f) > 2){
    ror_arr->len ++;
    ror_arr->ror = realloc(ror_arr->ror, ror_arr->len * sizeof(* ror_arr->ror));
    index_level = save_data(line, &ror_arr->ror[ror_arr->len - 1], index, index_level);
    //line = NULL;
  }
  free(line);

  if(ror_arr->len == 0){
    fprintf(stderr,"There is nothing in the input file.\n");
    exit(EXIT_FAILURE);
  }
  return ror_arr;
}

ror_arr_t * read_file(const char * file_name, size_t index){
  FILE * f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr,"Cannot read the input file.\n");
    exit(EXIT_FAILURE);
  }
  ror_arr_t * ror_arr = read_data(f, index);
  if (fclose(f) != 0) {
    fprintf(stderr,"Cannot close the input file.\n");
    exit(EXIT_FAILURE);
  }
  return ror_arr;
}


int find_sta(ror_arr_t * sp_array, date_t sta_date){
  int i = 0;
  while(i < sp_array->len){
    if (sp_array->ror[i].dates.year == sta_date.year && sp_array->ror[i].dates.month == sta_date.month){
      return i + 1;
    }
    i++;
  }
  fprintf(stderr,"Start date is illegal.\n");
  exit(EXIT_FAILURE);
}
int find_end(ror_arr_t * sp_array, date_t end_date){
  int j = 0;
  while(j < sp_array->len){
    if (sp_array->ror[j].dates.year == end_date.year && sp_array->ror[j].dates.month == end_date.month){
      return j;
    }
    j++;
  }
  fprintf(stderr,"End date is illegal.\n");
  exit(EXIT_FAILURE);
}

ret_portfolio_t * cal_invest_equities(ror_arr_t * sp_array, date_t sta_date, date_t end_date, double deposit, double increase){
  int i = find_sta(sp_array, sta_date);
  int j = find_end(sp_array, end_date);
  if (i > j){
    fprintf(stderr,"Illegal date.\n");
    exit(EXIT_FAILURE);
  }

  ret_portfolio_t * ret_array = malloc (sizeof(*ret_array));

  ret_array->cum_invest = malloc (sizeof(*ret_array->cum_invest));
  ret_array->dates = malloc (sizeof(*ret_array->dates));
  ret_array->n = 0;
  double money = 0;

  while (i <= j){
    ret_array->n ++;
    ret_array->dates = realloc (ret_array->dates, ret_array->n * sizeof(*ret_array->dates));
    ret_array->cum_invest = realloc (ret_array->cum_invest, ret_array->n * sizeof(*ret_array->cum_invest));
    
    
    ret_array->dates[ret_array->n - 1].year = sp_array->ror[i].dates.year;
    ret_array->dates[ret_array->n - 1].month = sp_array->ror[i].dates.month;
    //printf("%d, %d ",ret_array->dates[i].year,ret_array->dates[i].month);
    if(ret_array->n > 1 && ret_array->dates[ret_array->n - 1].month == 1){
      deposit *= (1 + increase);
    }

    money = money * (1 + sp_array->ror[i].interest) + deposit;
    ret_array->cum_invest[ret_array->n - 1] = money;
    //printf("%f\n", ret_array->cum_invest[i]);
    i++;
  }

  return ret_array;
}

ret_portfolio_t * cal_invest_bonds(ror_arr_t * bond_array, date_t sta_date, date_t end_date, double deposit, double increase){
  int i = find_sta(bond_array, sta_date);
  int j = find_end(bond_array, end_date);
  if (i > j){
    fprintf(stderr,"Illegal date.\n");
    exit(EXIT_FAILURE);
  }

  ret_portfolio_t * ret_array = malloc (sizeof(*ret_array));

  ret_array->cum_invest = malloc (sizeof(*ret_array->cum_invest));
  ret_array->dates = malloc (sizeof(*ret_array->dates));
  ret_array->n = 0;
  double money = 0;
  while (i <= j){
    ret_array->n ++;
    ret_array->dates = realloc (ret_array->dates, ret_array->n * sizeof(*ret_array->dates));
    ret_array->cum_invest = realloc (ret_array->cum_invest, ret_array->n * sizeof(*ret_array->cum_invest));
    
    
    ret_array->dates[ret_array->n - 1].year = bond_array->ror[i].dates.year;
    ret_array->dates[ret_array->n - 1].month = bond_array->ror[i].dates.month;
    //printf("%d, %d ",ret_array->dates[i].year,ret_array->dates[i].month);
    if(ret_array->n > 1 && ret_array->dates[ret_array->n - 1].month == 1){
      deposit *= (1 + increase);
    }

    money = money * (1 + bond_array->ror[i].interest) + deposit;
    ret_array->cum_invest[ret_array->n - 1] = money;
    //printf("%f\n", ret_array->cum_invest[i]);
    i++;
  }

  return ret_array;
}

ret_portfolio_t * cal_invest_lifecycle(ror_arr_t * sp_array, ror_arr_t * bond_array, date_t sta_date, date_t end_date, double deposit, double increase, double decrease){
int i = find_sta(bond_array, sta_date);
  int j = find_end(bond_array, end_date);
  if (i > j){
    fprintf(stderr,"Illegal date.\n");
    exit(EXIT_FAILURE);
  }

  ret_portfolio_t * ret_array = malloc (sizeof(*ret_array));

  ret_array->cum_invest = malloc (sizeof(*ret_array->cum_invest));
  ret_array->dates = malloc (sizeof(*ret_array->dates));
  ret_array->n = 0;
  double money = 0;
  double percent = 1;
  while (i <= j){
    ret_array->n ++;
    ret_array->dates = realloc (ret_array->dates, ret_array->n * sizeof(*ret_array->dates));
    ret_array->cum_invest = realloc (ret_array->cum_invest, ret_array->n * sizeof(*ret_array->cum_invest));
    
    
    ret_array->dates[ret_array->n - 1].year = sp_array->ror[i].dates.year;
    ret_array->dates[ret_array->n - 1].month = sp_array->ror[i].dates.month;
    //printf("%d, %d ",ret_array->dates[i].year,ret_array->dates[i].month);
    if(ret_array->n > 1 && ret_array->dates[ret_array->n - 1].month == 1){
      deposit *= (1 + increase);
      percent -= decrease;
    }

    money = money * (1 + sp_array->ror[i].interest) * percent + money * (1 + bond_array->ror[i].interest) * (1 - percent) + deposit;
    ret_array->cum_invest[ret_array->n - 1] = money;
    //printf("%f\n", ret_array->cum_invest[i]);
    i++;
  }

  return ret_array;
}

date_t read_date(char * str){
  date_t date;
  char * date_dot = strchr(str, '.');
  if (date_dot == NULL){
    fprintf(stderr,"Illegal input.");
    exit(EXIT_FAILURE);
  }
  char * endptr;
  date.year = strtoul(str, &endptr, 10);
  date.month = strtoul(date_dot + 1, &endptr, 10);
  return date;
}

void write_file(ret_portfolio_t * equities, ret_portfolio_t * bonds, ret_portfolio_t * lifecycle, char * file_name){
  FILE * f = fopen(file_name, "w");
  assert(equities->n == bonds->n && bonds->n == lifecycle->n);
  for (int i = 0; i < equities->n; i++){
    fprintf(f, "%u.%02u,%.2f,%.2f,%.2f\n", equities->dates[i].year, equities->dates[i].month, equities->cum_invest[i], bonds->cum_invest[i], lifecycle->cum_invest[i]);
  }
  if (fclose(f) != 0) {
    fprintf(stderr,"Cannot close the input file.\n");
    exit(EXIT_FAILURE);
  }
}
void free_interest_array(ror_arr_t * sp_array, ror_arr_t * bond_array){
  for(int i = sp_array->len; i > 0; i--){
    //free(&(sp_array[i]));
  }
  free(sp_array->ror);
  free(sp_array);
  for(int i = bond_array->len; i > 0; i--){
    //free(bond_array->ror + i);
  }
  free(bond_array->ror);
  free(bond_array);
}

void free_results(ret_portfolio_t * equities_results, ret_portfolio_t * bonds_results, ret_portfolio_t * lifecycle_results){
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
  if (argc != 5) {
    fprintf(stderr,"Command line arguments are not enough.\n");
    exit(EXIT_FAILURE);
  }
  
  ror_arr_t * sp_array = read_file(argv[1], 1);
  ror_arr_t * bond_array = read_file(argv[2], 2);
  date_t sta_date = read_date(argv[3]);
  date_t end_date = read_date(argv[4]);
  ret_portfolio_t * equities_results = cal_invest_equities(sp_array, sta_date, end_date, 100, 0.025);
  ret_portfolio_t * bonds_results = cal_invest_bonds(bond_array, sta_date, end_date, 100, 0.025);
  ret_portfolio_t * lifecycle_results = cal_invest_lifecycle(sp_array, bond_array, sta_date, end_date, 100, 0.025, 0.02);
  // printf("\n");
  //   for (int i = 0; i < cal_equities_results->n; i++){
  //   printf("%d, %d , %f\n", cal_equities_results->dates[i].year, cal_equities_results->dates[i].month, cal_equities_results->cum_invest[i]);
  // }
  // for (int i = 0; i < cal_bonds_results->n; i++){
  //   printf("%d, %d , %f\n", cal_bonds_results->dates[i].year, cal_bonds_results->dates[i].month, cal_bonds_results->cum_invest[i]);
  // }
  // for (int i = 0; i < cal_lifecycle_results->n; i++){
  //   printf("%d, %d , %f\n", cal_lifecycle_results->dates[i].year, cal_lifecycle_results->dates[i].month, cal_lifecycle_results->cum_invest[i]);
  // }
  char * filename = "portfolio.csv";
  write_file(equities_results, bonds_results, lifecycle_results, filename);
  free_interest_array(sp_array, bond_array);
  free_results(equities_results, bonds_results, lifecycle_results);
  return EXIT_SUCCESS;
}
