#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITOLO 100
#define MAX_AUTORE 100
#define MAX_EDITORE 50
#define MAX_ISBN 20
#define FILENAME "biblioteca.dat"

typedef struct {
    char titolo[MAX_TITOLO];
    char autore[MAX_AUTORE];
    char editore[MAX_EDITORE];
    int anno;
    char isbn[MAX_ISBN];
} Libro;

void pulisciBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserisciLibro() {
    FILE *fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Errore apertura file!\n");
        return;
    }
    
    Libro libro;
    
    printf("\nINSERIMENTO NUOVO LIBRO\n");
    
    printf("Titolo: ");
    pulisciBuffer();
    fgets(libro.titolo, MAX_TITOLO, stdin);
    libro.titolo[strcspn(libro.titolo, "\n")] = 0;
    
    printf("Autore: ");
    fgets(libro.autore, MAX_AUTORE, stdin);
    libro.autore[strcspn(libro.autore, "\n")] = 0;
    
    printf("Editore: ");
    fgets(libro.editore, MAX_EDITORE, stdin);
    libro.editore[strcspn(libro.editore, "\n")] = 0;
    
    printf("Anno di pubblicazione: ");
    scanf("%d", &libro.anno);
    
    printf("Codice ISBN: ");
    pulisciBuffer();
    fgets(libro.isbn, MAX_ISBN, stdin);
    libro.isbn[strcspn(libro.isbn, "\n")] = 0;
    
    fwrite(&libro, sizeof(Libro), 1, fp);
    fclose(fp);
    
    printf("\nLibro inserito con successo!\n");
}

void visualizzaLibro(Libro *libro) {
    printf("\nLIBRO: \n");
    printf("Titolo: %s\n", libro->titolo);
    printf("Autore: %s\n", libro->autore);
    printf("Editore: %s\n", libro->editore);
    printf("Anno: %d\n", libro->anno);
    printf("ISBN: %s\n", libro->isbn);
    printf("---------------------\n");
}

void ricercaLibro() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Nessun libro presente in archivio!\n");
        return;
    }
    
    char ricerca[MAX_TITOLO];
    
    printf("\nRICERCA LIBRO PER TITOLO\n");
    printf("Inserisci il titolo da cercare: ");
    pulisciBuffer();
    fgets(ricerca, MAX_TITOLO, stdin);
    ricerca[strcspn(ricerca, "\n")] = 0;
    
    Libro libro;
    int trovato = 0;
    
    while (fread(&libro, sizeof(Libro), 1, fp) == 1) {
        if (strstr(libro.titolo, ricerca) != NULL) {
            visualizzaLibro(&libro);
            trovato = 1;
        }
    }
    
    if (!trovato) {
        printf("Nessun libro trovato con questo titolo!\n");
    }
    
    fclose(fp);
}

void modificaLibro() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Nessun libro presente in archivio!\n");
        return;
    }
    
    char titolo[MAX_TITOLO];
    printf("\nMODIFICA LIBRO\n");
    printf("Inserisci Titolo del libro da modificare: ");
    pulisciBuffer();
    fgets(titolo, MAX_TITOLO, stdin);
    titolo[strcspn(titolo, "\n")] = 0;
    
    Libro *libri = NULL;
    int count = 0;
    int pos = -1;
    Libro libro;
    
    while (fread(&libro, sizeof(Libro), 1, fp) == 1) {
        libri = realloc(libri, (count + 1) * sizeof(Libro));
        libri[count] = libro;
        if (strcmp(libro.titolo, titolo) == 0) {
            pos = count;
        }
        count++;
    }
    fclose(fp);
    
    if (pos == -1) {
        printf("Libro non trovato!\n");
        free(libri);
        return;
    }
    
    printf("\nLibro trovato:\n");
    visualizzaLibro(&libri[pos]);
    
    printf("\nInserisci i nuovi dati:\n");
    
    printf("Nuovo titolo: ");
    fgets(libri[pos].titolo, MAX_TITOLO, stdin);
    libri[pos].titolo[strcspn(libri[pos].titolo, "\n")] = 0;
    
    printf("Nuovo autore: ");
    fgets(libri[pos].autore, MAX_AUTORE, stdin);
    libri[pos].autore[strcspn(libri[pos].autore, "\n")] = 0;
    
    printf("Nuovo editore: ");
    fgets(libri[pos].editore, MAX_EDITORE, stdin);
    libri[pos].editore[strcspn(libri[pos].editore, "\n")] = 0;
    
    printf("Nuovo anno: ");
    scanf("%d", &libri[pos].anno);
    
    printf("Nuovo ISBN: ");
    pulisciBuffer();
    fgets(libri[pos].isbn, MAX_ISBN, stdin);
    libri[pos].isbn[strcspn(libri[pos].isbn, "\n")] = 0;
    
    fp = fopen(FILENAME, "wb");
    fwrite(libri, sizeof(Libro), count, fp);
    fclose(fp);
    free(libri);
    
    printf("\nLibro modificato con successo!\n");
}

void visualizzaTutti() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Nessun libro presente in archivio!\n");
        return;
    }
    
    Libro libro;
    int count = 0;
    
    printf("\nLIBRI INSERITI: \n");
    while (fread(&libro, sizeof(Libro), 1, fp) == 1) {
        visualizzaLibro(&libro);
        count++;
    }
    
    printf("\nTotale libri: %d\n", count);
    fclose(fp);
}

int main() {
    int scelta;
    
    do {
        printf("BIBLIOTECA DI MIMI\n");
        printf("1. Inserisci nuovo libro\n");
        printf("2. Ricerca libro per titolo\n");
        printf("3. Modifica libro\n");
        printf("4. Visualizza tutti i libri\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        
        switch(scelta) {
            case 1:
                inserisciLibro();
                break;
            case 2:
                ricercaLibro();
                break;
            case 3:
                modificaLibro();
                break;
            case 4:
                visualizzaTutti();
                break;
            case 0:
                printf("Arrivederci!\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (scelta != 0);
    
    return 0;
}