#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 200

typedef enum {
    NORMAL,
    FIGHTING,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    STEEL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCHIC,
    ICE,
    DRAGON,
    DARK,
    FAIRY
} pokemonType;

typedef struct {
    char name[51];
    int pokeID;
    char type[20];
    char weakness[20];
    char species[101];
    float height;
    float weight;
    char abilites[101];
} Pokemon;

const char* typeName(pokemonType type) {
    switch (type) {
        case NORMAL: return "Normal";
        case FIGHTING: return "Fighting";
        case FLYING: return "Flying";
        case POISON: return "Poison";
        case GROUND: return "Ground";
        case ROCK: return "Rock";
        case BUG: return "Bug";
        case GHOST: return "Ghost";
        case STEEL: return "Steel";
        case FIRE: return "Fire";
        case WATER: return "Water";
        case GRASS: return "Grass";
        case ELECTRIC: return "Electric";
        case PSYCHIC: return "Psychic";
        case ICE: return "Ice";
        case DRAGON: return "Dragon";
        case DARK: return "Dark";
        case FAIRY: return "Fairy";
    }
    return "Unknown";
}

Pokemon poke[MAX];
int size;

int equalID(int id){
    Pokemon p[MAX];
    FILE *fp = fopen("pokemon.txt", "r");
    int c = 0;
    while(fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n", p[c].name, &p[c].pokeID, p[c].type, p[c].weakness, p[c].species, &p[c].height, &p[c].weight, p[c].abilites) != EOF) {
        c++;
    }
    fclose(fp);
    for(int i = 0; i < c; i++){
        if(p[i].pokeID == id) return 0;
    }
    return 1;
}
void clearScreen() {
    printf("\e[1;1H\e[2J");
}

void removeID(int id) {
    FILE *fp = fopen("pokemon.txt", "r");
    FILE *fp2 = fopen("temp.txt", "a");
    Pokemon p[MAX];
    if (fp == NULL){
        printf("File not found"); getchar();
        return;
    } 
    else if(fp2 == NULL) {
        printf("File not found"); getchar();
        return;
    }
    int c = 0;
    while(fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n", p[c].name, &p[c].pokeID, p[c].type, p[c].weakness, p[c].species, &p[c].height, &p[c].weight, p[c].abilites) != EOF) {
        c++;
    }
    fclose(fp);
    for(int i = 0; i < c; i++){
    if(p[i].pokeID != id) {
        fprintf(fp2, "%s#%d#%s#%s#%s#%0.1f#%0.1f#%s\n", p[i].name, p[i].pokeID, p[i].type, p[i].weakness, p[i].species, p[i].height, p[i].weight, p[i].abilites);
    }
}
    fclose(fp2);
    remove("pokemon.txt");
    rename("temp.txt", "pokemon.txt");
    printf("Pokemon removed"); getchar();
}
void printPokemon(Pokemon *pokemons, int count) {
    printf("+-------+----------------------+----------+-----------------+-----------------------+--------+--------+----------------------------+\n");
    printf("| ID    |Name                  | Type     | Weakness        | Species               | Height | Weight | Abilities                  |\n");
    printf("+-------+----------------------+----------+-----------------+-----------------------+--------+--------+----------------------------+\n");
    for (int i = 0; i < count; i++) {
        printf("| #%04d | %-20s | %-8s | %-15s | %-21s | %-6.1f | %-6.1f | %-26s |\n",
               pokemons[i].pokeID,
               pokemons[i].name,
               pokemons[i].type,
               pokemons[i].weakness,
               pokemons[i].species,
               pokemons[i].height,
               pokemons[i].weight,
               pokemons[i].abilites);
    }
    printf("+-------+----------------------+----------+-----------------+-----------------------+--------+--------+----------------------------+\n");
}


int validateType(const char* type){
    if (strcasecmp(type, "Normal") == 0) return 1;
    if (strcasecmp(type, "Fighting") == 0) return 1;
    if (strcasecmp(type, "Flying") == 0) return 1;
    if (strcasecmp(type, "Poison") == 0) return 1;
    if (strcasecmp(type, "Ground") == 0) return 1;
    if (strcasecmp(type, "Rock") == 0) return 1;
    if (strcasecmp(type, "Bug") == 0) return 1;
    if (strcasecmp(type, "Ghost") == 0) return 1;
    if (strcasecmp(type, "Steel") == 0) return 1;
    if (strcasecmp(type, "Fire") == 0) return 1;
    if (strcasecmp(type, "Water") == 0) return 1;
    if (strcasecmp(type, "Grass") == 0) return 1;
    if (strcasecmp(type, "Electric") == 0) return 1;
    if (strcasecmp(type, "Psychic") == 0) return 1;
    if (strcasecmp(type, "Ice") == 0) return 1;
    if (strcasecmp(type, "Dragon") == 0) return 1;
    if (strcasecmp(type, "Dark") == 0) return 1;
    if (strcasecmp(type, "Fairy") == 0) return 1;
    return 0;
}

