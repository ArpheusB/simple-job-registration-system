#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <errno.h>

#include <unistd.h>

#include <string.h>

#include <ctype.h>



struct Jelentkezes {
    int id;
    char nev[100];
    char cim[100];
    char napok[64];
};

int napok[] = {
    10,
    10,
    10,
    10,
    10,
    10,
    10
};
int nameCheckFunction(char temp[]) {
    char * napok[] = {
        "hetfo",
        "kedd",
        "szerda",
        "csutortok",
        "pentek",
        "szombat",
        "vasarnap"
    };

    int countNapok[7];
    for(int i=0;i<7;i++)
    countNapok[i] = 0;

    char * token;
    char * rest = temp;
    while ((token = strtok_r(rest, " ", & rest))) {
        int isDay = 0;

        for (int i = 0; i < 7; i++) {
            if (strcmp(token, napok[i]) == 0) {
                isDay = 1;
                countNapok[i]++;
                break;
            }
        }
        if (!isDay) {
            printf("Hoppa! Csak helyes napokat adhat meg! \n");
            return 0;
        }
    }

    for (int i = 0; i < 7; i++) {

        if (countNapok[i] > 1) {
            printf("Egy nap csak egyszer szerepelhet! \n");
            return 0;
        }
        
    }
    return 1;

}

char * trim(char * s) {
    char * ptr;
    if (!s)
        return NULL;
    if (! * s)
        return s;
    for (ptr = s + strlen(s) - 1;
        (ptr >= s) && isspace( * ptr); --ptr)
    ;
    ptr[1] = '\0';
    return s;
}

