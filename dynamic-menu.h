#ifndef DYNAMIC_MENU_H
#define DYNAMIC_MENU_H

#include <stdbool.h>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>

    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define KEY_ENTER 13

#else
    #include <termios.h>
    #include <unistd.h>

    #define KEY_UP 'A'
    #define KEY_DOWN 'B'
    #define KEY_LEFT 'C'
    #define KEY_RIGHT 'D'
    #define KEY_ENTER 10

#endif // _WIN32

#define CREATE_MENU(title, items_array, columns, gap) \
    create_menu(title, items_array, (sizeof(items_array) / sizeof(items_array[0])), columns, gap)

typedef enum{
    MENU_FLOW_CONTINUE,
    MENU_FLOW_EXIT
} MenuFlow;

typedef enum{
    MENU_OP_SUCCESS,
    MENU_OP_INVALID_KEY = 0,
    MENU_OP_ITEM_NOT_FOUND
} MenuOpStatus;

typedef struct ItemMenu{
    const char* label;
    int (*action)(void);

    bool activated;
    int currentColumn;
    int currentRow;
} ItemMenu;

typedef struct Menu{
    const char* title;
    ItemMenu* item;
    int columns;
    int gap;

    int selectedIndex;
    int numberItems;
    int rows;
    int columnWidth;
} Menu;

Menu create_menu(const char* title, ItemMenu* item, int numberItems, int columns, int gap);
void run_menu(Menu *menu);
MenuOpStatus disable_item(Menu *menu, const char* label);
int exit_menu();

#endif // DYNAMIC_MENU_H_INCLUDED
