#include <stdio.h>

#include <prompt.h>


int main()
{
    card_t card1;
    card_t card2;
    card_args_t args;

    if (ask_for_card_args(&args) && Card->init(&card1, &args))
        Card->print(&card1);
    else
        printf("Erro ao criar carta");

    if (ask_for_card_args(&args) && Card->init(&card2, &args))
        Card->print(&card2);
    else
        printf("Erro ao criar carta");

    print_card_comparison(&card1, &card2);

    return 0;
}