#include <stdio.h>
#include <unistd.h>

// Proměnné
unsigned short max_hp = 100; // 100HP je maximum
unsigned short hp = 100; // 100HP v základu 10HP = 1 srdce

unsigned short max_shields = 100;
unsigned short shields = 0; // 0 Shields v základu

unsigned int money = 10; // 10 zlatých v základu
int xp = 0; // Zkušenostní body hráče

int eq_sword = 0;


// Funkce pro výpis aktuálních statistik hráče
void print_stats() {
    int level = xp / 10;

    int full_hearts = hp / 10; // Počet plných srdíček
    int empty_hearts = (max_hp - hp) / 10; // Počet prázdných srdíček

    int full_shields = shields / 10;

    printf("\n");
    printf("Level: %d 🔮\n", level);
    printf("Shields: ");
    for (int i = 0; i < full_shields; i++) {
        printf("️🔵");
    }

    printf("\nHP: ");

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
    printf("1. Drink ......... $3 [+20 HP]");
    printf("\n");
    printf("2. Beer .......... $1 [+10 HP]");
    printf("\n");
    printf("3. Soup .......... $5 [+40 HP]");
    printf("\n");
    printf("4. Chicken ....... $8 [+80 HP]");
    printf("\n");
    printf("5. Small Shield Potion ....... $4 [+20 Shields]");
    printf("\n");
    printf("6. Big Shield Potion ......... $12 [+60 Shields]");
    printf("\n");
    printf("7. Back");
    printf("\n\n");
}

