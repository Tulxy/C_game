#include <stdio.h>
#include <unistd.h>

// Maximální počet životů hráče
unsigned short max_hp = 10; // 10HP je maximum
// Aktuální počet životů hráče
unsigned short hp = 10; // 10HP v základu

// Množství peněz hráče
unsigned int money = 10; // 10 zlatých v základu
// Zkušenostní body hráče
unsigned int xp = 0;

// Funkce pro výpis aktuálních statistik hráče
void print_stats() {
    int empty_hp = max_hp - hp; // počet chybějících životů
    int level = xp / 10; // výpočet úrovně na základě XP

    printf("\n");
    printf("Level: %d 🔮", level);
    printf("\n");
    printf("HP: ");
    // Vykreslení plných životů
    for (int i = 0; i < hp; i++) {
        printf("❤️");
    }
    // Vykreslení prázdných životů
    for (int i = 0; i < empty_hp; i++) {
        printf("🩶");
    }
    printf("\n");
    printf("Money: %d 💵\n", money);
}

// Výpis nabídky hospody
void pub_print() {
    printf("Pub:\n");
    printf("\n");
    printf("--- [HP: %d] --- [$: %d] ---", hp, money);
    printf("\n");
    printf("1. Drink ......... $3 [+2 HP]");
    printf("\n");
    printf("2. Beer .......... $1 [+1 HP]");
    printf("\n");
    printf("3. Soup .......... $5 [+4 HP]");
    printf("\n");
    printf("4. Chicken ....... $8 [+10 HP]");
    printf("\n");
    printf("5. Back");
    printf("\n\n");
}

// Obsluha menu hospody, aktualizuje HP a peníze podle volby
int pub_menu() {
    pub_print();

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            printf("That was refreshing! [+2 HP]\n");
            // Zajištění, že HP nepřesáhne 100
            if (hp >= 98) {
                hp = 100;
            } else {
                hp += 2;
            }
            money -= 3;
            break;
        case 2:
            printf("Popici plznička! [+1 HP]\n");
            if (hp >= 99) {
                hp = 100;
            } else {
                hp += 1;
            }
            money -= 1;
            break;
        case 3:
            printf("Amazing! [+4 HP]\n");
            if (hp >= 96) {
                hp = 100;
            } else {
                hp += 4;
            }
            money -= 5;
            break;
        case 4:
            printf("Amazing chiken!\n");
            if (hp >= 90) {
                hp = 100;
            } else {
                hp += 10;
            }
            money -= 8;
            break;
        case 5:
            printf("Leaving th pub!\n");
            break;
        default:
            printf("Invalid choice!\n");
    }

    return choice;
}

// Odpočet času tréninku s vizuálním zobrazením a přidáním XP
int count_down(int time, int add_xp) {
    printf("Training ends in: ");
    for (int i = time; i > 0; i--) {
        int min = i / 60;
        int sec = i % 60;
        printf("\r%02d:%02d  ", min, sec);
        fflush(stdout);
        sleep(1);
    }
    printf("Nice training!\n");
    if (add_xp > 0) {
        printf("+%d XP\n", add_xp);
        xp += add_xp;
    }
}

// Výpis nabídky tréninkového tábora
void training_print() {
    int level = xp / 10;

    printf("Traaining Camp:\n");
    printf("\n");
    printf("--- [HP: %d] --- [$: %d] --- [LVL: %d]", hp, money, level);
    printf("\n");
    printf("How long do you want to train for?");
    printf("\n");
    printf("1. 10s ....... [+5 XP]");
    printf("\n");
    printf("2. 30s ....... [+15 XP]");
    printf("\n");
    printf("3. 1m ........ [+30 XP]");
    printf("\n");
    printf("4. 3m ........ [+90 XP]");
    printf("\n");
    printf("5. 5m ........ [+150 XP]");
    printf("\n");
    printf("6. Custom time .. [+0.5 XP per Second]");
    printf("\n");
    printf("7. Back");
    printf("\n\n");
}

// Obsluha menu tréninkového tábora, volá odpočty a přidává XP
int training_menu() {
    training_print();

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            count_down(10, 5);
            break;
        case 2:
            count_down(30, 15);
            break;
        case 3:
            count_down(60, 30);
            break;
        case 4:
            count_down(180, 90);
            break;
        case 5:
            count_down(300, 150);
            break;
        case 6:
            // Vlastní čas tréninku zadaný uživatelem
            printf("Custom time: ");
            int time;
            scanf("%d", &time);

            printf("Training ends in: ");
            for (int i = time; i > 0; i--) {
                int min = i / 60;
                int sec = i % 60;
                printf("\r%02d:%02d  ", min, sec);
                fflush(stdout);
                sleep(1);
            }
            printf("\nNice training!\n");
            break;
        case 7:
            printf("See you next time!");
            break;
        default:
            printf("Invalid choice!\n");
    }
}

// Prototyp funkce hry pro rekurzivní volání
void game();

// Úvodní obrazovka hry
void welcome() {
    printf("Welcome to the world of C game!");
    printf("\n");
    printf("===============================");
    printf("\n");
    printf("\n");
}

// Výpis hlavního menu (křižovatka)
int cross_menu() {
    printf("Cross: ");
    printf("\n");
    printf("1. Go to pub");
    printf("\n");
    printf("2. Go to Training Camp");
    printf("\n");
    printf("3. Go to Arena");
    printf("\n");
    printf("4. Exit");
    printf("\n\n");

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

// Hlavní funkce programu
int main(void) {
    welcome(); // Zobrazení uvítání
    game();    // Spuštění hry

    return 0;
}

// Hlavní herní smyčka, která volí lokaci podle uživatele
void game(void) {
    int choice = cross_menu();

    switch (choice) {
        case 1:
            printf("You chose to go to pub");
            pub_menu();  // Volání hospody
            break;
        case 2:
            printf("You chose go to Training Camp");
            training_menu(); // Volání tréninku
            break;
        case 3:
            printf("Ypu chose to go to Arena");
            break;
        case 4:
            printf("Thanks for playing!");
            break;
        default:
            printf("Invalid choice");
    }

    print_stats(); // Výpis statistik po akci

    // Pokud hráč nevybral ukončení, hra pokračuje rekurzivně
    if (choice != 4) {
        game();
    }
}
