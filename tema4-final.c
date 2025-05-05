int main() {
    meniuPrincipal();
    return 0;
}

void meniuPrincipal() {
    int choice;
    do {
        system("cls");  
        printf(GREEN"=== Rezervare Hotel - Meniu Principal ===\n"RESET);
        printf(YELLOW"1. Afiseaza camerele disponibile\n"RESET);
        printf(YELLOW"2. Cauta camere dupa tip\n"RESET);
        printf(YELLOW"3. Rezerva camera / Detalii rezervari\n"RESET);
        printf(YELLOW"4. Anuleaza rezervare\n"RESET);
        printf(YELLOW"5. Iesire\n"RESET);
        printf("Selectati o optiune: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        
        switch(choice) {
            case 1:
                camereDisponibile();
                break;
            case 2:
                cautaCamere();
                break;
            case 3:
                rezervaCamere();
                break;
            case 4:
                anulareRezervare();
                break;
            case 5:
                printf("\nIesire...\n");
                break;
            default:
                printf(RED"\nOptiune invalida! Apasati ENTER pentru a incerca din nou..."RESET);
                getchar();
                break;
        }
    } while(choice != 5);
}

void citesteCamereDinFisier() {
    FILE *f = fopen("camere.txt", "r");
    if (f == NULL) {
        printf(RED"Nu s-a putut deschide fisierul 'camere.txt'\n"RESET);
        return;
    }
    
    struct Camera camere[MAX_CAMERE];
    int count = 0;
    while (fscanf(f, "%[^,],%f,%s\n", camere[count].tip, &camere[count].pret, camere[count].status) == 3 && count < MAX_CAMERE) {
        count++;
    }
    fclose(f);
    
    printf(GREEN"=== Lista Camerelor ===\n"RESET);
    for (int i = 0; i < count; i++) {
        printf("Tip: "YELLOW"%s"RESET" | Pret: "YELLOW"%.2f RON"RESET" | Status: "YELLOW"%s"RESET"\n",
               camere[i].tip, camere[i].pret, camere[i].status);
    }
    printf("\nApasati ENTER pentru a reveni la meniul principal...");
    getchar();
}

void salveazaRezervare(struct Rezervare r) {
    FILE *f = fopen("rezervari.txt", "a");
    if (f == NULL) {
        printf(RED"Eroare la deschiderea fisierului 'rezervari.txt'\n"RESET);
        return;
    }
    fprintf(f, "%s,%d,%s,%.2f\n", r.tipCamera, r.nrPersoane, r.perioada, r.pretTotal);
    fclose(f);
    printf(GREEN"Rezervare salvata cu succes!\n"RESET);
}

int valideazaNumarPersoane(int nr) {
    if (nr < 1) {
        printf(RED"Numarul de persoane trebuie sa fie cel putin 1!\n"RESET);
        return 0;
    }
    return 1;
}

void citesteData(char *data, int lungime) {
    int valid = 0;
    do {
        printf("Introdu data (format zz-ll-aaaa): ");
        fgets(data, lungime, stdin);
        data[strcspn(data, "\n")] = '\0';  // Elimină caracterul newline dacă e prezent
        if (strlen(data) == 10 && data[2] == '-' && data[5] == '-') {
            valid = 1;
        } else {
            printf(RED"Format invalid! "RESET);
        }
    } while(!valid);
}

void camereDisponibile() {
    system("cls");
    citesteCamereDinFisier();
}

void cautaCamere() {
    system("cls");
    printf(GREEN"=== Cautare Camera ===\n"RESET);
    printf("Tip de camere disponibile:\n");
    printf("1. Single\n");
    printf("2. Double\n");
    printf("3. Suite\n");
    printf("\nApasati ENTER pentru a reveni la meniul principal...");
    getchar();
}

void rezervaCamere() {
    int op;
    struct Rezervare rezervare;
    do {
        system("cls");
        printf(GREEN"=== Rezervare / Detalii Rezervari ===\n"RESET);
        printf(YELLOW"1. Rezerva o camera\n"RESET);
        printf(YELLOW"2. Verifica detaliile rezervarilor\n"RESET);
        printf(YELLOW"3. Revenire la meniul principal\n"RESET);
        printf("Selectati o optiune: ");
        scanf("%d", &op);
        while(getchar() != '\n');

        switch(op) {
            case 1:
                system("cls");
                printf(GREEN"Rezervare camera:\n"RESET);
                printf("Introduceti tipul camerei (Single/Double/Suite): ");
                scanf("%s", rezervare.tipCamera);
                while(getchar() != '\n');
                
                
                do {
                    printf("Introduceti numarul de persoane: ");
                    scanf("%d", &rezervare.nrPersoane);
                    while(getchar() != '\n');
                } while(!valideazaNumarPersoane(rezervare.nrPersoane));  
               
                citesteData(rezervare.perioada, sizeof(rezervare.perioada));
                
                if (strcmp(rezervare.tipCamera, "Single") == 0) {
                    rezervare.pretTotal = 100.00 * rezervare.nrPersoane;
                } else if (strcmp(rezervare.tipCamera, "Double") == 0) {
                    rezervare.pretTotal = 150.00 * rezervare.nrPersoane;
                } else if (strcmp(rezervare.tipCamera, "Suite") == 0) {
                    rezervare.pretTotal = 300.00 * rezervare.nrPersoane;
                } else {
                    rezervare.pretTotal = 0;
                }
                
                salveazaRezervare(rezervare);
                printf("\nApasati ENTER pentru a reveni...");
                getchar();
                break;
            case 2:
                verificaDetaliiRezervare();
                break;
            case 3:
                system("cls");
                break;
            default:
                printf(RED"\nOptiune invalida! Apasati ENTER pentru a incerca din nou..."RESET);
                getchar();
                break;
        }
    } while(op != 3);
}

void verificaDetaliiRezervare() {
    system("cls");
    FILE *f = fopen("rezervari.txt", "r");
    if (f == NULL) {
        printf(RED"Nu s-a putut deschide fisierul 'rezervari.txt'\n"RESET);
        printf("Apasati ENTER pentru a reveni...");
        getchar();
        return;
    }
    
    struct Rezervare rezervari[MAX_REZERVARI];
    int count = 0;
    while (fscanf(f, "%[^,],%d,%[^,],%f\n", 
                  rezervari[count].tipCamera, 
                  &rezervari[count].nrPersoane,
                  rezervari[count].perioada, 
                  &rezervari[count].pretTotal) == 4 && count < MAX_REZERVARI) {
        count++;
    }
    fclose(f);
    
    if (count == 0) {
        printf(YELLOW"Nu exista rezervari in fisier.\n"RESET);
    } else {
        printf(GREEN"=== Detalii Rezervari ===\n"RESET);
        for (int i = 0; i < count; i++) {
            printf(YELLOW"%d. "RESET, i + 1);
            printf("Tip camera: %s | Numar persoane: %d | Perioada: %s | Pret total: %.2f RON\n",
                   rezervari[i].tipCamera, rezervari[i].nrPersoane,
                   rezervari[i].perioada, rezervari[i].pretTotal);
        }
    }
    printf("\nApasati ENTER pentru a reveni la meniul anterior...");
    getchar();
}

void anulareRezervare() {
    system("cls");
    FILE *f = fopen("rezervari.txt", "r");
    if (f == NULL) {
        printf(RED"Nu s-a putut deschide fisierul 'rezervari.txt'\n"RESET);
        printf("Apasati ENTER pentru a reveni...");
        getchar();
        return;
    }
    
    struct Rezervare rezervari[MAX_REZERVARI];
    int count = 0;
    while (fscanf(f, "%[^,],%d,%[^,],%f\n", 
                  rezervari[count].tipCamera, 
                  &rezervari[count].nrPersoane,
                  rezervari[count].perioada, 
                  &rezervari[count].pretTotal) == 4 && count < MAX_REZERVARI) {
        count++;
    }
    fclose(f);
    
    if (count == 0) {
        printf(YELLOW"Nu exista rezervari de anulat.\n"RESET);
        printf("Apasati ENTER pentru a reveni...");
        getchar();
        return;
    }

    printf(GREEN"=== Lista Rezervarilor ===\n"RESET);
    for (int i = 0; i < count; i++) {
        printf(YELLOW"%d. "RESET, i + 1);
        printf("Tip camera: %s | Numar persoane: %d | Perioada: %s | Pret total: %.2f RON\n",
               rezervari[i].tipCamera, rezervari[i].nrPersoane,
               rezervari[i].perioada, rezervari[i].pretTotal);
    }
    
    int opt;
    printf("\nIntrodu numarul rezervarii pe care doriti sa o anulati (0 pentru a anula operatia): ");
    scanf("%d", &opt);
    while(getchar() != '\n');

    if (opt == 0) {
        return;
    }
    
    if (opt < 1 || opt > count) {
        printf(RED"Optiune invalida!\n"RESET);
        printf("Apasati ENTER pentru a reveni...");
        getchar();
        return;
    }
 
    for (int i = opt - 1; i < count - 1; i++) {
        rezervari[i] = rezervari[i + 1];
    }
    count--;  

    f = fopen("rezervari.txt", "w");
    if (f == NULL) {
        printf(RED"Eroare la deschiderea fisierului pentru rescriere!\n"RESET);
        printf("Apasati ENTER pentru a reveni...");
        getchar();
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s,%d,%s,%.2f\n", rezervari[i].tipCamera, rezervari[i].nrPersoane,
                rezervari[i].perioada, rezervari[i].pretTotal);
    }
    fclose(f);
    
    printf(GREEN"\nRezervarea selectata a fost anulata cu succes!\n"RESET);
    printf("Apasati ENTER pentru a reveni la meniul anterior...");
    getchar();
}
