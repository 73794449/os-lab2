#include "coin_machine.h"
#include "sem_blocks.h"
#include "thread_A.h"
#include "thread_B.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_CREATE_THREAD -11
#define SUCCESS 0
#define TIMES_TO_GO 25
// #define GET_CHAR_MODE

/*
Kiev 28
Moscow 37
London 50
Berlin 77
Paris 91
*/

int main() {
  CM coin_mch1 = {
      .change = 0,
      .COINS_IN_MACHINE =
          {{1, 50}, {2, 25}, {5, 20}, {10, 15}, {25, 10}, {50, 5}},
      .COINS_TO_CHANGE = {{1, 0}, {2, 0}, {5, 0}, {10, 0}, {25, 0}, {50, 0}},
      .PRICES = {28, 37, 55, 77, 91},
      .message = ""};
  srand((unsigned int)time(NULL));
  pthread_t PA, PB;
  int status1, status2;
  int status_addr1, status_addr2;
#ifdef GET_CHAR_MODE
  size_t i = 0;
  while (1) {
#endif
#ifndef GET_CHAR_MODE
    for (size_t i = 0; i < TIMES_TO_GO; i++) {
#endif
      printf("Today tickets bought: %ld\n", i);
      sem_init(&sem1, 0, 1);
      sem_init(&sem2, 0, 0);
      sem_init(&sem3, 0, 0);
      status1 = pthread_create(&PA, NULL, thread_a, (void *)&coin_mch1);
      if (status1 != 0) {
        printf("int main() error: cannot create thread_a");
        exit(ERROR_CREATE_THREAD);
      }
      status2 = pthread_create(&PB, NULL, thread_b, (void *)&coin_mch1);
      if (status2 != 0) {
        printf("int main() error: cannot create thread_b");
        exit(ERROR_CREATE_THREAD);
      }

      status1 = pthread_join(PA, (void **)&status_addr1);
      status2 = pthread_join(PB, (void **)&status_addr2);
#ifdef GET_CHAR_MODE
      getchar();
      i++;
#endif
    }
    pthread_exit(NULL);
  }