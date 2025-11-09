#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
//          Hlavní proměnné hry
// ==========================================

unsigned short max_hp = 100; // Maximální počet životů, které hráč může mít
unsigned short hp = 100; // Aktuální počet životů hráče (10HP = 1 srdce)

unsigned short max_shields = 100; // Maximální kapacita štítů
unsigned short shields = 0; // Aktuální hodnota štítů hráče

unsigned short max_armour = 100; // Maximální hodnota brnění
unsigned short armour = 0; // Aktuální hodnota brnění hráče

unsigned int money = 10; // Počáteční množství peněz hráče
int xp; // Aktuální množství zkušenostních bodů (XP) hráče

int eq_sword = 0; // Úroveň nebo typ meče, který má hráč vybavený
int eq_armour = 0; // Úroveň nebo typ brnění, které má hráč vybavené


// Funkce pro výpis aktuálních statistik hráče

// Funkce pro zobrazení aktuálních životů hráče jako srdíčka
void print_hp() {
    int full_hearts = hp / 10; // Počet plných srdíček
    int empty_hearts = (max_hp - hp) / 10; // Počet prázdných srdíček

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

// Funkce pro zobrazení aktuálních štítů hráče jako srdíčka
void print_shields() {
    int full_shields = shields / 10;
    int empty_shields = (max_shields - shields) / 10;

    printf("\nShields: ");

    for (int i = 0; i < full_shields; i++) {
        printf("💙");
    }
    for (int i = 0; i < empty_shields; i++) {
        printf("🩶");
    }
    printf(" (%d/%d)\n", shields, max_shields); // zobrazí číselně Shields
}

// Funkce pro zobrazení aktuálního brnění hráče jako zámky
void print_armour() {
    int full_armour = armour / 10;

    // Vykreslení brnění
    printf("\nArmour: ");

    for (int i = 0; i < full_armour; i++) {
        printf("🔒");
    }

    printf(" (%d/%d)\n", armour, max_armour); // zobrazí číselně Armour
}

// Funkce pro vypsání všech statistik hráče (úroveň, štíty, brnění, HP, peníze)
void print_stats() {
    int level = xp / 10;

    printf("\n");
    printf("Level: %d 🔮\n", level);

    print_shields();
    print_armour();
    print_hp();
}

// Funkce pro nastavení hodnoty brnění podle úrovně vybaveného brnění
void set_shields() {
    switch (eq_armour) {
        case 1:
            armour += 10;
            break;
        case 2:
            armour += 25;
            break;
        case 3:
            armour += 46;
            break;
        case 4:
            armour += 100;
            break;
        default:
            armour += 0;
    }
}


// =========================
//      Hospoda (Pub)
// =========================

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

// Funkce pro přidání HP, odečtení peněz a přidání štítů po nákupu v hospodě
void stats_add(int add_hp, int pay_money, int add_shield) {
    // Ošetření maximální hodnoty HP a štítů
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

// Funkce pro obsluhu menu hospody, zpracuje volbu a upraví statistiky
int pub_menu() {
    pub_print();

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    // Zpracování volby uživatele v hospodě
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


// =========================
//    Tréninkový tábor
// =========================

// Funkce pro odpočet času tréninku, zobrazení průběhu a přidání XP
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

// Funkce pro vypsání nabídky tréninkového tábora
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

// Funkce pro obsluhu menu tréninkového tábora, volá odpočty a přidává XP
void training_menu() {
    training_print();

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    // Zpracování volby uživatele v tréninkovém táboře
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


// =========================
//         Aréna
// =========================

// Funkce pro zobrazení nabídky útoků hráče v aréně podle úrovně
void attack_print() {
    int level = xp / 10;

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
}

// Funkce pro volbu útoku hráče v aréně, řeší cooldowny a vrací sílu útoku
int player_attack(int *ss_wait_time, int *fb_wait_time, int *mjz_wait_time) {
    int punch = 4;
    int sword_slash = 10;
    int fireball = 30;
    int mrd_jak_zmrd = 60;

    int attack_choice = 0;
    int valid_choice = 0;

    // Smyčka dokud hráč nevybere platný útok (nebo cooldown)
    while (!valid_choice) {
        attack_print();

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
}

// Funkce pro průběh souboje s monstrem v aréně
void attacks(int monster_hp, int min, int max, char monster_name[], int monster_reward, int monster_xp) {
    int attack_turn = 1;
    int ss_wait_time = 1;
    int fb_wait_time = 2;
    int mjz_wait_time = 4;
    int monster_attack = rand() % (max - min + 1) + min;

    printf("You're fighting with %s!\n", monster_name);

    // Hlavní smyčka souboje: střídání hráč/monstrum, dokud někdo nepadne
    while (hp > 0 && monster_hp > 0) {
        if (attack_turn % 2 == 1) {
            // Hráč útočí
            printf("Your turn, Attack!\n");

            int damage = player_attack(&ss_wait_time, &fb_wait_time, &mjz_wait_time);
            // Přičtení bonusového poškození podle meče
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
                default:
                    damage += 0;
            }
            if (damage > 0) {
                monster_hp -= damage;
                // Snížení cooldownů útoků
                ss_wait_time -= 1;
                fb_wait_time -= 1;
                mjz_wait_time -= 1;
                if (ss_wait_time < 0) ss_wait_time = 0;
                if (fb_wait_time < 0) fb_wait_time = 0;
                if (mjz_wait_time < 0) mjz_wait_time = 0;
            }

            printf("Monster HP: %d\n\n", monster_hp);
        } else {
            // Monstrum útočí na hráče
            printf("The %s is fighting back!\n", monster_name);
            if (monster_attack > shields) {
                // Poškození projde skrz štíty
                int remaining_damage = monster_attack - shields;
                shields = 0;

                if (remaining_damage > armour) {
                    // Brnění pohltí část poškození
                    hp -= remaining_damage - armour;
                    armour = 0;
                } else {
                    // Brnění pohltí vše
                    armour -= remaining_damage;
                }
            } else {
                // Štíty pohltí vše
                shields -= monster_attack;
            }
            print_stats();
        }
        attack_turn++;
    }

    // Vyhodnocení výsledku souboje
    if (hp <= 0) {
        printf("You have been defeated!\n");
    } else {
        printf("You defeated the %s!\n", monster_name);
        // Odměna za výhru
        money += monster_reward;
        xp += monster_xp;
    }
}

// Funkce pro zobrazení a zpracování menu arény (výběr soupeře)
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

    // Zpracování volby soupeře v aréně
    switch (choice) {
        case 1:
            attacks(10, 5, 15, "Slime", 1, 2);
            break;
        case 2:
            attacks(25, 10, 35, "Skeleton", 3, 8);
            break;
        case 3:
            attacks(50, 20, 40, "NEGR", 10, 16);
            break;
        case 4:
            attacks(150, 15, 35, "Martin", 20, 32);
            break;
        case 5:
            if (level >= 10) {
                attacks(300, 30, 60, "Hangárová Držka", 50, 80);
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


// =========================
//        Kovář (Blacksmith)
// =========================

// Funkce pro vypsání nabídky zbraní a brnění u kováře
void blacksmith_print(int level) {
    printf("\n");
    printf("-- Welcome to the Blacksmith --\n");
    printf("-- Swords --\n");
    printf("1. Bronze sword ........ 18$ [+3 Damage]\n");
    printf("2. Iron sword .......... 35$ [+8 Damage]\n");
    printf("3. Ascended sword ...... 55$ [+14 Damage]\n");
    printf("4. The beast sword ..... 180$ [+50 Damage]\n");
    if (level >= 50) {
        printf("5. This is unfair (Rubinium sword) ..... 500$ [+400 Damage]\n");
    } else if (level < 50) {
        printf("5. -- You need level 50 to unlock this sword --\n");
    }
    printf("-- Armour --\n");
    printf("6. Bronze armour ..... 12$ [+10 Armour]\n");
    printf("7. Iron armour ....... 28$ [+25 Armour]\n");
    printf("8. Diamond armour .... 50$ [+46 Armour]\n");
    if (level >= 25) {
        printf("9. Awakened armour ... 150$ [+100HP]\n");
    } else if (level < 25) {
        printf("9. -- You need level 25 to unlock this sword --\n");
    }
    printf("10. Exit\n");
    printf("\n");
}

// Funkce pro nákup meče
void sword_buy(int sword_cost, int sword_level) {
    if (money >= sword_cost) {
        money -= sword_cost;
        eq_sword = sword_level;
    } else {
        printf("You don't have enough money!");
    }
}

// Funkce pro nákup brnění
void armour_buy(int armour_cost, int armour_level) {
    if (money >= armour_cost) {
        money -= armour_cost;
        eq_armour = armour_level;
        set_shields();
    } else {
        printf("You don't have enough money!");
    }
}

// Funkce pro zobrazení a zpracování menu u kováře
void blacksmith_menu() {
    int level = xp / 10;

    blacksmith_print(level);

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    // Zpracování volby nákupu u kováře
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

        // Armours
        case 6:
            armour_buy(12, 1);
            break;
        case 7:
            armour_buy(28, 2);
            break;
        case 8:
            armour_buy(50, 3);
            break;
        case 9:
            armour_buy(150, 4);
            break;
        case 10:
            printf("Goodbye.");
            break;
        default:
            printf("Invalid choice");
    }
}


// =========================
//          Hra
// =========================

// Prototyp funkce hry pro rekurzivní volání
void game();

// Funkce pro úvodní obrazovku hry
void welcome() {
    printf("Welcome to the world of C game!");
    printf("\n");
    printf("===============================");
    printf("\n");
    printf("\n");
}

// Funkce pro vypsání hlavního menu (křižovatka)
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

// Hlavní funkce programu, inicializuje hru
int main(void) {
    srand(time(NULL));
    welcome(); // Zobrazení uvítání
    game(); // Spuštění hry

    return 0;
}

// Hlavní herní smyčka, která zpracovává volbu lokace a volá příslušné funkce
void game(void) {
    int choice = cross_menu();

    // Zpracování volby lokace hráče
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
