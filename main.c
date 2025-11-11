#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // needed for strcmp


// ==========================================
//          Hlavní proměnné hry
// ==========================================

int max_hp = 100; // Maximální počet životů, které hráč může mít
int hp = 100; // Aktuální počet životů hráče (10HP = 1 srdce)

int max_shields = 100; // Maximální kapacita štítů
int shields = 0; // Aktuální hodnota štítů hráče

int max_armour = 100; // Maximální hodnota brnění
int armour = 0; // Aktuální hodnota brnění hráče

int max_stamina = 100;
int stamina = 100;

unsigned int money = 10000; // Počáteční množství peněz hráče
int xp = 3000; // Aktuální množství zkušenostních bodů (XP) hráče

int eq_sword = 0; // Úroveň nebo typ meče, který má hráč vybavený
int eq_armour = 0; // Úroveň nebo typ brnění, které má hráč vybavené

const int sword_bonus[] = {0, 3, 8, 14, 50, 400};


// Quest variables

int slime_kills = 0;
int skeleton_kills = 0;
int Golem_kills = 0;
int Martin_kills = 0;
int Mira_kills = 0;

int time_trained = 0;


// Funkce pro výpis aktuálních statistik hráče

// Funkce pro zobrazení aktuálních životů hráče jako srdíčka
void print_hp() {
    int full_hearts = hp / 10; // Počet plných srdíček
    int empty_hearts = (max_hp - hp) / 10; // Počet prázdných srdíček

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

// Funkce pro zobrazení aktuálních štítů hráče jako srdíčka
void print_shields() {
    int full_shields = shields / 10;
    int empty_shields = (max_shields - shields) / 10;

    printf("Shields: ");

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
    printf("Armour: ");

    for (int i = 0; i < full_armour; i++) {
        printf("🔒");
    }

    printf(" (%d/%d)\n", armour, max_armour); // zobrazí číselně Armour
}

void print_stamina() {
    int full_stamina = stamina / 10;
    int empty_stamina = (max_stamina - stamina) / 10;

    printf("Stamina: \n");

    for (int i = 0; i < full_stamina; i++) {
        printf("⚡️");
    }

    for (int i = 0; i < empty_stamina; i++) {
        printf("");
    }
}

// Funkce pro vypsání všech statistik hráče (úroveň, štíty, brnění, HP, peníze)
void print_stats() {
    int level = xp / 10;

    printf("\n");
    printf("Level: %d 🔮\n", level);

    print_shields();
    print_armour();
    print_hp();
    print_stamina();
}

// Funkce pro nastavení hodnoty brnění podle úrovně vybaveného brnění
void set_armour() {
    switch (eq_armour) {
        case 1:
            armour = 10;
            break;
        case 2:
            armour = 30;
            break;
        case 3:
            armour = 60;
            break;
        case 4:
            armour = 100;
            break;
        default:
            armour += 0;
    }
}


// ====================
// Quests
// ====================


void complete_quest(int quest_number) {
    switch (quest_number) {
        case 1: // Kill 5 Slimes
            if (slime_kills >= 5) {
                printf("Quest completed: Kill 5 Slimes! [+30 XP, +12 Money]\n");
                xp += 30;
                money += 12;
                slime_kills = 0; // Reset counter to prevent repeating reward
            } else {
                printf("Quest not completed yet! Slimes killed: %d/5\n", slime_kills);
            }
            break;
        case 2: // Train for 2 minutes
            if (time_trained >= 120) {
                printf("Quest completed: Train for 2 minutes! [+40 XP, +20 Money]\n");
                xp += 40;
                money += 20;
                time_trained = 0; // Reset counter
            } else {
                printf("Quest not completed yet! Time trained: %d/120 seconds\n", time_trained);
            }
            break;
        case 3: // Kill Mira the Devourer
            if (Mira_kills >= 1) {
                printf("Quest completed: Kill Mira the Devourer! [+200 XP, +120 Money]\n");
                xp += 200;
                money += 120;
                Mira_kills = 0; // Reset counter
            } else {
                printf("Quest not completed yet!\n");
            }
            break;
        default:
            printf("Invalid quest number!\n");
    }
}

void quests_menu() {
    printf("\n-- The Questboard --");
    printf("Complete quests to earn XP and Money.\n");

    if (slime_kills >= 5) {
        printf("1. Kill 5 Slimes ... [Ready to claim!]\n");
    } else {
        printf("1. Kill 5 Slimes ... [Progress: %d/5]\n", slime_kills);
    }

    if (time_trained >= 120) {
        printf("2. Train for 2 Minutes ... [Ready to claim!]\n");
    } else {
        printf("2. Train for 2 Minutes ... [Progress: %d/120 seconds]\n", time_trained);
    }

    if (Mira_kills >= 1) {
        printf("3. Kill Mira the Devourer ... [Ready to claim!]\n");
    } else {
        printf("3. Kill Mira the Devourer ... [Not done]\n");
    }

    printf("4. Back\n");
    printf("Choose a quest to claim reward: ");
    int choice;
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3) {
        complete_quest(choice);
    } else {
        printf("Returning...\n");
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
    printf("6. Big Shield Potion ......... $10 [+60 Shields]");
    printf("\n");
    printf("7. Back");
    printf("\n\n");
}

// Funkce pro přidání HP, odečtení peněz a přidání štítů po nákupu v hospodě
void stats_add(int add_hp, int pay_money, int add_shield) {
    // Ošetření maximální hodnoty HP a štítů
    // Zajištění, že HP nepřesáhne 100
    hp += add_hp;
    if (hp > max_hp) {
        hp = max_hp;
    }

    if (hp == max_hp && add_hp > 0) {
        printf("Your HP is already full!\n");
    }

    shields += add_shield;
    if (shields > max_shields) {
        shields = max_shields;
    }

    if (shields == max_shields && add_shield > 0) {
        printf("Your Shields are already full!\n");
    }

    if (money >= pay_money) {
        money -= pay_money;
    } else {
        printf("You don’t have enough money!\n");
    }
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
            stats_add(20, 2, 0);
            break;
        case 2:
            printf("Popici plznička! [+10 HP]\n");
            stats_add(10, 1, 0);
            break;
        case 3:
            printf("Amazing! [+40 HP]\n");
            stats_add(40, 4, 0);
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
            printf("That was tasty! [+60 Shields]\n");
            stats_add(0, 10, 60);
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
        time_trained++;
    }
    printf("Nice training!\n");
    if (add_xp > 0) {
        printf("+%d XP\n", add_xp);
        xp += add_xp;
        complete_quest(2);
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
                time_trained++;
            }
            complete_quest(2);
            xp += time * 0.5;

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

    printf("1. Punch .......... [Damage 4HP | -5 Stamina]\n");

    if (level >= 3) {
        printf("2. Sword Slash .... [Damage 10HP | -10 Stamina]\n");
    } else {
        printf("2. -- You need level 3 to unlock --\n");
    }

    if (level >= 8) {
        printf("3. Fireball ....... [Damage 30HP | -20 Stamina]\n");
    } else {
        printf("3. -- You need level 8 to unlock! --\n");
    }

    if (level >= 10) {
        printf("4. Mrd jak zmrd ... [Damage 60HP | -40 Stamina]\n");
    } else {
        printf("4. -- You need level 10 to unlock! --\n");
    }

    if (level >= 15) {
        printf("5. Ultimate Sword Slash ... [Damage 100HP | -50 Stamina]\n");
    } else {
        printf("5. -- You need level 15 to unlock! --\n");
    }

    if (level >= 20) {
        printf("6. Arcane Spell ... [Damage 145HP | -60 Stamina]\n");
    } else {
        printf("6. -- You need level 20 to unlock! --\n");
    }

    if (level >= 35) {
        printf("7. Destroyer punch ... [Damage 350HP | -80 Stamina]\n");
    } else {
        printf("7. -- You need level 35 to unlock! --\n");
    }
}