int validateSpecies(const char* species){
    int idx = 0;
    char temp[51];
    for(int i = 0; i<=strlen(species); i++){
        if(species[i] == ' '||species[i] == '\0'){
            idx = 0;
        }
        else {
            temp[idx] = species[i];
            idx++;
        }
    }
    if (strcasecmp(temp, "Pokemon") == 0) return 1;
    return 0;
}
void writePokemon(){
    FILE *fp = fopen("pokemon.txt", "a");
    if(fp == NULL){
        printf("File not foung"); getchar();
        return;
    }
    char pokemonName[51];
    int pokemonID;
    char pokemonType[20];
    char pokemonWeakness[20];
    char pokemonSpecies[101];
    float pokemonHeight;
    float pokemonWeight;
    char pokemonAbility[101];
    int t = 0;
    int verified = 0;
 do {
        printf("Insert Pokemon's name (Pokemon name must be at least 3 characters, type \"exit\" to exit): ");
        scanf("%[^\n]", pokemonName); getchar();
        int hasNumber = 0;
        if(strcasecmp(pokemonName, "exit") == 0) return;
        for (int i = 0; i < strlen(pokemonName); i++) {
            if (pokemonName[i] >= '0' && pokemonName[i] <= '9') {
                hasNumber = 1;
                break;
            }
        }

        if (strlen(pokemonName) < 3 && hasNumber) {
            clearScreen();
            printf("Pokemon's name must not contain number and at least 3 characters\n");
            t=1;
        } else if (strlen(pokemonName) < 3) {
            clearScreen();
            printf("Pokemon's name must be at least 3 characters\n");
            t=1;
        } else if (hasNumber) {
            clearScreen();
            printf("Pokemon's name must not contain numbers\n");
            t=1;
        }
        else t=0;

    } while (t == 1);
    
    do{
        printf("Insert Pokemon's ID(ID must at least 1-9999): ");
        scanf("%d", &pokemonID); getchar();
        if((pokemonID < 1 || pokemonID > 9999) || pokemonID < 0){
            clearScreen();
            printf("Pokemon's ID must be around 1-9999\n");
            t=1;
        }
        else{
            if(!equalID(pokemonID)){
                clearScreen();
                printf("Pokemon's ID already exist\n"); 
                t=1;
            }
            else t =0;
        } 
    }while (t==1);
    
    do{
   printf("Insert Pokemon's type: ");
    scanf("%[^\n]", pokemonType); getchar();
    if(!validateType(pokemonType)){
        clearScreen();
        printf("Invalid pokemon's type\n");
        t = 1;
    }
    else{
    if (strcasecmp(pokemonType, "Normal") == 0) strcpy(pokemonType, "Normal");
    if (strcasecmp(pokemonType, "Fighting") == 0) strcpy(pokemonType, "Fighting");
    if (strcasecmp(pokemonType, "Flying") == 0) strcpy(pokemonType, "Flying");
    if (strcasecmp(pokemonType, "Poison") == 0) strcpy(pokemonType, "Poison");
    if (strcasecmp(pokemonType, "Ground") == 0) strcpy(pokemonType, "Ground");
    if (strcasecmp(pokemonType, "Rock") == 0) strcpy(pokemonType, "Rock");
    if (strcasecmp(pokemonType, "Bug") == 0) strcpy(pokemonType, "Bug");
    if (strcasecmp(pokemonType, "Ghost") == 0) strcpy(pokemonType, "Ghost");
    if (strcasecmp(pokemonType, "Steel") == 0) strcpy(pokemonType, "Steel");
    if (strcasecmp(pokemonType, "Fire") == 0) strcpy(pokemonType, "Fire");
    if (strcasecmp(pokemonType, "Water") == 0) strcpy(pokemonType, "Water");
    if (strcasecmp(pokemonType, "Grass") == 0) strcpy(pokemonType, "Grass");
    if (strcasecmp(pokemonType, "Electric") == 0) strcpy(pokemonType, "Electric");
    if (strcasecmp(pokemonType, "Psychic") == 0) strcpy(pokemonType, "Psychic");
    if (strcasecmp(pokemonType, "Ice") == 0) strcpy(pokemonType, "Ice");
    if (strcasecmp(pokemonType, "Dragon") == 0) strcpy(pokemonType, "Dragon");
    if (strcasecmp(pokemonType, "Dark") == 0) strcpy(pokemonType, "Dark");
    if (strcasecmp(pokemonType, "Fairy") == 0) strcpy(pokemonType, "Fairy");
    t=0;
    }
    }while(t==1);

    do{
    printf("Insert Pokemon's weakness: ");
    scanf("%[^\n]", pokemonWeakness); getchar();
    if(!validateType(pokemonWeakness)){
        clearScreen();
        printf("Invalid pokemon's weakness type\n");
        t = 1;
    }
    else{
    if (strcasecmp(pokemonWeakness, "Normal") == 0) strcpy(pokemonWeakness, "Normal");
    if (strcasecmp(pokemonWeakness, "Fighting") == 0) strcpy(pokemonWeakness, "Fighting");
    if (strcasecmp(pokemonWeakness, "Flying") == 0) strcpy(pokemonWeakness, "Flying");
    if (strcasecmp(pokemonWeakness, "Poison") == 0) strcpy(pokemonWeakness, "Poison");
    if (strcasecmp(pokemonWeakness, "Ground") == 0) strcpy(pokemonWeakness, "Ground");
    if (strcasecmp(pokemonWeakness, "Rock") == 0) strcpy(pokemonWeakness, "Rock");
    if (strcasecmp(pokemonWeakness, "Bug") == 0) strcpy(pokemonWeakness, "Bug");
    if (strcasecmp(pokemonWeakness, "Ghost") == 0) strcpy(pokemonWeakness, "Ghost");
    if (strcasecmp(pokemonWeakness, "Steel") == 0) strcpy(pokemonWeakness, "Steel");
    if (strcasecmp(pokemonWeakness, "Fire") == 0) strcpy(pokemonWeakness, "Fire");
    if (strcasecmp(pokemonWeakness, "Water") == 0) strcpy(pokemonWeakness, "Water");
    if (strcasecmp(pokemonWeakness, "Grass") == 0) strcpy(pokemonWeakness, "Grass");
    if (strcasecmp(pokemonWeakness, "Electric") == 0) strcpy(pokemonWeakness, "Electric");
    if (strcasecmp(pokemonWeakness, "Psychic") == 0) strcpy(pokemonWeakness, "Psychic");
    if (strcasecmp(pokemonWeakness, "Ice") == 0) strcpy(pokemonWeakness, "Ice");
    if (strcasecmp(pokemonWeakness, "Dragon") == 0) strcpy(pokemonWeakness, "Dragon");
    if (strcasecmp(pokemonWeakness, "Dark") == 0) strcpy(pokemonWeakness, "Dark");
    if (strcasecmp(pokemonWeakness, "Fairy") == 0) strcpy(pokemonWeakness, "Fairy");
    t=0;
    }
    }while(t==1);

    do{
    printf("Insert Pokemon's species: ");
    scanf("%[^\n]", pokemonSpecies); getchar();
    int len = strlen(pokemonSpecies);
    for(int i = 0; i < len; i++){
        if(pokemonSpecies[i] >= '0' && pokemonSpecies[i] <= '9'){
            clearScreen();
            printf("Pokemon's species can't contain numbers\n");
            t = 1;
        }
        else t =0;
     }
     if(!t)strcat(pokemonSpecies, " Pokemon");
    }while(t==1);   

    do{
    printf("Insert Pokemon's height: ");
    scanf("%f", &pokemonHeight); getchar();
    if(pokemonHeight <= 0){
        clearScreen();
        printf("Pokemon's height must above 0\n");
        t = 1;
    }
    else t = 0;
    }while(t==1);
    
    do{
        printf("Insert Pokemon's weight: ");
        scanf("%f", &pokemonWeight); getchar();
        if(pokemonWeight <= 0){
            clearScreen();
            printf("Pokemon's weight must above 0\n");
            t = 1;
        }
        else t = 0;
    }while(t==1);

    do{
    printf("Insert Pokemon's abilities: ");
    scanf("%[^\n]", pokemonAbility); getchar();
    int len = strlen(pokemonAbility);
    for(int i = 0; i < len; i++){
        if(pokemonAbility[i] >= '0' && pokemonAbility[i] <= '9'){
            clearScreen();
            printf("Pokemon's species can't contain numbers\n");
            t = 1;
        }
        else t =0;
    }

    }while(t==1);
    clearScreen();
    verified = 1;
    if(verified){
        fprintf(fp, "%s#%d#%s#%s#%s#%0.1f#%0.1f#%s\n", pokemonName, pokemonID, pokemonType, pokemonWeakness, pokemonSpecies, pokemonHeight, pokemonWeight, pokemonAbility);
        printf("Pokemon added!\n"); getchar();
    }
    else printf("Error while adding pokemon\n");verified = 0; 
    fclose(fp);
}

