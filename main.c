#include "slay_the_spire_type.h"
#include "slay_the_spire_cards_func.h"
#include "slay_the_spire_enemy_func.h"
#include "slay_the_spire_handler.h"


int continue_handler(int *mod, bool *running) {
    printf("Don't work\n");
    return 0;
}


int quit_handler(int *mod, bool *running) {
    *running = false;
    return 0;
}


int new_game_handler(int *mod, bool *running) {
    *mod = MAP;
    return 0;
}


int count_enter(char *text) {
    int count = 0;
    for (char *i = text; *i != '\0'; i++) {
        if (*i == '\n') count++;
    }
    return count;
}


void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *const_text, SDL_Color color, SDL_Rect *rect) {
    char *text = (char *)malloc((strlen(const_text) + 1) * sizeof(char));
    if (!text) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    strcpy(text, const_text);

    int count = count_enter(text) + 1;
    char *lines[count];

    char *token = strtok(text, "\n");
    int index = 0;
    while (token != NULL) {
        lines[index] = token;
        index++;
        token = strtok(NULL, "\n");
    }

    int start_position;
    int bias;

    for (int i = 0; i < count; i++) {
        SDL_Surface *surface = TTF_RenderText_Blended(font, lines[i], color);
        if (!surface) {
            fprintf(stderr, "TTF_RenderText_Blended Error: %s\n", TTF_GetError());
            continue;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }
        if (count % 2) bias = (surface->h) * (count / 2 - i) - (surface->h);
        else bias = (surface->h) * (count / 2 - i);
        start_position = rect->y + (rect->h - surface->h) / 2;
        SDL_Rect text_rect = {rect->x + (rect->w - surface->w) / 2, start_position - (surface->h) * (count / 2 - i), surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &text_rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    free(text);
}


int print_enemy(Enemy_list *enemy_list, SDL_Renderer *renderer, TTF_Font *font) {
    if (enemy_list == NULL) {
        printf("enemy not exist\n");
        return 1;
    }

    char enemy_text[16];
    Enemy_node *enemy_help_node = enemy_list->head;

    for (int i = 0; i < enemy_list->len; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &enemy_help_node->value);
        SDL_Color textColor = {255, 255, 255, 255};
        snprintf(enemy_text, sizeof(enemy_text), "enemy\n%d", enemy_help_node->hp);
        render_text(renderer, font, enemy_text, textColor, &enemy_help_node->value);
        enemy_help_node = enemy_help_node->next;
    }

    return 0;
}


int print_card(Card_list *rect_list, SDL_Renderer *renderer, TTF_Font *font) {
    if (rect_list == NULL) {
        printf("cards not exist\n");
        return 1;
    }

    Card_node *card_help_node = rect_list->head;
    
    for (int i = 0; i < rect_list->len; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &card_help_node->value);
        SDL_Color textColor = {255, 255, 255, 255};
        render_text(renderer, font, card_help_node->desc, textColor, &card_help_node->value);
        card_help_node = card_help_node->next;
    }

    return 0;
}


int battle(SDL_Renderer *renderer, SDL_Event *event, TTF_Font *font, bool *running, Enemy_list *enemy_list, int *choose_rect, Player *player, int *mod, int *turn) {
    
    //printf("%d\n", *turn);

    SDL_SetRenderDrawColor(renderer, WINDOW_BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
    SDL_Color textColor = {255, 255, 255, 255};

    // printf("%d\n", player->hand->head->energy);
    print_card(player->hand, renderer, font);
    print_enemy(enemy_list, renderer, font);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player->energy_rect);

    char energy_text[6];
    sprintf(energy_text, "%d", player->cur_energy);
    render_text(renderer, font, energy_text, textColor, &player->energy_rect);

    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderDrawRect(renderer, &player->hero_rect);
    // render_text(renderer, font, "hero", textColor, &player->hero_rect);

    printf("%d\n", player->hand->len);

    SDL_RenderPresent(renderer);

    if (enemy_list->len <= 0) {
        *mod = AWARDS;
    }

    return 0;
}


int start_menu(SDL_Renderer *renderer, SDL_Event *event, bool *running, Rect_Text_List *start_menu_list, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, WINDOW_BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
    SDL_Color textColor = {255, 255, 255, 255};

    for (int i = 0; i < start_menu_list->len; i++) {

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &start_menu_list->list[i]->rect);
        render_text(renderer, font, start_menu_list->list[i]->text, textColor, &start_menu_list->list[i]->rect);
    }

    SDL_RenderPresent(renderer);
    return 0;
}


int start_map(SDL_Renderer *renderer, SDL_Event *event, TTF_Font *font, bool *running, SDL_Rect *map_rect, Player *player) {
    SDL_SetRenderDrawColor(renderer, WINDOW_BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
    SDL_Color textColor = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, map_rect);
    render_text(renderer, font, "next_battle", textColor, map_rect);

    SDL_RenderPresent(renderer);
    return 0;
}


