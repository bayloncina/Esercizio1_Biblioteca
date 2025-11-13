# 📚 Progetto Biblioteca in C

Il **Progetto Biblioteca** è un’applicazione sviluppata in linguaggio **C** per la gestione dei libri in una piccola biblioteca.  
È stato realizzato come progetto universitario presso **l’Università Mercatorum** e permette di gestire in modo semplice un archivio di volumi tramite salvataggio su file binario.

---

## 🧠 Descrizione generale

L’app consente di:
- 🗂️ Inserire nuovi libri nella biblioteca  
- 🔍 Cercare un libro per titolo  
- ✏️ Modificare le informazioni di un libro già presente  
- 📖 Visualizzare tutti i libri archiviati  

Tutti i dati vengono memorizzati nel file **`biblioteca.dat`**, così da essere conservati anche dopo la chiusura del programma.

---

## ⚙️ Struttura del codice

Il programma è composto da un unico file sorgente **`main.c`** che contiene:
- la definizione della struttura `Libro`  
- le funzioni operative per la gestione dei dati  
- il menu principale di interazione con l’utente  

### 🧩 Struttura `Libro`
Ogni libro è rappresentato da una struttura con i seguenti campi:

typedef struct {
    char titolo[100];
    char autore[100];
    char editore[50];
    int anno;
    char isbn[20];
} Libro;

---

📜 Licenza
Questo progetto è distribuito per scopi didattici e formativi.