void stats_add(int add_hp, int pay_money, int add_shield) {
    // Zajištění, že HP nepřesáhne 100
    if (hp >= 90) {
        hp = 100;
    } else {
        hp += add_hp;
    }

    if (shields >= 98) {
        shields = 100;
    } else {
        shields += add_shield;
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
            stats_add(20, 3, 0);
            break;
        case 2:
            printf("Popici plznička! [+10 HP]\n");
            stats_add(10, 1, 0);
            break;
        case 3:
            printf("Amazing! [+40 HP]\n");
            stats_add(40, 5, 0);
            break;
        case 4:
            printf("Amazing chicken! [+80 HP]\n");
            stats_add(80, 8, 0);
            break;
        case 5:
            printf("I feel stronger! [+20 Shields]\n");
            stats_add(0, 4, 20);
            break;
        case 6:
            printf("That was tasty! [+20 Shields]\n");
            stats_add(0, 12, 60);
            break;
        case 7:
            printf("Leaving the pub!\n");
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

int player_attack(int *ss_wait_time, int *fb_wait_time, int *mjz_wait_time) {
    int punch = 4;
    int sword_slash = 10;
    int fireball = 30;
    int mrd_jak_zmrd = 60;

    int level = xp / 10;

    int attack_choice = 0;
    int valid_choice = 0;

    while (!valid_choice) {
        printf("1. Punch .......... [Damage 4HP]\n");
        printf("2. Sword Slash .... [Damage 10HP]\n");
        printf("3. Fireball ....... [Damage 30HP]\n");
        printf("4. Mrd jak zmrd ... [Damage 60HP]\n");
        if (level >= 5) {
            printf("5. Ultimate Sword Slash ... [Damage 75HP]\n");
        } else if (level < 5) {
            printf("5. -- You need level 5 to unlock! --\n");
        }

        if (level >= 10) {
            printf("6. Arcane Spell ... [Damage 95HP]\n");
        } else if (level < 10) {
            printf("6. -- You need level 10 to unlock! --\n");
        }

        if (level >= 35) {
            printf("7. Destroyer punch ... [Damage 150HP]\n");
        } else if (level < 35) {
            printf("7. -- You need level 35 to unlock! --\n");
        }

        printf("Your choice: ");
        scanf("%d", &attack_choice);
        printf("\n");

        switch (attack_choice) {
            case 1:
                valid_choice = 1;
                return punch;
            case 2:
                if (*ss_wait_time > 0) {
                    printf("You can use this attack again in %d rounds\n\n", *ss_wait_time);
                } else {
                    *ss_wait_time = 2;
                    valid_choice = 1;
                    printf("You used Sword Slash!\n\n");
                    return sword_slash;
                }
                break;
            case 3:
                if (*fb_wait_time > 0) {
                    printf("You can use this attack again in %d rounds\n\n", *fb_wait_time);
                } else {
                    *fb_wait_time = 3;
                    valid_choice = 1;
                    printf("You used Fireball!\n\n");
                    return fireball;
                }
                break;
            case 4:
                if (*mjz_wait_time > 0) {
                    printf("You can use this attack again in %d rounds\n\n", *mjz_wait_time);
                } else {
                    *mjz_wait_time = 5;
                    valid_choice = 1;
                    printf("You used Mrd jak Zmrd!\n\n");
                    return mrd_jak_zmrd;
                }
                break;
            default:
                printf("Invalid choice!\n\n");
        }
    }

    return 0;
}

void attacks(int monster_hp, int monster_attack, char monster_name[], int monster_reward, int monster_xp) {
    int attack_turn = 1;
    int ss_wait_time = 1;
    int fb_wait_time = 2;
    int mjz_wait_time = 4;

    printf("You're fighting with %s!\n", monster_name);

    while (hp > 0 && monster_hp > 0) {
        if (attack_turn % 2 == 1) {
            printf("Your turn, Attack!\n");

            int damage = player_attack(&ss_wait_time, &fb_wait_time, &mjz_wait_time);
            switch (eq_sword) {
                case 1:
                    damage += 3;
                    break;
                case 2:
                    damage += 8;
                    break;
                case 3:
                    damage += 14;
                    break;
                case 4:
                    damage += 50;
                    break;
                case 5:
                    damage += 400;
                    break;
            }
            if (damage > 0) {
                monster_hp -= damage;
                ss_wait_time -= 1;
                fb_wait_time -= 1;
                mjz_wait_time -= 1;
                if (ss_wait_time < 0) ss_wait_time = 0;
                if (fb_wait_time < 0) fb_wait_time = 0;
                if (mjz_wait_time < 0) mjz_wait_time = 0;
            }

            printf("Monster HP: %d\n\n", monster_hp);
        } else {
            printf("The %s is fighting back!\n", monster_name);
            if (monster_attack > shields) {
                hp -= monster_attack - shields;
                shields = 0;
            } else {
                shields -= monster_attack;
            }

            print_stats();
        }
        attack_turn++;
    }

    if (hp <= 0) {
        printf("You have been defeated!\n");
    } else {
        printf("You defeated the %s!\n", monster_name);
        money += monster_reward;
        xp += monster_xp;
    }

    attack_turn = 1;
}

void arena_menu() {
    int level = xp / 10; // výpočet úrovně na základě XP

    printf("\n-- Who do you want to fight with? --\n");
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
            attacks(10, 10, "Slime", 1, 2);
            break;
        case 2:
            attacks(25, 20, "Skeleton", 3, 8);
            break;
        case 3:
            attacks(50, 35, "NEGR", 10, 16);
            break;
        case 4:
            attacks(150, 25, "Martin", 20, 32);
            break;
        case 5:
            if (level >= 10) {
                attacks(300, 40, "Hangárová Držka", 50, 80);
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


// Blacksmith

void blacksmith_print(int level) {
    printf("\n");
    printf("-- Welcome to the Blacksmith --");
    printf("\n");
    printf("1. Bronze sword ........ 18$ [+3 Damage]");
    printf("\n");
    printf("2. Iron sword .......... 35$ [+8 Damage]");
    printf("\n");
    printf("3. Ascended sword ...... 55$ [+14 Damage]");
    printf("\n");
    printf("4. The beast sword ..... 180$ [+50 Damage]");
    printf("\n");
    if (level >= 50) {
        printf("5. This is unfair (Rubinium sword) ..... 500$ [+400 Damage]");
    } else if (level < 50) {
        printf("5. -- You need level 50 to unlock this sword --");
    }
    printf("\n");
    printf("6. Exit");
    printf("\n");
}

void sword_buy(int sword_cost, int sword_level) {
    if (money >= sword_cost) {
        money -= sword_cost;
        eq_sword = sword_level;
    } else {
        printf("You don't have enough money!");
    }
}

void blacksmith_menu() {
    int level = xp / 10;

    blacksmith_print(level);

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            sword_buy(18, 1);
            break;
        case 2:
            sword_buy(35, 2);
            break;
        case 3:
            sword_buy(55, 3);
            break;
        case 4:
            sword_buy(180, 4);
            break;
        case 5:
            if (level >= 50) {
                sword_buy(500, 5);
            } else {
                printf("Your level is too low!");
            }
            break;
        case 6:
            printf("Goodbye.");
            break;
        default:
            printf("Invalid choice");
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
    printf("4. Go to Blacksmith");
    printf("\n");
    printf("5. Exit");
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
            printf("You chose to go to Arena");
            arena_menu();
            break;
        case 4:
            printf("You chose go to the Blacksmith");
            blacksmith_menu();
            break;
        case 5:
            printf("Thanks for playing!");
            break;
        default:
            printf("Invalid choice");
    }
    print_stats(); // Výpis statistik po akci


    // Pokud hráč nevybral ukončení, hra pokračuje rekurzivně
    if (choice != 5) {
        game();
    }
}