int start_awards(SDL_Renderer *renderer, SDL_Event *event, TTF_Font *font, bool *running, Rect_Text_List *awards_list, Player *player, Card_list *awards_cards) {
    
    SDL_SetRenderDrawColor(renderer, WINDOW_BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
    SDL_Color textColor = {255, 255, 255, 255};

    for (int i = 0; i < awards_list->len; i++) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &awards_list->list[i]->rect);
        render_text(renderer, font, awards_list->list[i]->text, textColor, &awards_list->list[i]->rect);
    }

    SDL_RenderPresent(renderer);

    awards_cards = NULL;

    return 0;
}


int battle_init(Player **player, Enemy_list **enemy_list, int *battle_start) {
    (*player)->hand = card_init_list();

    for (int i = 0; i < 5; i++) {
        card_add_node(
            (*player)->hand,
            rand() % 2,
            WINDOW_WIDTH / 5 + (WINDOW_WIDTH / 10 + 10) * i, 
            WINDOW_HEIGHT / 3 * 2, 
            WINDOW_WIDTH / 10, 
            WINDOW_HEIGHT / 9 * 2);
    }

    *enemy_list = enemy_init_list();

    for (int i = 0; i < 2; i++) {
        enemy_add_node(
            *enemy_list, 
            100,
            WINDOW_WIDTH / 1.7 + (WINDOW_WIDTH / 10 + 10) * i, 
            WINDOW_HEIGHT / 5.5, 
            WINDOW_WIDTH / 10, 
            WINDOW_HEIGHT / 9 * 2);
    }

    *battle_start = false;
    return 0;
}


int player_turn(Player **player, Enemy_list **enemy_list, int *battle_start, int *turn) {

    
}


int enemy_turn(Player **player, Enemy_list **enemy_list, int *battle_start) {

    
}


Rect_Text *create_Rect_Text(int x, int y, int w, int h, char *text, int (*handler)(int *, bool *)) {
    Rect_Text *new_rect_text = (Rect_Text *)malloc(sizeof(Rect_Text));
    new_rect_text->rect.x = x;
    new_rect_text->rect.y = y;
    new_rect_text->rect.w = w;
    new_rect_text->rect.h = h;
    new_rect_text->text = text;
    new_rect_text->func = handler;
    return new_rect_text;
}


Rect_Text_List *create_Rect_Text_List(int len, ...) {
    Rect_Text_List *list = (Rect_Text_List *)malloc(sizeof(Rect_Text_List));
    list->len = len;
    list->list = (Rect_Text **)malloc(len * sizeof(Rect_Text *));
    
    va_list args;
    va_start(args, len);
    for (int i = 0; i < len; i++) {
        list->list[i] = va_arg(args, Rect_Text *);
    }
    va_end(args);
    return list;
}


Card_list start_choose_card() {

    Card_list *list = card_init_list(list);
    for (int i = 0; i < 3; i ++) {
        card_add_node(
            list, 
            rand() % COUNT_CARDS, 
            WINDOW_WIDTH / 5 + (WINDOW_WIDTH / 10 + 10) * i, 
            WINDOW_HEIGHT / 3 * 2, 
            WINDOW_WIDTH / 10, 
            WINDOW_HEIGHT / 9 * 2);
    }

    return *list;
}


Player *player_init() {
    Player *player = (Player *) malloc(sizeof(Player));
    SDL_Rect hero_rect;
    player->hero_rect = hero_rect;
    player->hp = 100;
    SDL_Rect rect = {WINDOW_WIDTH / 18, WINDOW_HEIGHT / 9 * 6.5, WINDOW_WIDTH / 15, WINDOW_WIDTH / 15};
    player->energy_rect = rect;
    player->max_energy = 3;
    player->cur_energy = 3;

    return player;
}


