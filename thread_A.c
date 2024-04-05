#include "thread_A.h"
#include "coin_machine.h"
#include "sem_blocks.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculate_change(CM *c_machine) {
  unsigned long int client_gives = 100;
  int selected_ticket = rand() % 5;
  char *cities[5] = {"Kiev", "Moscow", "London", "Berlin", "Paris"};
  printf("I want to buy ticket to %s\n", cities[selected_ticket]);
  c_machine->change = client_gives - c_machine->PRICES[selected_ticket];
}
void give_change(CM *c_machine) {

  printf("%s\n", c_machine->message);
  printf("Change: %ld\n", c_machine->change);
  printf("Coins to give:\n");
  for (size_t i = 0; i < 6; i++) {
    printf("[%ld|%ld] ", c_machine->COINS_TO_CHANGE[i][0],
           c_machine->COINS_TO_CHANGE[i][1]);
  }
  printf("\nCoins in machine:\n");
  for (size_t i = 0; i < 6; i++) {
    printf("[%ld|%ld] ", c_machine->COINS_IN_MACHINE[i][0],
           c_machine->COINS_IN_MACHINE[i][1]);
  }
  printf("\n");
  c_machine->change = 0;
  if (strcmp(c_machine->message, "Success") == 0) {
    for (size_t i = 0; i < 6; i++) {
      c_machine->COINS_IN_MACHINE[i][1] -= c_machine->COINS_TO_CHANGE[i][1];
    }
  }

  CM temp_machine = {
      .COINS_TO_CHANGE = {{1, 0}, {2, 0}, {5, 0}, {10, 0}, {25, 0}, {50, 0}}};

  for (int i = 0; i < 6; i++)
    for (int k = 0; k < 2; k++)
      c_machine->COINS_TO_CHANGE[i][k] = temp_machine.COINS_TO_CHANGE[i][k];
}
void *thread_a(void *args) {
  sem_wait(&sem1);
  printf("===================================================\n");
  CM *c_machine = (CM *)args;
  calculate_change(c_machine);
  sem_post(&sem2);
  sem_wait(&sem3);
  give_change(c_machine);
  printf("===================================================\n");
  sem_post(&sem1);
  return NULL;
}