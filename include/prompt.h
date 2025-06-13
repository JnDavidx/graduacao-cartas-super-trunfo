#ifndef PROMPT_H
#define PROMPT_H

#include <card.h>

bool ask_for_card_args(card_args_t *args);
void print_card_comparison(card_t *card1, card_t *card2);

#endif /* PROMPT_H */