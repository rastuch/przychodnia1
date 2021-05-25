//
// Created by programista on 09.03.2021.
//
#include "patients.h"
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>


/*!
 * Funkcja pomocnicza do konkatynacji tablic charow
 *
 * @param num_args liczba stringów do konkatynacji
 *
 * @return void
*/
char *strconcat(int num_args, ...) {
    int strsize = 0;
    va_list ap;
    va_start(ap, num_args);
    for (int i = 0; i < num_args; i++)
        strsize += strlen(va_arg(ap, char*));

    char *res = malloc(strsize+1);
    strsize = 0;
    va_start(ap, num_args);
    for (int i = 0; i < num_args; i++) {
        char *s = va_arg(ap, char*);
        strcpy(res+strsize, s);
        strsize += strlen(s);
    }
    va_end(ap);
    res[strsize] = '\0';

    return res;
}

/**
 * Struktura reprezentujaca tabele Pcjenta w bazie danych
  */
struct Patient {
    /*@{*/
    char name[200]; /**< Imie */
    char secondName[200]; /**< Nazwisko */
    char pesel[50]; /**< Numer pesel jako tablia znakow */
    char birthDate[200]; /**< data urodzenia w formacje DD-MM-YYYY */
    char address[200]; /**< Adres */
    char email[200]; /**< Email */
    char phone[50]; /**< Numer telefonu */
    char weight[200]; /**< Waga w kg */
    char height[200]; /**< Wzrost w cm */
    char nfz[200]; /**< NFZ */
    /*@{*/
};

/*!
 * Funkcja pozwaljaca ustalic rodzaj wedlug jakiej kolumny ma zostac posortowane wyniki
 *
 *
 * @return char* wskaznik z tablica charow okreslajaca nazwe tabeli w bazie danych
*/
const char* columnNamePatientChoice() {
    int choiceNumber;
    printf("\n1.ID 2.Imie 3.Nazwisko 4.Pesel, 5.Data urodzenia 6.Adress\n7.Email 8.Telefon 9.Waga 10.Wzrost 11.NFZ");
    printf("\nPodaj numer columny wedlug ktorej chcesz posortowac wyniki:\n");
    scanf("%i",&choiceNumber);
  switch(choiceNumber) {
       case 1: {
           char *table = "id";
           return table;
       }
      case 2: {
          char *table = "name";
          return table;
      }
      case 3: {
          char *table = "secondName";
          return table;
      }
      case 4: {
          char *table = "pesel";
          return table;
      }
      case 5: {
          char *table = "birthDate";
          return table;
      }
      case 6: {
          char *table = "address";
          return table;
      }
      case 7: {
          char *table = "email";
          return table;
      }
      case 8: {
          char *table = "phone";
          return table;
      }
      case 9: {
          char *table = "weight";
          return table;
      }
      case 10: {
          char *table = "height";
          return table;
      }
      case 11: {
          char *table = "nfz";
          return table;
      }
      default: {
          char *table = "id";
          return table;
      }
   }
}
/*!
 * Funkcja pozwaljaca ustalic rodzaj sortowania (malejacy/rosnacy)
 *
 *
 * @return char* wskaznik z tablica charow okreslajaca rodzaj sortowania
*/
const char* sortPatientOrder() {
    int choiceNumber;
    printf("\nPodaj numer sortowania :\n");
    printf("\n1.Malejaco 2.Rosnaco\n");
    scanf("%i",&choiceNumber);
    switch (choiceNumber) {
        case 1: {
            char *order = "desc;";
                    return order;
        }
        case 2: {
            char *order = "asc;";
            return order;
        }
        default: {
            char *order = "asc;";
            return order;
        }
    }
}





/*!
 * Zmienna z aktualnym pacjentem
 */
struct Patient patient;

/*!
 * Zmienna pomocnicza z pacjentem o pustych wartosciach
 */
struct Patient emptyPatient;

/*!
 * Domyslna funkcja wywolania zwrotnego uzywana uzyskania informacji o poprawnym odczytaniu danych z bazy
 *
 * @return int
*/
static int callback(void *data, int argc, char **argv, char **azColName) {
    printf("All good\n");
    return 0;
}

/*!
 * Funkcja usuwaj¹ca pacjenta z bazy przyjmuj¹ca za argument id
 * @param id identyfikator u¿ytkownika do usuniêcia
 * @retrun void
*/
void deletePatientById(char id[50]) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("przychodnia.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        //  fprintf(stderr, "Opened database successfully\n");
    }

    /* Create merged SQL statement */
    char sql[200] = "DELETE from patients where ID=";
    strcat(sql, id);
    strcat(sql, ";");

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        // fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}


