#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


#define UP 72      // Cod ASCII pentru sageata sus
#define DOWN 80    // Cod ASCII pentru sageata jos
#define ENTER 13
#define true 1

//structura pentru produs
typedef struct {
    char name[200], country[200], description[200];
    int quantity;
    double price;
} product;

//structura pentru lista de produse
typedef struct {
    int product_count;
    product **products;
} Store;

void clearscreen() {
    system("cls || clear");
}
void green() {printf("\033[1;32m");}
void blue() {printf("\033[1;34m");}
void cyan() {printf("\033[1;36m");}
void red() {printf("\033[1;31m");}
void yellow() {printf("\033[1;33m");}
void purple() {printf("\033[1;35m");}
void orange() {printf("\033[1;38;5;214m");}
void brown() {printf("\033[1;38;5;130m");}
void lightpink() {printf("\033[1;38;5;200m");}
void gray() {printf("\033[1;38;5;245m");}
void lightred() {printf("\033[1;38;5;196m");}
void lightgreen() {printf("\033[1;38;5;82m");}
void lightorange() {printf("\033[1;38;5;208m");}
void coral() {printf("\033[1;38;5;211m");}
void reset() {printf("\033[0m");}



//functia pentru a salva produsele in produse.txt
void save_to_file(Store *store) {
    FILE *file = fopen("produse.txt", "w");
    if (!file) {
        printf("Nu s-a gasit fisierul\n");
        return;
    }
    for (int i = 0; i < store->product_count; i++) {
        fprintf(file, "%s\n", store->products[i]->name);
        fprintf(file, "%d\n", store->products[i]->quantity);
        fprintf(file, "%.2f\n", store->products[i]->price);
        fprintf(file, "%s\n", store->products[i]->country);
        fprintf(file, "%s\n", store->products[i]->description);
    }
    fclose(file);
}

//functia pentru a salva noua cantitate dupa cumparare
void save_quantity(Store *store) {
    if (store->product_count == 0) {
        printf("Nu exista produse de salvat!\n");
        return;
    }

    FILE *file = fopen("produse.txt", "w");
    if (!file) {
        printf("Nu s-a putut deschide fisierul pentru scriere!\n");
        return;
    }

    for (int i = 0; i < store->product_count; i++) {
        if (store->products[i] != NULL) {
            fprintf(file, "%s\n", store->products[i]->name);
            fprintf(file, "%d\n", store->products[i]->quantity);
            fprintf(file, "%.2f\n", store->products[i]->price);
            fprintf(file, "%s\n", store->products[i]->country);
            fprintf(file, "%s\n", store->products[i]->description);
        }
    }
    fclose(file);
}

//functia pentru a incarca produsele din fisier
void load_from_file(Store *store) {
    FILE *file = fopen("produse.txt", "r");
    if (!file) {
        // Daca fisierul nu exista se continua cu magazinul gol
        return;
    }

    while (!feof(file)) {
        //realoca memoria pentru a adauga un nou produs
        store->products = realloc(store->products, (store->product_count + 1) * sizeof(product *));

        //aloca memorie pentru noul produs
        store->products[store->product_count] = malloc(sizeof(product));


        //citeste datele din fisier
        if (fscanf(file, " %[^\n]", store->products[store->product_count]->name) == EOF) {
            free(store->products[store->product_count]); // Evitam o alocare inutila
            break;
        }
        fscanf(file, "%d", &store->products[store->product_count]->quantity);
        fscanf(file, "%lf", &store->products[store->product_count]->price);
        fscanf(file, " %[^\n]", store->products[store->product_count]->country);
        fscanf(file, " %[^\n]", store->products[store->product_count]->description);

        store->product_count++;
    }
    fclose(file);
}

