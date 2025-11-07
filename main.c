#include <stdio.h>
#include <unistd.h>

// Proměnné
unsigned short max_hp = 100; // 10HP je maximum
unsigned short hp = 100; // 10HP v Klaudiusz
unsigned int money = 10; // 10 zlatých v základu
int xp = 0; // Zkušenostní body hráče


// Funkce pro výpis aktuálních statistik hráče
void print_stats() {
    int level = xp / 10;
    int full_hearts = hp / 10;         // Počet plných srdíček
    int empty_hearts = (max_hp - hp) / 10; // Počet prázdných srdíček

    printf("\n");
    printf("Level: %d 🔮\n", level);
    printf("HP: ");

    // Vykreslení plných životů
    for (int i = 0; i < full_hearts; i++) {
        printf("❤️");
    }

    // Vykreslení prázdných životů
    for (int i = 0; i < empty_hearts; i++) {
        printf("🩶");
    }

    printf(" (%d/%d)\n", hp, max_hp); // zobrazí číselně HP
    printf("Money: %d 💵\n", money);
}


// Pub functions

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

void stats_add(int add_hp, int pay_money) {
    // Zajištění, že HP nepřesáhne 100
    if (hp >= 98) {
        hp = 100;
    } else {
        hp += add_hp;
    }

    money -= pay_money;
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
            printf("That was refreshing! [+20 HP]\n");
            stats_add(20, 3);
            break;
        case 2:
            printf("Popici plznička! [+10 HP]\n");
            stats_add(10, 1);
            break;
        case 3:
            printf("Amazing! [+40 HP]\n");
            stats_add(40, 5);
            break;
        case 4:
            printf("Amazing chiken! [+80 HP]\n");
            stats_add(80, 8);
            break;
        case 5:
            printf("Leaving th pub!\n");
            break;
        default:
            printf("Invalid choice!\n");
    }

    return choice;
}


// Training Camp functions

// Odpočet času tréninku s vizuálním zobrazením a přidáním XP
void count_down(int time, int add_xp) {
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
void training_menu() {
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


// Arena functions

void attacks(int monster_hp, int monster_attack, char monster_name[]) {
    int attack_turn = 1;
    printf("You're fighting with %s!\n", monster_name);

    while (hp > 0 && monster_hp > 0) {
        if (attack_turn % 2 == 1) {
            printf("Your turn, Attack!\n");
            monster_hp -= 1;
            printf("Monster HP: %d\n\n", monster_hp);
        } else {
            printf("The %s is fighting back!\n", monster_name);
            hp -= monster_attack;
            print_stats();
        }
        attack_turn++;
    }

    if (hp <= 0) {
        printf("You have been defeated!\n");
    } else {
        printf("You defeated the Slime!\n");
        money += 1;
    }

    attack_turn = 1;
}

void arena_menu() {
    int level = xp / 10; // výpočet úrovně na základě XP

    printf("-- Who do you want to fight with? --\n");
    printf("1. Slime ...... 10HP [+1 Money, -1 HP]\n");
    printf("2. Skeleton ... 25HP [+3 Money, -3 HP]\n");
    printf("3. NEGR ....... 50HP [+10 Money, -8 HP]\n");
    printf("4. Martin ..... 150HP [+20 Money, -5 HP]\n");
    if (level >= 10) {
        printf("5. Hangárová Držka ..... 300HP [+50 Money, -20 HP]\n");
    } else {
        printf("5. -- You need level 10 to unlock! --\n");
    }
    printf("6. Back\n");

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            attacks(10, 3, "Slime");
            break;
        case 2:
            attacks(25, 5, "Skeleton");
            break;
        case 3:
            attacks(50, 15, "NEGR");
            break;
        case 4:
            attacks(150, 10, "Martin");
            break;
        case 5:
            if (level >= 10) {
                attacks(300, 20, "Hangárová Držka");
            } else {
                printf("5. -- You need level 10 to unlock! --\n");
            }
            break;
        case 6:
            printf("You're leaving, too scared huh?");
            break;
        default:
            printf("Invalid choice!");
    }
}


// Game

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
    game(); // Spuštění hry

    return 0;
}

// Hlavní herní smyčka, která volí lokaci podle uživatele
void game(void) {
    int choice = cross_menu();

    switch (choice) {
        case 1:
            printf("You chose to go to pub");
            pub_menu(); // Volání hospody
            break;
        case 2:
            printf("You chose go to Training Camp");
            training_menu(); // Volání tréninku
            break;
        case 3:
            printf("Ypu chose to go to Arena");
            arena_menu();
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
