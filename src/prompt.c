#include <stdio.h>
#include <string.h>

#include <prompt.h>


static void flush_stdin();

bool ask_for_card_state(card_args_t *args);
bool ask_for_card_code(card_args_t *args);
bool ask_for_card_area(card_args_t *args);
bool ask_for_card_city(card_args_t *args);
bool ask_for_card_population(card_args_t *args);
bool ask_for_card_gpd(card_args_t *args);
bool ask_for_card_tourist_attractions(card_args_t *args);
bool ask_for_card_args(card_args_t *args);

const char *format_comparison_result(int8_t result);
void print_card_comparison(card_t *card1, card_t *card2);


static void flush_stdin()
{
    int c = 0;

    do c = getchar(); while (c != '\n' && c != EOF);
}

bool ask_for_card_state(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    while (true)
    {
        printf("\nDigite o estado da carta (A-H):\n> ");
        scanf(" %c%c", &args->state, &char_after_input);

        if (char_after_input == '\n' && Card->check_state(args->state))
            break;

        if (char_after_input != '\n')
            flush_stdin();

        printf("Estado inválido\n\n");
    }

    return true;
}

bool ask_for_card_code(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;
    char code = 0;

    while (true)
    {
        printf("\nDigite um número para o código da carta (1-4):\n> ");
        scanf(" %c%c", &code, &char_after_input);

        sprintf(args->code, "%c0%c", args->state, code);

        if (char_after_input == '\n' && Card->check_code(args->code, args->state))
            break;

        if (char_after_input != '\n')
            flush_stdin();

        printf("Número inválido\n\n");
    }

    return true;
}

bool ask_for_card_area(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    while (true)
    {
        printf("\nDigite o area da cidade (em km²):\n> ");
        scanf(" %f%c", &args->area, &char_after_input);

        if (char_after_input != '\n')
            flush_stdin();

        if (Card->check_area(args->area))
            break;

        printf("Área inválida");
    }

    return true;
}

bool ask_for_card_city(card_args_t *args)
{
    if (args == NULL)
        return false;

    printf("\nDigite o nome da cidade:\n> ");
    fgets(args->city, sizeof(args->city), stdin);

    args->city[strlen(args->city) - 1] = 0;

    return true;
}

bool ask_for_card_population(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    printf("\nDigite a população da cidade:\n> ");
    scanf(" %ui%c", &args->population, &char_after_input);

    if (char_after_input != '\n')
        flush_stdin();

    return true;
}

bool ask_for_card_gpd(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    printf("\nDigite o PIB da cidade (em bilhões de reais):\n> ");
    scanf(" %f%c", &args->gpd, &char_after_input);

    if (char_after_input != '\n')
        flush_stdin();

    return true;
}

bool ask_for_card_tourist_attractions(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    printf("\nDigite o numero de pontos turisticos da cidade:\n> ");
    scanf(" %ui%c", &args->tourist_attractions, &char_after_input);

    if (char_after_input != '\n')
        flush_stdin();

    return true;
}

bool ask_for_card_args(card_args_t *args)
{
    if (args == NULL)
        return false;

    memset(args, 0, sizeof(card_args_t));

    bool status = ask_for_card_state(args)
               && ask_for_card_code(args)
               && ask_for_card_city(args)
               && ask_for_card_area(args)
               && ask_for_card_population(args)
               && ask_for_card_gpd(args)
               && ask_for_card_tourist_attractions(args);

    return status;
}

const char *format_comparison_result(int8_t result)
{
    return result == 1 ? "Carta 1 venceu"
         : result == -1 ? "Carta 2 venceu"
         : result == 0 ? "Empate"
         : "Erro ao comparar cartas";
}

void print_card_comparison(card_t *card1, card_t *card2)
{
    int8_t area                = Card->compare(Card->fields->area, card1, card2);
    int8_t gpd                 = Card->compare(Card->fields->gpd, card1, card2);
    int8_t gpd_per_capita      = Card->compare(Card->fields->gpd_per_capita, card1, card2);
    int8_t population          = Card->compare(Card->fields->population, card1, card2);
    int8_t population_density  = Card->compare(Card->fields->population_density, card1, card2);
    int8_t power               = Card->compare(Card->fields->power, card1, card2);
    int8_t tourist_attractions = Card->compare(Card->fields->tourist_attractions, card1, card2);

    printf("\nComparação de Cartas:\n\n");
    printf("População: %s\n", format_comparison_result(population));
    printf("Área: %s\n", format_comparison_result(area));
    printf("PIB: %s\n", format_comparison_result(gpd));
    printf("Pontos Turísticos: %s\n", format_comparison_result(tourist_attractions));
    printf("Densidade Populacional: %s\n", format_comparison_result(population_density));
    printf("PIB per Capita: %s\n", format_comparison_result(gpd_per_capita));
    printf("Super Poder: %s\n", format_comparison_result(power));
}