int use_stamina(int cost) {
    if (stamina < cost) {
        if (stamina <= 5) {
            printf("You have no stamina left!\n");
            return 0;
        }
        printf("⚠️ Not enough stamina! (%d/%d)\n", stamina, max_stamina);
        return 0;
    }
    stamina -= cost;
    printf("Stamina left: %d/%d\n", stamina, max_stamina);
    return 1;
}

// Funkce pro volbu útoku hráče v aréně, řeší cooldowny a vrací sílu útoku
int player_attack(const int *p_stamina, const int *ss_stamina, const int *fb_stamina,
                  const int *mjz_stamina, const int *ultss_stamina, const int *as_stamina, const int *dp_stamina) {
    int level = xp / 10;
    // 1 level == 0.5 damage
    int damage_bonus = level / 2;

    int attack_choice = 0;

    // Smyčka dokud hráč nevybere platný útok (nebo cooldown)
    while (1) {
        attack_print();

        printf("Your choice: ");
        scanf("%d", &attack_choice);
        printf("\n");

        switch (attack_choice) {
            case 1:
                if (use_stamina(5)) return 4 + damage_bonus;
                break;
            case 2:
                if (level >= 3 && use_stamina(10)) return 10 + damage_bonus;
                break;
            case 3:
                if (level >= 8 && use_stamina(20)) return 30 + damage_bonus;
                break;
            case 4:
                if (level >= 10 && use_stamina(40)) return 60 + damage_bonus;
                break;
            case 5:
                if (level >= 15 && use_stamina(50)) return 100 + damage_bonus;
                break;
            case 6:
                if (level >= 20 && use_stamina(60)) return 145 + damage_bonus;
                break;
            case 7:
                if (level >= 35 && use_stamina(80)) return 350 + damage_bonus;
                break;
            default:
                printf("Invalid choice!\n\n");
                break;
        }
        if (stamina <= 0) {
            printf("You collapse from exhaustion...\n");
            return 0;
        }
    }
}

