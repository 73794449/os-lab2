#ifndef COIN_MACHINE_H
#define COIN_MACHINE_H
struct coin_machine {
  unsigned long int change;
  unsigned long int COINS_IN_MACHINE[6][2];
  unsigned long int COINS_TO_CHANGE[6][2];
  unsigned long int PRICES[5];
  char *message;
};
typedef struct coin_machine CM;
#endif