struct Jelentkezes jelentkezes;
struct Jelentkezes jelentkezesek[70];
int db = 0;
///Utility function
int modifyDaysFunction(char * temp, char method) {

    char * token;
    char * rest = temp;
    if (method == 'a') {

        while ((token = strtok_r(rest, " ", & rest))) {
            if (strcmp(token, "hetfo") == 0) {

                if (napok[0] >= 1) {
                    napok[0] -= 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            } else if (strcmp(token, "kedd") == 0) {
                if (napok[1] >= 1) {
                    napok[1] -= 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            } else if (strcmp(token, "szerda") == 0) {
                if (napok[2] >= 1) {
                    napok[2] -= 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }
            } else if (strcmp(token, "csutortok") == 0) {
                if (napok[3] >= 1) {
                    napok[3] -= 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }
            } else if (strcmp(token, "pentek") == 0) {
                if (napok[4] >= 1) {
                    napok[4] -= 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }
            } else if (strcmp(token, "szombat") == 0) {
                if (napok[5] >= 1) {
                    napok[5] -= 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }
            } else if (strcmp(token, "vasarnap") == 0) {
                if (napok[6] >= 1) {
                    napok[6] -= 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }
            }
        }
    } else if (method == 'd' || method == 'm') {
        while ((token = strtok_r(rest, " ", & rest))) {
            if (strcmp(token, "hetfo") == 0) {
                if (napok[0] <= 9) {
                    napok[0] += 1;

                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            } else if (strcmp(trim(token), "kedd") == 0) {
                if (napok[1] <= 9) {
                    napok[1] += 1;
                } else {
                    printf("Sikertelen muvelet. \n");

                    return 0;

                }

            } else if (strcmp(token, "szerda") == 0) {
                if (napok[2] <= 9) {
                    napok[2] += 1;
                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            } else if (strcmp(token, "csutortok") == 0) {
                if (napok[3] <= 9) {
                    napok[3] += 1;
                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            } else if (strcmp(token, "pentek") == 0) {
                if (napok[4] <= 9) {
                    napok[4] += 1;
                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            } else if (strcmp(token, "szombat") == 0) {
                if (napok[5] <= 9) {
                    napok[5] += 1;
                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            } else if (strcmp(token, "vasarnap") == 0) {
                if (napok[6] <= 9) {
                    napok[6] += 1;
                } else {
                    printf("Sikertelen muvelet. \n");
                    return 0;
                }

            }
        }
    }

    return 1;
}


///Utility function
void modifyingTheFile() {

    int f = open("out.txt", O_WRONLY | O_TRUNC);

    for (int i = 0; i < db; i++) {

        if (write(f, & jelentkezesek[i], sizeof(jelentkezesek[i])) != sizeof(jelentkezesek[i])) {
            write(2, "There was an error writing to testfile.txt\n", 43);
            return;
        }
    }
    close(f);
}
void readFunction() {
    int f = open("out.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (f < 0) {
        perror("Error 'cause of reading the file\n");
        exit(1);
    }
    while (read(f, & jelentkezes, sizeof(struct Jelentkezes))) {
        jelentkezesek[db].id = jelentkezes.id;
        strcpy(jelentkezesek[db].nev, jelentkezes.nev);
        strcpy(jelentkezesek[db].cim, jelentkezes.cim);
        strcpy(jelentkezesek[db].napok, jelentkezes.napok);

        char temp[64];
        strcpy(temp, jelentkezesek[db].napok);

        modifyDaysFunction(temp, 'a');

        db++;

    }

    close(f);

}
void printWorksByDay(char * day) {
    printf("Eddigi jelentkezesek adatai: \n");
    if (db == 0)
        printf("eddig nem tortent jelentkezes.");
    for (int i = 0; i < db; i++) {

        char * pch = strstr(jelentkezesek[i].napok, trim(day));

        if (pch) {
            printf("id: %d ", jelentkezesek[i].id);
            printf("\n");
            printf("nev: %s ", jelentkezesek[i].nev);
            printf("\n");
            printf("cim: %s ", jelentkezesek[i].cim);
            printf("\n");
            printf("napok: %s ", jelentkezesek[i].napok);
            printf("\n");
            printf("\n");
            printf("\n");
        }

    }
}
void printFunction() {
    printf("Eddigi jelentkezesek adatai: \n");
    if (db == 0)
        printf("eddig nem tortent jelentkezes.");
    for (int i = 0; i < db; i++) {

        printf("id: %d ", jelentkezesek[i].id);
        printf("\n");
        printf("nev: %s ", jelentkezesek[i].nev);
        printf("\n");
        printf("cim: %s ", jelentkezesek[i].cim);
        printf("\n");
        printf("napok: %s ", jelentkezesek[i].napok);
        printf("\n");
        printf("\n");
        printf("\n");

    }

}
void addFunction() {

    int f = open("out.txt", O_WRONLY | O_TRUNC);
    printf("\nADJA BE AZ ADATOKAT\n");
    printf("Id:%d \n", db);
    jelentkezesek[db].id = db;
    printf("Nev:");
    gets((jelentkezesek[db].nev));
    gets(trim(jelentkezesek[db].nev));
    printf("Cim:");
    gets(trim(jelentkezesek[db].cim));
    printf("Napok:");

    char temp[64];
    char temp_names[64];

    gets(jelentkezesek[db].napok);
    strcpy(temp_names, jelentkezesek[db].napok);
    int answer = nameCheckFunction(temp_names);

    strcpy(temp, jelentkezesek[db].napok);
    if (answer) {
        if (modifyDaysFunction(temp, 'a')) {

            db++;

            modifyingTheFile();
            printf("\nSIKER!\n");
        }

    } else {

        close(f);

        return;
    }

}

void deleteFunction(int index) {
    int exist = 0;
    for (int i = 0; i < db; i++) {
        if (jelentkezesek[i].id == index) {
            exist = 1;
            if (!modifyDaysFunction(jelentkezesek[i].napok, 'd')) {
                return;
            }
            for (int j = i; j < db - 1; j++) {
                jelentkezesek[j] = jelentkezesek[j + 1];
                jelentkezesek[j].id -= 1;;

            }
            break;
        }
    }
    db--;

    modifyingTheFile();
    if (exist) {
        printf(("Sikeres a torles! \n"));

    } else {
        printf("Nincsen ilyen azonositoval rendelkezo jelentkezes. \n");
    }

}
void modifyingFunction(int index) {
    int exist = 0;
    int i=0;
    for ( i = 0; i < db; i++) {
        if (jelentkezesek[i].id == index) {
            printf("Mik legyenek az uj munkanapok? \n");
            char temp[64];
            char before_copy[64];
            char temp2[64];
            char temp4[64];

            char temp3[64];

            strcpy(temp4, jelentkezesek[i].napok);
            strcpy(temp2, jelentkezesek[i].napok);
            strcpy(temp, jelentkezesek[i].napok);

            //strcpy(before_copy, jelentkezesek[i].napok);

            gets(temp);
            gets(temp);
            char test_days[64];
            strcpy(test_days,temp);
            if (nameCheckFunction(test_days)) {
                          modifyDaysFunction(temp2, 'd');
                strcpy(before_copy, temp);
                strcpy(temp3, before_copy);
                int successful = 1;
                char * token;
                char * rest = before_copy;

                while ((token = strtok_r(rest, " ", & rest))) {

                    if (strcmp(token, "hetfo") == 0) {

                        if (napok[0] >= 1) {
                            napok[0] -= 1;

                        } else {
                            printf("Sikertelen muvelet. \n");
                            successful = 0;
                        }

                    } else if (strcmp(trim(token), "kedd") == 0) {
                        if (napok[1] >= 1) {
                            napok[1] -= 1;
                        } else {
                            printf("Sikertelen muvelet. \n");
                            successful = 0;

                        }

                    } else if (strcmp(token, "szerda") == 0) {
                        if (napok[2] >= 1) {
                            napok[2] -= 1;
                        } else {
                            printf("Sikertelen muvelet. \n");
                            successful = 0;

                        }

                    } else if (strcmp(token, "csutortok") == 0) {
                        if (napok[3] >= 1) {
                            napok[3] -= 1;
                        } else {
                            printf("Sikertelen muvelet. \n");
                            successful = 0;

                        }

                    } else if (strcmp(token, "pentek") == 0) {
                        if (napok[4] >= 1) {
                            napok[4] -= 1;
                        } else {
                            printf("Sikertelen muvelet. \n");
                            successful = 0;

                        }

                    } else if (strcmp(token, "szombat") == 0) {
                        if (napok[5] >= 1) {
                            napok[5] -= 1;
                        } else {
                            printf("Sikertelen muvelet. \n");
                            successful = 0;

                        }

                    } else if (strcmp(token, "vasarnap") == 0) {
                        if (napok[6] >= 9) {
                            napok[6] -= 1;
                        } else {
                            printf("Sikertelen muvelet. \n");
                            successful = 0;

                        }

                    }
                }

                if (successful == 0) {
                    strcpy(jelentkezesek[i].napok, temp4);
                    modifyingTheFile();
                    return;

                }

                strcpy(jelentkezesek[i].napok, temp3);
                printf("Mi legyen az uj nev? \n");
                gets(jelentkezesek[i].nev);

                printf("Mi legyen az uj cim? \n");
                gets(jelentkezesek[i].cim);

                exist = 1;
                       modifyingTheFile();
        if (exist == 0)
            printf("A megadott azonositoval nem talalhato munkavallalo! \n");
            }
break;
        }
       
 
    }
     if(i==db){
            printf("A megadott azonositoval nem talalhato munkavallalo! \n");
        }

}
void clearFileFunction() {

    remove("out.txt");

}

void menu() {
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("Aktualis helyek szama: \n \n");
    char week[7][10] = {
        "hetfo",
        "kedd",
        "szerda",
        "csutortok",
        "pentek",
        "szombat",
        "vasarnap"
    };
    for (int i = 0; i < 7; i++) {
        printf("%s: ", week[i]);
        for (int j = 0; j < napok[i]; j++) {
            printf("#");
        }
        printf("(%d)", napok[i]);
        printf("\n");
    }
    printf("\nValassz opciot!\n\n");
    printf("1, Uj munkajelentkezes felvitele\n");
    printf("2, Munkajelentkezesek listaja\n");
    printf("3, Munkajelentkezesek modositasa\n");
    printf("4, Munkajelentkezesek torlese\n");
    printf("5, Munkajelentkezesek egy adott napra \n");
    printf("6, Kilepes\n\n");
    printf("Nyomj meg egy szamot a valasztashoz!\n");
    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    int valasz;

    if (scanf("%d", & valasz) != 1) {
        printf("Szamot adj meg!");
        menu();
    }

    int index = 0;
    switch (valasz) {
    case 1:
        addFunction();
        menu();
        break;
    case 2:
        printFunction();
        menu();
        break;
    case 3:
        printf("Add meg a megvaltoztatni kivant jelentkezes azonositojat!");
        scanf("%d", & index);

        modifyingFunction(index);
        menu();
        break;
    case 4:
        printf("Add meg a torolni kivant jelentkezes azonositojat!");

        scanf("%d", & index);
        deleteFunction(index);
        menu();
        break;
    case 6:
        printf("\nViszlat!\n");
        //file_kiir();
        exit(0);
        break;
    case 5:
        printf("Adott napi munkajelentkezesek listazasa \n");
        printf("Adjon meg egy napot! \n");
        char temp[10];
        scanf("%s", temp);

        printWorksByDay(temp);

        menu();
        break;
    default:
        printf("\nRossz valasz, ujra!\n");
        menu();
    }
}

int main() {
    printf("\nMunkanyilvantarto rendszer!\n\n");
    printf("\nKezdetben minden napra (hétfő-vasárnap) 10-10 emberre van szüksegünk.\n\n");
    readFunction();

    menu();
    return 0;
}