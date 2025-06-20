#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dynamic-menu.h"
#include "colors-menu.h"

int display_menu(Menu *menu);
int read_key();
void clear_screen();
void enable_color_mode();
int get_column_width(ItemMenu *menu, int numberItemsMenu);

Menu create_menu(const char* title, ItemMenu* item, int numberItems, int columns, int gap){
    Menu menu;

    menu.title = title;
    menu.item = item;
    menu.numberItems = numberItems;
    menu.columns = columns;
    menu.gap = gap;

    menu.selectedIndex = 0;

    menu.rows = menu.numberItems / menu.columns;
    if(menu.numberItems % menu.columns) menu.rows++;

    menu.columnWidth = get_column_width(menu.item, menu.numberItems);

    for(int i = 0; i < numberItems; i++){
        menu.item[i].activated = true;
        menu.item[i].currentColumn = i % menu.columns;
        menu.item[i].currentRow = i / menu.columns;
    }

    return menu;
}


void run_menu(Menu *menu){
    int input = 0;
    int actionResult;
    bool isCommand = false;

    enable_color_mode();

    do{
        display_menu(menu);

        do{
            input = read_key();
            if(input){
                isCommand = true;

                int previousIndex = menu->selectedIndex;
                int currentColumn = menu->item[previousIndex].currentColumn;
                int currentRow = menu->item[previousIndex].currentRow;
                bool itFound = false;
                switch(input){
                    case KEY_UP:{
                        int newIndex = previousIndex - menu->columns;

                        while(newIndex >= 0 &&
                              menu->item[newIndex].currentColumn == currentColumn) {
                            if (menu->item[newIndex].activated) {
                                menu->selectedIndex = newIndex;
                                itFound = true;
                                break;
                            }
                            newIndex -= menu->columns;
                        }

                        if (!itFound) {
                            for (int i = menu->numberItems - 1; i >= 0; i--) {
                                if (menu->item[i].currentColumn == currentColumn &&
                                    menu->item[i].activated) {
                                    menu->selectedIndex = i;
                                    break;
                                }
                            }
                        }
                        break;
                    }

                    case KEY_DOWN:{
                        int newIndex = previousIndex + menu->columns;

                        while(newIndex < menu->numberItems &&
                              menu->item[newIndex].currentColumn == currentColumn) {
                            if (menu->item[newIndex].activated) {
                                menu->selectedIndex = newIndex;
                                itFound = true;
                                break;
                            }
                            newIndex += menu->columns;
                        }

                        if (!itFound) {
                            for (int i = 0; i < menu->numberItems; i++) {
                                if (menu->item[i].currentColumn == currentColumn &&
                                    menu->item[i].activated) {
                                    menu->selectedIndex = i;
                                    break;
                                }
                            }
                        }
                        break;
                    }

                    case KEY_LEFT:{
                        int newIndex = previousIndex - 1;

                        while(newIndex >= 0 &&
                              menu->item[newIndex].currentRow == currentRow) {
                            if (menu->item[newIndex].activated) {
                                menu->selectedIndex = newIndex;
                                itFound = true;
                                break;
                            }
                            newIndex--;
                        }

                        if (!itFound) {
                            for (int i = menu->numberItems - 1; i >= 0; i--) {
                                if (menu->item[i].currentRow == currentRow &&
                                    menu->item[i].activated) {
                                    menu->selectedIndex = i;
                                    break;
                                }
                            }
                        }
                        break;
                    }

                    case KEY_RIGHT:{
                        int newIndex = previousIndex + 1;

                        while(newIndex < menu->numberItems &&
                              menu->item[newIndex].currentRow == currentRow) {
                            if (menu->item[newIndex].activated) {
                                menu->selectedIndex = newIndex;
                                itFound = true;
                                break;
                            }
                            newIndex++;
                        }

                        if (!itFound) {
                            for (int i = 0; i < menu->numberItems; i++) {
                                if (menu->item[i].currentRow == currentRow &&
                                    menu->item[i].activated) {
                                    menu->selectedIndex = i;
                                    break;
                                }
                            }
                        }
                        break;
                    }

                    case KEY_ENTER:{
                        actionResult = menu->item[menu->selectedIndex].action();

                        if (actionResult == MENU_FLOW_EXIT) {
                            return;
                        }
                        break;
                    }
                }
            }
        }while(!isCommand);
        isCommand = false;
    }while(1);
}

