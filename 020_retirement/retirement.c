#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double compute_balance(int age_month, double balance, retire_info info){

  for(int i = 1; i <= info.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n", age_month/12, age_month%12, balance);
    balance += balance * info.rate_of_return + info.contribution;
    age_month += 1;
  }
  return balance;
}

void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired){ //info about being retired
  double after_working = compute_balance(startAge, initial, working);
  compute_balance(startAge + working.months, after_working, retired);
}

int main(){
  retire_info working = {489, 1000, 0.045/12};
  retire_info retired = {384, -4000, 0.01/12};
  retirement(327, 21345, working, retired);
  return 0;
}

  
  
  
  
  
  
  















