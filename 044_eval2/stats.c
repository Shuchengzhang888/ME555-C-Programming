#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// any other headers you need here

stat_t parseLine(const char * line) {
  // STEP 1: write me
  ///No input
  if (line == NULL){
    fprintf(stderr,"There is no line.");
    exit(EXIT_FAILURE);
  }
  stat_t p;
  ///Check the format and divide line into 3 parts
  /// name      :games       :points
  /// line      first_colon  second_colon
  char * first_colon = strchr(line, ':');
  if (first_colon == NULL){
    fprintf(stderr,"There is no colon.");
    exit(EXIT_FAILURE);
  }
  //printf("%d",first_colon);
  char * second_colon = strchr(first_colon + 1, ':');
  //printf("%s",second_colon);
  if (second_colon == NULL){
    fprintf(stderr,"There is no second colon.");
    exit(EXIT_FAILURE);
  }

  ///Input players' name
  int i =0;
  ///Use do-while to check there is no input
  do{
    ///Check if the name has numbers and there is nothing before first colon
    if (isdigit(line[i]) || (i == 1 && line[i] == ':')){
      fprintf(stderr, "The name is not valid.");
      exit(EXIT_FAILURE);
    }
    else{
      if (i < MAX_NAME_LEN){
        p.player[i] = line[i];
        i++;
      }
      ///Check if the name is loger than MAX
      else{
        fprintf(stderr, "The name is too long.");
        exit(EXIT_FAILURE);
      }
    }
  }while(line[i] != ':');
  p.player[i] = '\0';

  
  ///Input points
  i = 1;
  int flag = 0;
  do{
    ///The situation of 0 points
    if (first_colon[1] == 0 && first_colon[2] == ':'){
      flag = 1;
      break;
    }
    ///Make sure it just includes digits and be positive and the number is not 0 beginning
    if (!isdigit(first_colon[i]) || (i == 1 && first_colon[i] == '0' && flag == 1)){
      fprintf(stderr, "The point number is not valid.");
      exit(EXIT_FAILURE);
    }
    i++;
  }while(first_colon[i] != ':');
  ///parse whole string to unsigned
  char * endptr;
  p.points = strtoul(first_colon + 1, &endptr, 10);

  ///Input games
  i = 1;
  flag = 0;
  do{
    ///The situation of 0 points
    if (second_colon[1] == 0 && second_colon[2] == '\0'){
      flag = 1;
      break;
    }
    ///Make sure it just includes digits and be positive and the number is not 0 beginning
    if (!isdigit(second_colon[i]) || (i ==1 && second_colon[i] == '0' && flag)){
      fprintf(stderr, "The games number is not valid.");
      exit(EXIT_FAILURE);
    }
    i++;
  }while(second_colon[i] != '\0');
  ///parse whole string to unsigned long
  p.games = strtoul(second_colon + 1, &endptr, 10);

  return p;  
}

double calcGamePerformance(stat_t * statarr, unsigned long * pointarr, size_t nplayers) {
  // STEP 2: write me
  if (statarr == NULL){
    fprintf(stderr,"There is no history record.");
    exit(EXIT_FAILURE);
  }
  if (pointarr == NULL){
    fprintf(stderr,"There is no new record.");
    exit(EXIT_FAILURE);
  }
  if (nplayers <= 0){
    fprintf(stderr,"Number of players is not valid.");
    exit(EXIT_FAILURE);
  }
  
  double singlePer = 0;
  double averagePer = 0;

  for (size_t i = 0; i < nplayers; i++){
    averagePer += (double)statarr[i].points / (double)statarr[i].games;
    singlePer += (double)pointarr[i];
  }
  double rate = singlePer / averagePer;

  return rate;
}

void addGameStats(stat_t * statarr, unsigned long * pointarr, size_t nplayers) {
  // STEP 3: write me
  if (statarr == NULL){
    fprintf(stderr,"There is no history record.");
    exit(EXIT_FAILURE);
  }
  if (pointarr == NULL){
    fprintf(stderr,"There is no new record.");
    exit(EXIT_FAILURE);
  }
  if (nplayers <= 0){
    fprintf(stderr,"Number of players is not valid.");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < nplayers; i++){
    statarr[i].points += pointarr[i];
    statarr[i].games++;
  }
}

void printBreakout(stat_t * statarr, unsigned long * pointarr, size_t nplayers) {
  // STEP 4: write me
  if (statarr == NULL){
    fprintf(stderr,"There is no history record.");
    exit(EXIT_FAILURE);
  }
  if (pointarr == NULL){
    fprintf(stderr,"There is no new record.");
    exit(EXIT_FAILURE);
  }
  if (nplayers <= 0){
    fprintf(stderr,"Number of players is not valid.");
    exit(EXIT_FAILURE);
  }

  double per[nplayers];
  for (size_t i = 0; i < nplayers; i++){
    if (statarr[i].points != 0){
      per[i] = (double)pointarr[i] / ((double)statarr[i].points / (double)statarr[i].games);
    }
    else{
      per[i] = 1000;
    }
  }

  size_t max = 0;
  for (size_t i = 1; i < nplayers; i++){
    if(per[i] > per[max]){
      max = i;
    }
  }

  if (per[max] == 1000){
    printf("The breakout player this game is %s with infinity %% of avg ppg\n", statarr[max].player);
  }
  else{
    printf("The breakout player this game is %s with %.0f%% of avg ppg\n", statarr[max].player, per[max]*100);
  }
}