// Funkce pro průběh souboje s monstrem v aréně
void attacks(int monster_hp, int min, int max, char monster_name[], int monster_reward, int monster_xp) {
    int attack_turn = 1;

    int p_stamina = 5;
    int ss_stamina = 10;
    int fb_stamina = 20;
    int mjz_stamina = 40;
    int ultss_stamina = 50;
    int as_stamina = 60;
    int dp_stamina = 80;

    int level = xp / 10;
    int monster_attack = rand() % (max - min + 1) + min;

    printf("You're fighting with %s!\n", monster_name);

    // Hlavní smyčka souboje: střídání hráč/monstrum, dokud někdo nepadne
    while (hp > 0 && monster_hp > 0) {
        if (attack_turn % 2 == 1) {
            // Hráč útočí
            printf("Your turn, Attack!\n");

            int damage = player_attack(&p_stamina, &ss_stamina, &fb_stamina, &mjz_stamina, &ultss_stamina, &as_stamina,
                                       &dp_stamina);
            if (stamina <= 0) {
                printf("You collapse from exhaustion...\n");
                printf("Final stats:\n");
                print_stats();
                return;
            }

            if (rand() % 100 < 10) {
                // 10% šance
                printf("Critical hit! 💥\n");
                damage *= 2;
                printf("critical damage");
            }
            // Přičtení bonusového poškození podle meče
            switch (eq_sword) {
                case 1:
                    damage += sword_bonus[eq_sword];
                    break;
                case 2:
                    damage += sword_bonus[eq_sword];
                    break;
                case 3:
                    damage += sword_bonus[eq_sword];
                    break;
                case 4:
                    damage += sword_bonus[eq_sword];
                    break;
                case 5:
                    damage += sword_bonus[eq_sword];
                    break;
                default:
                    damage += sword_bonus[eq_sword];
            }
            if (damage > 0) {
                monster_hp -= damage;
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
                    if (hp < 0) hp = 0;
                    armour = 0;
                } else {
                    // Brnění pohltí vše
                    armour -= remaining_damage;
                }
            } else {
                // Štíty pohltí vše
                shields -= monster_attack;
            }
            if (hp < 0) hp = 0;
            if (hp > 0) {
                print_stats();
            }
        }

        // Regenerate small amount of stamina only when it's the monster's turn
        if (attack_turn % 2 == 0) {
            if (level >= 3 && level < 5) {
                stamina += 10;
            } else if (level >= 5 && level < 10) {
                stamina += 15;
            } else if (level >= 10 && level < 15) {
                stamina += 20;
            } else if (level >= 15 && level < 20) {
                stamina += 40;
            }
            if (stamina > max_stamina) stamina = max_stamina;
        }

        attack_turn++;
    }

    // Vyhodnocení výsledku souboje
    if (hp <= 0) {
        printf("You have been defeated!\n");
        printf("Final stats: \n");
        print_stats();
    } else {
        printf("You defeated the %s!\n", monster_name);
        money += monster_reward;
        xp += monster_xp;

        // restore only part of stamina after fight
        stamina = 100;
        if (stamina > max_stamina) stamina = max_stamina;
    }

    // Add to kill counts
    if (strcmp(monster_name, "Slime") == 0) {
        slime_kills++;
        complete_quest(1); // check Slime quest
    } else if (strcmp(monster_name, "Skeleton") == 0) {
        skeleton_kills++;
    } else if (strcmp(monster_name, "Golem") == 0) {
        Golem_kills++;
    } else if (strcmp(monster_name, "Martin") == 0) {
        Martin_kills++;
    } else if (strcmp(monster_name, "Mira") == 0) {
        Mira_kills++;
        complete_quest(3); // check Mira quest
    }
}

