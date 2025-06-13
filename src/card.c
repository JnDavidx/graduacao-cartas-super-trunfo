#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <card.h>


static bool card_init(card_t* card, const card_args_t *args);
static void card_print(const card_t *card);

static bool card_check_area(float area);
static bool card_check_code(const char *code, char state);
static bool card_check_state(char state);

static int8_t
card_compare(card_field_t field, const card_t *card1, const card_t *card2);


typedef enum
{
    area,
    city,
    code,
    gpd,
    gpd_per_capita,
    population,
    population_density,
    power,
    state,
    tourist_attractions

} _card_field_t;

const card_namespace_t *Card = &(card_namespace_t)
{
    .init = card_init,
    .print = card_print,
    .check_area = card_check_area,
    .check_code = card_check_code,
    .check_state = card_check_state,
    .compare = card_compare,
    .fields = &(card_fields_t)
    {
        .area = area,
        .city = city,
        .code = code,
        .gpd = gpd,
        .gpd_per_capita = gpd_per_capita,
        .population = population,
        .population_density = population_density,
        .power = power,
        .state = state,
        .tourist_attractions = tourist_attractions
    }
};

static bool card_check_area(float area)
{
    return area > 0;
}

static bool card_check_code(const char *code, char state)
{
    if (code == NULL || strlen(code) != 3)
        return false;

    if (code[0] != state || code[1] != '0' || code[2] < '1' || code[2] > '4')
        return false;

    return true;
}

static bool card_check_state(char state)
{
    if (state < 'A' || state > 'H')
        return false;

    return true;
}

static bool card_init(card_t *card, const card_args_t *args)
{
    bool are_args_valid = card != NULL
                       && args != NULL
                       && Card->check_state(args->state)
                       && Card->check_code(args->code, args->state)
                       && Card->check_area(args->area);

    if (!are_args_valid)
        return false;

    memset(card, 0, sizeof(card_t));

    card->state = args->state;
    card->population = args->population;
    card->area = args->area;
    card->gpd = args->gpd;
    card->tourist_attractions = args->tourist_attractions;

    strcpy(card->code, args->code);
    strcpy(card->city, args->city);

    card->gpd_per_capita = card->population > 0
                         ? card->gpd * 1000000000 / card->population
                         : 0;

    card->population_density = card->population / card->area;

    card->power = card->area
                + card->gpd
                + card->gpd_per_capita
                + card->population
                + card->tourist_attractions
                - card->population_density;

    return true;
}

static int8_t
card_compare(card_field_t field, const card_t *card1, const card_t *card2)
{
    if (card1 == NULL || card2 == NULL)
        return -2;

    int8_t result = -2;

    switch (field)
    {
        case area:
            result = card1->area > card2->area ? 1
                   : card1->area < card2->area ? -1
                   : 0;
            break;
        case gpd:
            result = card1->gpd > card2->gpd ? 1
                   : card1->gpd < card2->area ? -1
                   : 0;
            break;
        case population:
            result = card1->population > card2->population ? 1
                   : card1->population < card2->population ? -1
                   : 0;
            break;
        case tourist_attractions:
            result = card1->tourist_attractions > card2->tourist_attractions ? 1
                   : card1->tourist_attractions < card2->tourist_attractions ? -1
                   : 0;
            break;
        case gpd_per_capita:
            result = card1->gpd_per_capita > card2->gpd_per_capita ? 1
                   : card1->gpd_per_capita < card2->gpd_per_capita ? -1
                   : 0;
            break;
        case population_density:
            result = card1->population_density < card2->population_density ? 1
                   : card1->population_density > card2->population_density ? -1
                   : 0;
            break;
        case power:
        default:
            result = card1->power > card2->power ? 1
                   : card1->power < card2->power ? -1
                   : 0;
    }

    return result;
}

static void card_print(const card_t *card)
{
    if (card == NULL)
        return;

    printf("Estado: %c\n", card->state);
    printf("Código: %s\n", card->code);
    printf("Nome da Cidade: %s\n", card->city);
    printf("População: %d\n", card->population);
    printf("Área: %.2f km²\n", card->area);
    printf("PIB: %.2f bilhões de reais\n", card->gpd);
    printf("Número de Pontos Turísticos: %d\n", card->tourist_attractions);
    printf("Densidade Populacional: %.2f hab/km²\n", card->population_density);
    printf("PIB per Capita: %.2f reais\n", card->gpd_per_capita);
    printf("Super Poder: %.2f\n", card->power);
}