#include "thread_B.h"
#include "coin_machine.h"
#include "sem_blocks.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculate_coins(CM *c_machine) {
  int i = 5;
  while (i >= 0) {
    if ((c_machine->COINS_IN_MACHINE[i][1] -
         c_machine->COINS_TO_CHANGE[i][1]) != 0) {
      if (c_machine->change > c_machine->COINS_IN_MACHINE[i][0]) {
        c_machine->change -= c_machine->COINS_IN_MACHINE[i][0];
        c_machine->COINS_TO_CHANGE[i][1]++;
      } else if (c_machine->change == c_machine->COINS_IN_MACHINE[i][0]) {
        c_machine->change -= c_machine->COINS_IN_MACHINE[i][0];
        c_machine->COINS_TO_CHANGE[i][1]++;
        break;
      } else {
        i--;
      }
    } else {
      i--;
    }
  }
}
void generate_change(CM *c_machine) {
  if (c_machine->change != 0)
    c_machine->message = "Cannot give change";
  else
    c_machine->message = "Success";
}
void *thread_b(void *args) {
  sem_wait(&sem2);
  CM *c_machine = (CM *)args;
  calculate_coins(c_machine);
  generate_change(c_machine);
  sem_post(&sem3);
  return NULL;
}