int display_menu(Menu *menu){
    char *headerBorder;

    int lengthHeaderBorder;
    int lengthTitle;
    int lengthItems;
    int gapStart, gapEnd;

    lengthTitle = strlen(menu->title);
    lengthItems = menu->columns * menu->columnWidth + menu->gap * (menu->columns - 1);

    lengthHeaderBorder = 2 * menu->gap;
    if(lengthTitle > lengthItems){
        lengthHeaderBorder += lengthTitle;
    }
    else{
        lengthHeaderBorder += lengthItems;
    }

    headerBorder = (char*) malloc(lengthHeaderBorder + 1);
    if(headerBorder == NULL){
        printf("\nError: Failed to allocate memory!\n");
        return 1;
    }
    memset(headerBorder, '#', lengthHeaderBorder);
    headerBorder[lengthHeaderBorder] = '\0';

    // HEADER MENU
    gapEnd = (lengthHeaderBorder - lengthTitle) / 2;
    gapStart = (lengthHeaderBorder - lengthTitle) % 2;
    if(gapStart){
        gapStart = gapEnd + 1;
    }
    else gapStart = gapEnd;

    clear_screen();

    printf(HEADER_COLOR);
    printf("%s\n", headerBorder);
    printf("%-*s", gapStart, "");
    printf("%s", menu->title);
    printf("%-*s\n", gapEnd, "");
    printf("%s\n", headerBorder);
    printf(COLOR_RESET);

    // OPTION MENU
    gapEnd = (lengthHeaderBorder - lengthItems) / 2;
    gapStart = (lengthHeaderBorder - lengthItems) % 2;
    if(gapStart){
        gapStart = gapEnd + 1;
    }
    else gapStart = gapEnd;

    for(int i = 0; i < menu->rows; i++){
        printf("%-*s", gapStart, "");

        for(int j = 0; j < menu->columns; j++){
            int index = i * menu->columns +j;
            if(index < menu->numberItems){
                if(index == menu->selectedIndex)printf(SELECTED_COLOR);

                else if(menu->item[index].activated == false){
                    printf(DISABLED_COLOR);
                }

                else {
                    printf(MENU_COLOR);
                }

                printf("%-*s", menu->columnWidth, menu->item[index].label);
                printf(COLOR_RESET);
                if(j != menu->columns - 1){
                    printf("%-*s", menu->gap, "");
                }
            }
        }
        printf("%-*s\n", gapEnd, "");
    }
    printf(HEADER_COLOR "%s\n" COLOR_RESET, headerBorder);

    free(headerBorder);
    return 0;
}

void clear_screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif // _WIN32
}

void enable_color_mode(){
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if(hOut == INVALID_HANDLE_VALUE){
            fprintf(stderr, "ERRO: Nao foi possivel obter o handle do console.\n");
            return;
        }

        DWORD dwMode = 0;
        if(!GetConsoleMode(hOut, &dwMode)){
            fprintf(stderr, "ERRO: Nao foi possivel obter o modo do console.\n");
            return;
        }

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if(!SetConsoleMode(hOut, dwMode)){
            fprintf(stderr, "ERRO: Nao foi possivel ativar o modo de terminal virtual.\n");
            return;
        }
    #endif // _WIN32
}

int get_column_width(ItemMenu *menu, int numberItemsMenu){
    int maxLabelLength = 0;
    for(int i = 0; i < numberItemsMenu; i++){
        int currentLength = strlen(menu[i].label);
        if(currentLength > maxLabelLength) maxLabelLength = currentLength;
    }

    return maxLabelLength;
}

int read_key(){
    #ifdef _WIN32
        int input = _getch();

        if(input == 224) input = _getch();

        switch(input){
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_ENTER:
                return input;

            default:
                return MENU_OP_INVALID_KEY;
        }

    #else
        struct termios oldt, newt;
        int input;

        // Save current terminal config
        tcgetattr(STDIN_FILENO, &oldt);

        // Copy and modify to non-canonical mode (direct reading)
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        input = getchar();
        if(input == 27){
            if(getchar() == 91) input = getchar();
        }

        switch(input){
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_ENTER:
                break;

            default:
                input = MENU_OP_INVALID_KEY;
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return input;
    #endif // _WIN32
}

MenuOpStatus disable_item(Menu *menu, const char* label){
    for(int i = 0; i < menu->numberItems; i++){
        if(strcmp(menu->item[i].label, label) == 0){
            menu->item[i].activated = false;
            return MENU_OP_SUCCESS;
        }
    }

    return MENU_OP_ITEM_NOT_FOUND;
}

int exit_menu(){
    return MENU_FLOW_EXIT;
}