//functia pentru a adauga un produs
void add(Store *store) {
    //aloca memorie dinamic pentru produse
    store->products[store->product_count] = (product *)malloc(sizeof(product));

    clearscreen();
    printf("--- Adaugare produs ---\n");
    printf("Numele produsului: ");
    scanf(" %[^\n]", store->products[store->product_count]->name);

    printf("Cantitate: ");
    //verifica daca cantitatea este int, sa nu se introduca alte tipuri
    while (scanf("%d", &store->products[store->product_count]->quantity)!=1) {
        printf("\nIntrodu o cantitate valida!\n");
        printf("Cantitate: ");
        while (getchar() != '\n'); //curata buffer
    }

    printf("Pret: ");
    while (scanf("%lf", &store->products[store->product_count]->price)!=1) {
        printf("\nIntrodu un pret valid\n");
        printf("Pret: ");
        while (getchar() != '\n');
    }

    printf("Tara de provenienta: ");
    scanf(" %[^\n]", store->products[store->product_count]->country);

    printf("Descriere: ");
    scanf(" %[^\n]", store->products[store->product_count]->description);

    store->product_count++;
}

// Functia pentru a sterge un produs
void delete_product(Store *store, int n) {
    clearscreen();
    if (store->product_count == 0) {
        printf("Nu exista produse.\n");
        return;
    }

    //muta fiecare produs cu un pas in stanga (incepand de la cel sters)
    free(store->products[n]);
    for (int i = n; i < store->product_count - 1; i++) {
        store->products[i] = store->products[i + 1];
    }
    store->product_count--;
    store->products = realloc(store->products, store->product_count * sizeof(product *));

    printf("--- Produsul #%d a fost sters. ---\n", n);
}

//functia pentru a vizualiza toate produsele
void display_all(Store *store) {
    clearscreen();
    if (store->product_count == 0) {
        printf("Nu exista produse!\n");
        return;
    }

    for (int i = 0; i < store->product_count; i++) {
        printf("\n--- Produs #%d ---\n", i);
        reset();
        printf("Nume: %s\n", store->products[i]->name);
        printf("Tara: %s\n", store->products[i]->country);
        printf("Cantitate: %d\n", store->products[i]->quantity);
        printf("Pret: %.2f\n", store->products[i]->price);
        printf("Descriere: %s\n", store->products[i]->description);
        red();
    }
    printf("\n--- Apasa enter pentru a te intoarce la meniu. ---");
    while (getchar() != '\n');
    getchar();
}

void buy_menu(Store *store) {
    clearscreen();
    for (int i = 0; i < store->product_count; i++) {
        printf("\n--- Produs #%d ---\n", i);

        printf("\033[0;31mNume:\033[0;37m %s | ", store->products[i]->name);
        printf("\033[0;31mTara:\033[0;37m %s | ", store->products[i]->country);
        printf("\033[0;31mCantitate:\033[0;37m %d | ", store->products[i]->quantity);
        printf("\033[0;31mPret:\033[0;37m %.2f | ", store->products[i]->price);
        printf("\033[0;31mDescriere:\033[0;37m %s | \n", store->products[i]->description);

        printf("-----------------\n\033[0m");

    }
}


//functia pentru a vizualiza un singur produs (folosita la cautare)
void display(Store *store, int i) {
    clearscreen();
    printf("\n--- Produs #%d ---\n", i);
    printf("Nume: %s\n", store->products[i]->name);
    printf("Tara: %s\n", store->products[i]->country);
    printf("Cantitate: %d\n", store->products[i]->quantity);
    printf("Pret: %.2f\n", store->products[i]->price);
    printf("Descriere: %s\n", store->products[i]->description);
}


//functia pentru a cauta un produs pe baza tarii de provenienta sau a numelui
void search_product(Store *store, char search_term[200]) {
    clearscreen();
    int found = 0;
    for (int i = 0; i < store->product_count; i++) {
        if (strcmp(store->products[i]->name, search_term) == 0 || strcmp(store->products[i]->country, search_term) == 0) {
            display(store, i);
            found++;
        }
    }
    if (found == 1) printf("------------\n1 produs gasit\n");
    else if (found > 1)printf("------------\n%d produse gasite.\n",found);
    else if (found == 0) printf("Nu au fost gasite produse\n");
    printf("--- Apasa enter pentru a te intoarce la meniu. ---");
    getchar();
    while (getchar() != '\n');
}

//functie pentru a edita nume/tara/descriere
void edit_chr(Store *store, int k, int index, char new_text[200]) {
    switch (k) {
        case 1:
            strcpy(store->products[index]->name, new_text);
            break;
        case 2:
            strcpy(store->products[index]->description, new_text);
            break;
        case 3:
            strcpy(store->products[index]->country, new_text);
            break;
    }
}