void pokemonList() {
    FILE *fp = fopen("pokemon.txt", "r");
    if (fp == NULL) {
        printf("File not found");
        return;
    }
    int c = 0;
    while (fscanf(fp, "%[^#]#%d#%[^#]#%[^#]#%[^#]#%f#%f#%[^\n]\n", poke[c].name, &poke[c].pokeID, poke[c].type, poke[c].weakness, poke[c].species, &poke[c].height, &poke[c].weight, poke[c].abilites) != EOF) {
        c++;
    }
    fclose(fp);
    size = c;
}

int main() {
    int choice;
    do {
        clearScreen();
        printf("Welcome to pokeLite123\n");
        printf("1. Show pokemon list\n");
        printf("2. Edit pokemon list\n");
        printf("3. Quit\n");
        printf(">> ");
        int t;
        do{
            scanf("%d", &choice); getchar();
            if (choice >= '0' || choice <= '9') {
                continue;
            }
            else t = 1;
        }while(t == 1);
        switch (choice) {
            case 1:
            pokemonList();
            int select;
            do {
                clearScreen();
                puts("1. Show all");
                puts("2. Show type specific");
                puts("3. Exit");
                printf(">>");
                 do{
                     scanf("%d", &select); getchar();
                      if (select >= '0' || select <= '9') {
                     continue;
                      }
                    else t = 1;
                }while(t == 1);
                switch(select){
                    case 1: 
                        clearScreen();
                        printPokemon(poke, size);
                        getchar();
                     break;
                    case 2: {
                        char element[20];
                        Pokemon filteredPokemons[MAX];
                        int found = 0; 
                        int size2 = 0; 

                        printf("Insert what element type of Pokémon(type \"exit\" for exit): ");
                        scanf("%s", element);
                        getchar();
                        if(strcasecmp(element, "exit") == 0) break;
                        clearScreen();

                        for (int i = 0; i < size; i++) {
                            if (strcasecmp(element, poke[i].type) == 0) {
                                filteredPokemons[size2++] = poke[i];
                                found = 1;
                            }
                        }

                        if (found) {
                            printPokemon(filteredPokemons, size2); 
                        } else {
                            printf("No Pokémon found with type %s.\n", element);
                        }

                        getchar();
                        break;
                    }
                    break;
                    case 3:
                    break;
                    default:
                    printf("Invalid"); getchar();
                    break;
                     }
            }while (select !=3);
            break;
            case 2:
                int select2;
                do{
                    clearScreen();
                    puts("1. Add Pokemon");
                    puts("2. Remove Pokemon");
                    puts("3. Exit");
                    printf(">>");
                    do{
                     scanf("%d", &select2); getchar();
                      if (select2 >= '0' || select2 <= '9') {
                     continue;
                      }
                    else t = 1;
                }while(t == 1);
                    switch(select2){
                        case 1:
                        clearScreen();
                        writePokemon();
                        break;
                        case 2:
                        char select3[5];
                        int t = 0;
                        do{
                            clearScreen();
                            puts("Insert an ID(type \"exit\" for exit): ");
                            printf(">>");
                            scanf("%s", select3); getchar();
                            if (strcasecmp(select3, "exit") == 0) break;
                            int id = atoi(select3);
                            if(id<1 || id>9999) {
                                printf("Invalid ID"); getchar();
                                t = 1;
                            }
                            else{
                                if(equalID(id) == 0) removeID(id);
                                else{
                                    printf("ID not found"); getchar();
                                    t = 1;
                                } 
                            }
                        }while(t == 1);
                        break;
                        case 3:
                        break;
                        default:
                        printf("Invalid"); getchar();
                        break;
                 }
                }while(select2 != 3);
            break;
            case 3:
            break;
            default:
            printf("Invalid"); getchar();
            break;
            }
    }while (choice != 3);

    return 0;
}