// Funkce pro zobrazení a zpracování menu arény (výběr soupeře)
void arena_menu() {
    int level = xp / 10; // výpočet úrovně na základě XP

    printf("\n-- Who do you want to fight with? --\n");
    printf("1. Slime ...... 10HP [+5 Money, 5 - 15 DMG]\n");
    printf("2. Skeleton ... 25HP [+10 Money, 10 - 30 DMG]\n");
    printf("3. Golem ....... 50HP [+20 Money, 20 - 40 DMG]\n");
    printf("4. Martin ..... 150HP [+45 Money, 15 - 35 DMG]\n");
    if (level >= 8) {
        printf("5. Hangárová Držka ..... 300HP [+75 Money, 30 - 60 DMG]\n");
    } else {
        printf("5. -- You need level 10 to unlock! --\n");
    }

    if (level >= 20) {
        printf("6. Mira the devourer ..... 500HP [+120 Money, 50 - 80 DMG]\n");
    } else {
        printf("6. -- You need level 20 to unlock! --\n");
    }

    if (level >= 80) {
        printf("7. Ničitel světů Alfamus ..... 3000HP [+250 Money, 70 - 120 DMG]\n");
    } else {
        printf("7. -- You need level 80 to unlock! --\n");
    }

    printf("8. Back\n");

    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    // Zpracování volby soupeře v aréně
    switch (choice) {
        case 1:
            attacks(10, 5, 15, "Slime", 5, 5);
            break;
        case 2:
            attacks(25, 10, 30, "Skeleton", 10, 15);
            break;
        case 3:
            attacks(50, 20, 40, "Golem", 20, 25);
            break;
        case 4:
            attacks(150, 15, 35, "Martin", 45, 40);
            break;
        case 5:
            if (level >= 8) {
                attacks(300, 30, 60, "Hangárová Držka", 75, 80);
            } else {
                printf("5. -- You need level 8 to unlock! --\n");
            }
            break;
        case 6:
            if (level >= 20) {
                attacks(500, 50, 80, "Mira the devourer", 120, 150);
            } else {
                printf("6. -- You need level 20 to unlock! --\n");
            }
            break;
        case 7:
            if (level >= 80) {
                attacks(3000, 70, 110, "Ničitel světů Alfamus", 250, 300);
            } else {
                printf("7. -- You need level 80 to unlock! --\n");
            }
            break;
        case 8:
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
    printf("-- Welcome to the Blacksmith -- [%d] \n", money);
    printf("-- Swords --\n");

    if (eq_sword >= 1) {
        printf("-- Already bought --\n");
    } else {
        printf("1. Bronze sword ........ 18$ [+3 Damage]\n");
    }

    if (eq_sword >= 2) {
        printf("-- Already bought --\n");
    } else {
        printf("2. Iron sword .......... 35$ [+8 Damage]\n");
    }

    if (eq_sword >= 3) {
        printf("-- Already bought --\n");
    } else {
        printf("3. Ascended sword ...... 55$ [+14 Damage]\n");
    }

    if (eq_sword >= 4) {
        printf("-- Already bought --\n");
    } else {
        printf("4. The beast sword ..... 180$ [+50 Damage]\n");
    }

    if (level >= 50) {
        printf("5. This is unfair (Rubinium sword) ..... 500$ [+400 Damage]\n");
    } else {
        printf("5. -- You need level 50 to unlock this sword --\n");
    }
    printf("-- Armour --\n");
    printf("6. Bronze armour ..... 12$ [+10 Armour]\n");
    printf("7. Iron armour ....... 25$ [+30 Armour]\n");
    printf("8. Diamond armour .... 40$ [+60 Armour]\n");
    if (level >= 25) {
        printf("9. Awakened armour ... 150$ [+100HP]\n");
    } else {
        printf("9. -- You need level 25 to unlock this sword --\n");
    }
    printf("-- Armour Repair --\n");
    printf("10. Repair ........ [4$, 8$, 12$, 16$]");

    printf("\n11. back");
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
        set_armour();
    } else {
        printf("You don't have enough money!");
    }
}

void armour_repair(int repair_cost) {
    if (money < repair_cost) {
        printf("You don't have enough money to repair your armour!\n");
        return;
    }

    money -= repair_cost;

    switch (eq_armour) {
        case 1:
            armour = 10;
            break;
        case 2:
            armour = 30;
            break;
        case 3:
            armour = 60;
            break;
        case 4:
            armour = 100;
            break;
        default:
            printf("You don't have any armour to repair!\n");
            return;
    }

    printf("Your armour has been repaired!\n");
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
            armour_buy(25, 2);
            break;
        case 8:
            armour_buy(40, 3);
            break;
        case 9:
            armour_buy(150, 4);
            break;
        case 10:
            armour_repair(eq_armour * 4);
            break;
        case 11:
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
    printf("\nCross: ");
    printf("\n");
    printf("1. Go to pub");
    printf("\n");
    printf("2. Go to Training Camp");
    printf("\n");
    printf("3. Go to Arena");
    printf("\n");
    printf("4. Go to Blacksmith");
    printf("\n");
    printf("5. Go to Questboard");
    printf("\n");
    printf("6. Exit");
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
    int choice;
    do {
        choice = cross_menu();
        switch (choice) {
            case 1: pub_menu();
                break;
            case 2: training_menu();
                break;
            case 3: arena_menu();
                break;
            case 4: blacksmith_menu();
                break;
            case 5: quests_menu();
                break;
            case 6: printf("Thanks for playing!\n");
                break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);
}