int choose_card(SDL_Renderer *renderer, SDL_Event *event, bool *running, TTF_Font *font, Card_list *awards_cards) {

    //printf("307\n");

    if (awards_cards == NULL) {
        
        printf("311\n");
        *awards_cards = start_choose_card();
    }

    SDL_SetRenderDrawColor(renderer, WINDOW_BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
    SDL_Color textColor = {255, 255, 255, 255};

    if (awards_cards == NULL) printf("~\n");

    print_card(awards_cards, renderer, font);

    SDL_RenderPresent(renderer);
}


int main() {

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // // Инициализация PNG загрузки
    // if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    //     printf("SDL_image не может инициализироваться! SDL_image Error: %s\n", IMG_GetError());
    //     return -1;
    // }

    // // Загрузка изображения
    // SDL_Surface* loadedSurface = IMG_Load("background.png");
    // if (loadedSurface == NULL) {
    //     printf("Изображение не может быть загружено! SDL_image Error: %s\n", IMG_GetError());
    //     return -1;
    // }

    // // Создание текстуры из поверхности
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    // SDL_FreeSurface(loadedSurface);
    // if (texture == NULL) {
    //     printf("Не удалось создать текстуру! SDL Error: %s\n", SDL_GetError());
    //     return -1;
    // }


    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/JetBrainsMono/JetBrainsMonoNerdFont-Light.ttf", 24); // Укажите путь к вашему шрифту
    if (font == NULL) {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    bool choose_card_init = false;
    bool running = true;
    SDL_Event event;
    int choose_rect = 0;
    
    Card_list *rect_list = NULL;
    Enemy_list *enemy_list = NULL;
    // Player *player = player_init();
    Player *player = (Player *) malloc(sizeof(Player));
    SDL_Rect hero_rect;
    player->hero_rect = hero_rect;
    player->hp = 100;
    SDL_Rect rect = {WINDOW_WIDTH / 18, WINDOW_HEIGHT / 9 * 6.5, WINDOW_WIDTH / 15, WINDOW_WIDTH / 15};
    player->energy_rect = rect;
    player->max_energy = 3;
    player->cur_energy = 3;
    

    Rect_Text_List *start_menu_list = create_Rect_Text_List(
        3,
        create_Rect_Text(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 150, 200, 50, "Continue", continue_handler),
        create_Rect_Text(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 75, 200, 50, "New Game", new_game_handler),
        create_Rect_Text(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, 200, 50, "Quit", quit_handler)
    );

    SDL_Rect map_rect = {100, 100, 100, 100};

    SDL_Rect awards_new_card_rect = {WINDOW_WIDTH / 20, WINDOW_HEIGHT / 9 * 6, WINDOW_WIDTH / 5, WINDOW_HEIGHT / 20};
    SDL_Rect awards_gold_rect = {WINDOW_WIDTH / 20, WINDOW_HEIGHT / 9 * 6 + WINDOW_HEIGHT / 15, WINDOW_WIDTH / 5, WINDOW_HEIGHT / 20};

    Rect_Text_List *awards_list = create_Rect_Text_List(
        3,
        create_Rect_Text(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 150, 200, 50, "Choose card", continue_handler),
        create_Rect_Text(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 75, 200, 50, "Gold", new_game_handler),
        create_Rect_Text(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, 200, 50, "Continue", quit_handler)
    );
    
    int mod = 0;
    int battle_start = 1;
    int turn = PLAYER_TURN;
    Card_list awards_cards;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if (mod == START_MENU) {

                if (event.type == SDL_KEYDOWN) keyboard_handler(&event, &running);
                else if (event.type == SDL_MOUSEMOTION) mouse_move_handler(&event);
                else if (event.type == SDL_MOUSEBUTTONDOWN) start_menu_mouse_click_handler(&event, &mod, start_menu_list, &running);
            }
            else if (mod == BATTLE_MOD) {
                if (event.type == SDL_KEYDOWN) keyboard_handler(&event, &running);
                else if (event.type == SDL_MOUSEMOTION) mouse_move_handler(&event);
                else if (event.type == SDL_MOUSEBUTTONDOWN) battle_mouse_click_handler(&event, enemy_list, &choose_rect, player, &turn);
            }
            else if (mod == MAP) {
                if (event.type == SDL_KEYDOWN) keyboard_handler(&event, &running);
                else if (event.type == SDL_MOUSEMOTION) mouse_move_handler(&event);
                else if (event.type == SDL_MOUSEBUTTONDOWN) map_mouse_click_handler(&event, &mod, &map_rect, &running, &battle_start);
            }
            else if (mod == AWARDS) {

                if (event.type == SDL_KEYDOWN) keyboard_handler(&event, &running);
                else if (event.type == SDL_MOUSEMOTION) mouse_move_handler(&event);
                else if (event.type == SDL_MOUSEBUTTONDOWN) awards_mouse_click_handler(&event, &mod, awards_list, &running);
            }
        }

        if (battle_start) {
            if(battle_init(&player, &enemy_list, &battle_start)) printf("Battle init don't work\n");
            else printf("Battle init ready\n");
        }

        if (mod == START_MENU) start_menu(renderer, &event, &running, start_menu_list, font);
        else if (mod == BATTLE_MOD) battle(renderer, &event, font, &running, enemy_list, &choose_rect, player, &mod, &turn);
        else if (mod == MAP) start_map(renderer, &event, font, &running, &map_rect, player);
        else if (mod == AWARDS) start_awards(renderer, &event, font, &running, awards_list, player, &awards_cards);
        else if (mod == CHOOSE_CARD_MOD) choose_card(renderer, &event, &running, font, &awards_cards);
    }

    enemy_free_list(enemy_list); 
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