/*!
 * Funkcja dodajaca pacjenta do bazy przyjmujaca za argument strukture "patient"
 * @param newPatient zmienna zwierajaca strukture "patient" do zapisania
 * @return void
*/
void addPatient(struct Patient newPatient) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    /* Open database */
    rc = sqlite3_open("przychodnia.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        // fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    char sql[50500] = "INSERT INTO patients (name,secondName,pesel,birthDate,address,email,phone,weight,height,nfz) "  \
         "VALUES ";
    char setData[5000];
    struct Patient up = newPatient;
    snprintf(setData, sizeof(setData),
             "('%s', '%s', '%s', '%s', '%s', '%s', " \
             "'%s', '%s', '%s', '%s');",
             up.name, up.secondName, up.pesel, up.birthDate, up.address, up.email, up.phone, up.weight, up.height,
             up.nfz);
    strcat(sql, setData);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //  fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}


/*
 *  */
/*!
 * Funkcja aktualizujaca pacjenta w bazie, przyjmuje za argumeny id uzytkownika oraz strukture Patient
 * jako obiekt do ktorego ma zostac zaktualizowany
 *
 * @param id identyfikator pacjenta do zaktualizowania
 * @param newPatient zmienna zwierajaca strukture "patient" do zaktualizowania
 * @return void
*/
void updatePatientById(char id[50], struct Patient newPatient) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("przychodnia.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        //  fprintf(stderr, "Opened database successfully\n");
    }
    /* Create merged SQL statement */
    char sql[5050] = "UPDATE patients set ";
    struct Patient up = newPatient;
    char setData[5000];

    snprintf(setData, sizeof(setData),
             "name = '%s' , secondName = '%s' , pesel = '%s' , birthDate = '%s', address = '%s', email = '%s', " \
             "phone = '%s',  weight = '%s', height = '%s', nfz = '%s' where id=%s;",
             up.name, up.secondName, up.pesel, up.birthDate, up.address, up.email, up.phone, up.weight, up.height,
             up.nfz, id);
    strcat(sql, setData);




    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //    fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}

/*!
 *Funkcja wywo³ania zwrotnego przypisujaca informacje z bazy danych do stuktury pacjent
 *
 *
 * @return int
*/
static int cbGetPatient(void *data, int argc, char **argv, char **colName) {

    /* Funkcja korzysta ze zmiennej globalnej "patient" wiêc wymaga upewnienia siê ¿e jest pusta
     * poprzez przypisanie obiektu "emptyPatient" */
    patient = emptyPatient;
    strcpy(patient.name, argv[1] ? argv[1] : "NULL");
    strcpy(patient.secondName, argv[2] ? argv[2] : "NULL");
    strcpy(patient.pesel, argv[3] ? argv[3] : "NULL");
    strcpy(patient.birthDate, argv[4] ? argv[4] : "NULL");
    strcpy(patient.address, argv[5] ? argv[5] : "NULL");
    strcpy(patient.email, argv[6] ? argv[6] : "NULL");
    strcpy(patient.phone, argv[7] ? argv[7] : "NULL");
    strcpy(patient.weight, argv[8] ? argv[8] : "NULL");
    strcpy(patient.height, argv[9] ? argv[9] : "NULL");
    strcpy(patient.nfz, argv[10] ? argv[10] : "NULL");
    return 0;
}


/*!
 *Funkcja zwracaj¹ca strukture patient z bazy danych na podstawie podanego parametru id
 *
 * @param id identyfikator pacjenta do wyswietlenia
 * @return void
*/
struct Patient getPatientById(char id[50]) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("przychodnia.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        // fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    char sql[] = "SELECT * from patients where id=";
    strcat(sql, id);
    strcat(sql, ";");

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, cbGetPatient, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        // fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
    return patient;
}


/*!
 *Funkcja wywolania zwrotnego wswietlajaca liste pacjentow
 *
 * @return int
*/
static int cbShowAllPatients(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

    }
    printf("\n");
    return 0;
}


/*!
 *Funkcja wyszukiwaj¹ca pacjenta wedlug imienia i nazwiska
 *
 * @param nameOrSecondName imie lub nazwisko pacjenta do wyszukania
 * @return void
*/
void searchPatients(char nameOrSecondName[100] ) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("przychodnia.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        //  fprintf(stderr, "Opened database successfully\n");
    }

   /* Create SQL statement */
    sql = strconcat(6, "SELECT * from patients where name like '%%", nameOrSecondName,"%%' ",
                    "OR secondName like '%%",nameOrSecondName,"%%'");
    rc = sqlite3_exec(db, sql, cbShowAllPatients, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //   fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}



/*!
 *Funkcja wyœwietla listê wszystkich pacjentów
 *
 * @param sortByColumnName nazwa columny wedlug ktorej maja zostac posortowane wyniki
 * @param sortOrder rodzaj sortowania
 * @return void
*/
void showAllpatients(char sortByColumnName[], char sortOrder[]) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("przychodnia.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        //  fprintf(stderr, "Opened database successfully\n");
    }
    char setData[5000];
    /* Create SQL statement */
    sql = "SELECT * from patients order by ";

    snprintf(setData, sizeof(setData),
            "%s%s %s",
            sql,sortByColumnName,sortOrder);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, setData, cbShowAllPatients, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //   fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}



//

/*!
 *Insert data i callback to funkcje pomocnicze do uzupe³niania tabeli
 *
 * @return void
*/
int insertData() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /* Open database */
    rc = sqlite3_open("przychodnia.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sql = "INSERT INTO patients (ID,name,secondName,pesel,birthDate) "  \
         "VALUES (1, 'Paul', 'Romanow', '92112380993', '22-09-92' ); " \
         "INSERT INTO patients (ID,name,secondName,pesel,birthDate) "  \
         "VALUES (2, 'Allen', 'Smith', '92156380993', '11-09-92' ); "     \
         "INSERT INTO patients (ID,name,secondName,pesel,birthDate)" \
         "VALUES (3, 'Teddy', 'Kowalski', '86112380993', '03-09-92' );" \
         "INSERT INTO patients (ID,name,secondName,pesel,birthDate)" \
         "VALUES (4, 'Mark', 'Cukerberg', '73112380993', '13-09-92' );";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    return 1;
}