//functia pentru a cumpara un produs
void buy_product(Store *store, int buy_index, int buy_quantity) {
    clearscreen();
    //verifica daca cantitatea introdusa de utilizator este mai mica decat stocul total
    if (buy_quantity <= store->products[buy_index]->quantity) {
        double price = buy_quantity * store->products[buy_index]->price;
        printf("============\nTotal de plata: %.2f\n============\n", price);
        store->products[buy_index]->quantity -= buy_quantity;
        save_quantity(store);

        printf("--- Apasa enter pentru a te intoarce la meniu. ---");
        while (getchar() != '\n');
        getchar();

    } else {
        printf("Cantitate prea mare. In stoc: %d\n", store->products[buy_index]->quantity);
        printf("--- Apasa enter pentru a te intoarce la meniu. ---");
        while (getchar() != '\n');
        getchar();

    }
}

void edit_product(Store *store) {
    int index = 0;
    clearscreen();
    printf("--- Editare Produs ---\nIndex pentru editare (0 - %d): ", store->product_count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= store->product_count) {
        printf("Index invalid!\n");
        getch();
        return;
    }

    int selected = 0;
    int key;
    char edited_text[200];

    while (1) {
        clearscreen();
        red();
        printf("--- Meniu editare #%d [%s] ---\n", index, store->products[index]->name);

        if (selected == 0) green(); else red();
        printf("%s Editeaza Nume\n", selected == 0 ? " >" : "  ");

        if (selected == 1) green(); else red();
        printf("%s Editeaza Cantitate\n", selected == 1 ? " >" : "  ");

        if (selected == 2) green(); else red();
        printf("%s Editeaza Pret\n", selected == 2 ? " >" : "  ");

        if (selected == 3) green(); else red();
        printf("%s Editeaza Descriere\n", selected == 3 ? " >" : "  ");

        if (selected == 4) green(); else red();
        printf("%s Editeaza Tara de provenienta\n", selected == 4 ? " >" : "  ");

        if (selected == 5) green(); else red();
        printf("%s Sterge Produs\n", selected == 5 ? " >" : "  ");

        if (selected == 6) green(); else red();
        printf("%s Inapoi la meniu\n", selected == 6 ? " >" : "  ");

        red(); // revenim la roșu pentru ultima linie
        printf("-------------------------------\n");


        key = getch();

        if (key == 224) { // Detecteaza taste speciale (Windows)
            key = getch();
        }

        switch (key) {
            case UP:
                selected = (selected - 1 + 7) % 7; // Navigare sus
                break;
            case DOWN:
                selected = (selected + 1) % 7; // Navigare jos
                break;
            case ENTER:
                clearscreen();
                switch (selected) {
                    case 0:
                        printf("Nume nou: ");
                        while (getchar() != '\n'); // Evita problemele de input buffer
                        scanf("%[^\n]", edited_text);
                        edit_chr(store, 1, index, edited_text);
                        break;
                    case 1: {
                        int edited_quantity;
                        printf("Cantitate noua: ");
                        while (scanf("%d", &edited_quantity) != 1) {
                            printf("Introdu o cantitate valida!\nCantitate noua: ");
                            while (getchar() != '\n');
                        }
                        store->products[index]->quantity = edited_quantity;
                        break;
                    }
                    case 2: {
                        double edited_price;
                        printf("Pret nou: ");
                        while (scanf("%lf", &edited_price) != 1) {
                            printf("Introdu un pret valid!\nPret nou: ");
                            while (getchar() != '\n');
                        }
                        store->products[index]->price = edited_price;
                        break;
                    }
                    case 3:
                        printf("Descriere noua: ");
                        while (getchar() != '\n');
                        scanf("%[^\n]", edited_text);
                        edit_chr(store, 2, index, edited_text);
                        break;
                    case 4:
                        printf("Tara de provenienta noua: ");
                        while (getchar() != '\n');
                        scanf("%[^\n]", edited_text);
                        edit_chr(store, 3, index, edited_text);
                        break;
                    case 5:
                        delete_product(store, index);
                        return;
                    case 6:
                        return;
                }
                break;
        }
    }
}


void admin_menu(Store *store) {
    int selected = 0;
    int key;

    while (1) {
        clearscreen();
        red();
        printf("------ Administrare [%d produse in stoc] ------\n", store->product_count);

        if (selected == 0) green(); else red();
        printf("%s Adauga produs\n", selected == 0 ? " >" : "  ");

        if (selected == 1) green(); else red();
        printf("%s Vizualizeaza produse\n", selected == 1 ? " >" : "  ");

        if (selected == 2) green(); else red();
        printf("%s Editeaza produs\n", selected == 2 ? " >" : "  ");

        if (selected == 3) green(); else red();
        printf("%s Cautare\n", selected == 3 ? " >" : "  ");

        if (selected == 4) green(); else red();
        printf("%s Iesire\n", selected == 4 ? " >" : "  ");

        red(); // revenim la roșu pentru ultima linie
        printf("----------------------------------\n");


        key = getch();

        if (key == 224) { // Detecteaza taste speciale (Windows)
            key = getch();
        }

        switch (key) {
            case UP:
                selected = (selected - 1 + 5) % 5; // Navigare sus (circular)
                break;
            case DOWN:
                selected = (selected + 1) % 5; // Navigare jos (circular)
                break;
            case ENTER:
                clearscreen();
                switch (selected) {
                    case 0:
                        add(store);
                        break;
                    case 1:
                        display_all(store);
                        break;
                    case 2: {
                        edit_product(store);
                        break;
                    }
                    case 3: {
                        char search_term[200];
                        printf("--- Cautare Produs ---\nCautare: ");
                        while (getchar() != '\n');
                        scanf("%[^\n]", search_term);
                        search_product(store, search_term);
                        break;
                    }
                    case 4:
                        save_to_file(store);
                        return; // Iesire din meniu
                }
                break;
        }
    }
}

void customer_menu(Store *store) {
    clearscreen();
    while (true) {
        if (store->product_count == 0) {
            printf("Nu exista produse disponibile.\n");
            return;
        }

        buy_menu(store);
        int buy_index, buy_quantity;

        printf("[-1 pentru meniu principal]\n");
        printf("Cumpara (introdu index): ");
        scanf("%d", &buy_index);
        if (buy_index == -1) return;
        if (buy_index < store->product_count) {
            printf("Cantitatea dorita de %s (%d in stoc): ", store->products[buy_index]->name, store->products[buy_index]->quantity);
            scanf("%d", &buy_quantity);
            buy_product(store, buy_index, buy_quantity);
        } else {
            printf("Produs invalid!\n");
            return;
        }
    }
}

void cleanup_and_exit(Store *store) {
    save_to_file(store);
    for (int i = 0; i < store->product_count; i++) {
        free(store->products[i]);
    }
    free(store->products);
    exit(0);
}

void main_menu() {
    Store store = {0, NULL};
    load_from_file(&store);

    int selected = 0;
    int key;

    while (1) {
        clearscreen();
        red();
        printf("--- Magazin ---\n");

        if (selected == 0) green(); else red();
        printf("%s Administrare\n", selected == 0 ? " >" : "  ");

        if (selected == 1) green(); else red();
        printf("%s Cumpara produs\n", selected == 1 ? " >" : "  ");

        if (selected == 2) green(); else red();
        printf("%s Iesire\n", selected == 2 ? " >" : "  ");

        red(); // revenim pe roșu ca să fie liniuța de jos normală
        printf("----------------\n");


        key = getch();

        if (key == 224) {
            key = getch();
        }

        switch (key) {
            case UP:
                selected = (selected - 1 + 3) % 3;
            break;
            case DOWN:
                selected = (selected + 1) % 3;
            break;
            case ENTER:
                switch (selected) {
                    case 0:
                        clearscreen();
                    admin_menu(&store);
                    break;
                    case 1:
                        clearscreen();
                    customer_menu(&store);
                    break;
                    case 2:
                        clearscreen();
                    printf("Ai iesit din aplicatie\n");
                    cleanup_and_exit(&store);
                    return;
                }
            break;
        }
    }
}

int main() {
    while (true) {
        main_menu();
    }
}
