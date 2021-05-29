//
// Created by programista on 28.03.2021.
//

#include "doctors.h"
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Struktura reprezentujaca tabele Lekarza w bazie danych
  */
struct Doctor {
    int id; /**< Identyfikator */
    char name[200]; /**< Imie */
    char secondName[200]; /**< Nazwisko */
    char pesel[50]; /**< Numer PESEL */
    char pwzNumber[50]; /**< Numer PWZ */
    char title[200]; /**< Tytul naukowy */
    char specialization[200]; /**< Specjalizacja */
    char email[200]; /**< Email */
    char birthDate[200]; /**< Data urodzenia w formacie DD-MM-YYYY */
    char address[200]; /**< Adres */
    char phone[50]; /**< Numer telefonu */
    char weight[200]; /**< Waga */
    char height[200]; /**< Wzrost */
    char nfz[200]; /**< NFZ */
};


/*!
 * Funkcja pomocnicza do konkatynacji tablic charow
 *
 * @param num_args liczba stringów do konkatynacji
 *
 * @return void
*/
char *strconcat1(int num_args, ...) {
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


/*!
 * Funkcja pozwaljaca ustalic rodzaj wedlug jakiej kolumny ma zostac posortowane wyniki
 *
 *
 * @return char* wskaznik z tablica charow okreslajaca nazwe tabeli w bazie danych
*/
const char* columnNameDoctorChoice() {
    int choiceNumber;
    printf("\n1.ID 2.Imie 3.Nazwisko 4.Pesel, 5.PWZ 6.Tytul\n7.Specjalizacja 8.Email 9.Data urodzenia 10.Adres 11.Telefon\n12.Waga 13.Wzrost 14.NFZ");
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
            char *table = "pwzNumber";
            return table;
        }
        case 6: {
            char *table = "title";
            return table;
        }
        case 7: {
            char *table = "specialization";
            return table;
        }
        case 8: {
            char *table = "email";
            return table;
        }
        case 9: {
            char *table = "birthDate";
            return table;
        }
        case 10: {
            char *table = "address";
            return table;
        }
        case 11: {
            char *table = "phone";
            return table;
        }
        case 12: {
            char *table = "weight";
            return table;
        }
        case 13: {
            char *table = "height";
            return table;
        }
        case 14: {
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
const char* sortDoctorOrder() {
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
 * Domyslna funkcja wywolania zwrotnego uzywana uzyskania informacji o poprawnym odczytaniu danych z bazy
 *
 * @return int
*/
static int callback(void *data, int argc, char **argv, char **azColName) {
    printf("All good\n");
    return 0;
}

/*!
 * Zmienna z aktualnym lekarzem
 */
struct Doctor doctor;

/*!
 * Zmienna pomocnicza z lekarzem o pustych wartosciach
 */
struct Doctor emptyDoctor;

/*!
 * Funkcja usuwaj¹ca lekarza z bazy przyjmuj¹ca za argument id
 * @param id identyfikator u¿ytkownika do usuniêcia
 * @retrun void
*/
void deleteDoctorById(char id[50]) {
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
    char sql[200] = "DELETE from doctors where ID=";
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
 * Funkcja aktualizujaca lekarza w bazie, przyjmuje za argumeny id uzytkownika oraz strukture Doctor
 * jako obiekt do ktorego ma zostac zaktualizowany
 *
 * @param id identyfikator pacjenta do zaktualizowania
 * @param newDoctor zmienna zwierajaca strukture "doctor" do zaktualizowania
 * @return void
*/
void updateDoctorById(char id[50], struct Doctor newDoctor) {
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
    char sql[5050] = "UPDATE doctors set ";
    struct Doctor up = newDoctor;
    char setData[5000];

    snprintf(setData, sizeof(setData),
             "name = '%s' , secondName = '%s' , pesel = '%s' , pwzNumber = '%s', title = '%s'," \
             " specialization = '%s', birthDate = '%s', address = '%s', email = '%s', phone = '%s',  weight = '%s'," \
             " height = '%s', nfz = '%s' where id=%s;",
             up.name, up.secondName, up.pesel, up.pwzNumber, up.title, up.specialization, up.birthDate, up.address,
             up.email, up.phone, up.weight, up.height,up.nfz, id);
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
 * Funkcja dodajaca lekarza do bazy przyjmujaca za argument strukture "patient"
 * @param newPatient zmienna zwierajaca strukture "doctor" do zapisania
 * @return void
*/
void addDoctor(struct Doctor newDoctor) {
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
    char sql[50500] = "INSERT INTO doctors (name,secondName,pesel,pwzNumber,title,specialization,birthDate,address,email,phone,weight,height,nfz) "  \
         "VALUES ";
    char setData[5000];
    struct Doctor up = newDoctor;
    snprintf(setData, sizeof(setData),
             "('%s', '%s', '%s', '%s', '%s', '%s', " \
             "'%s', '%s', '%s', '%s', '%s', '%s', '%s');",
             up.name, up.secondName, up.pesel, up.pwzNumber, up.title, up.specialization, up.birthDate, up.address,
             up.email, up.phone, up.weight, up.height, up.nfz);
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


/*!
 *Funkcja wywo³ania zwrotnego przypisujaca informacje z bazy danych do stuktury lekarza
 *
 *
 * @return int
*/
static int cbGetDoctor(void *data, int argc, char **argv, char **colName) {

    /* Funkcja korzysta ze zmiennej globalnej "doctor" wiêc wymaga upewnienia siê ¿e jest pusta
     * poprzez przypisanie obiektu "emptyDoctor" */
    doctor = emptyDoctor;
    strcpy(doctor.name, argv[1] ? argv[1] : "NULL");
    strcpy(doctor.secondName, argv[2] ? argv[2] : "NULL");
    strcpy(doctor.pesel, argv[3] ? argv[3] : "NULL");
    strcpy(doctor.pwzNumber, argv[4] ? argv[4] : "NULL");
    strcpy(doctor.title, argv[5] ? argv[5] : "NULL");
    strcpy(doctor.specialization, argv[6] ? argv[6] : "NULL");
    strcpy(doctor.birthDate, argv[7] ? argv[7] : "NULL");
    strcpy(doctor.address, argv[8] ? argv[8] : "NULL");
    strcpy(doctor.email, argv[9] ? argv[9] : "NULL");
    strcpy(doctor.phone, argv[10] ? argv[10] : "NULL");
    strcpy(doctor.weight, argv[11] ? argv[11] : "NULL");
    strcpy(doctor.height, argv[12] ? argv[12] : "NULL");
    strcpy(doctor.nfz, argv[13] ? argv[13] : "NULL");
    return 0;
}


/*!
 *Funkcja zwracaj¹ca strukture doctor z bazy danych na podstawie podanego parametru id
 *
 * @param id identyfikator lekarza do wyswietlenia
 * @return void
*/
struct Doctor getDoctorById(char id[50]) {
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
    char sql[] = "SELECT * from doctors where id=";
    strcat(sql, id);
    strcat(sql, ";");

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, cbGetDoctor, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        // fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
    return doctor;
}


/*!
 *Funkcja wywolania zwrotnego wswietlajaca liste lekarzy
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
 *Funkcja wyszukiwaj¹ca lekarza wedlug imienia i nazwiska lub numerze pwz
 *
 * @param nameOrSecondNameOrPwz imie lub nazwisko lekarza lub numerze pwz do wyszukania
 * @return void
*/
void searchDoctors(char nameOrSecondNameOrPwz[100] ) {
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
        sql = "test";
    /* Create SQL statement */
    sql = strconcat1(9, "SELECT * from doctors where name like '%%", nameOrSecondNameOrPwz,"%%' ",
                    "OR secondName like '%%",nameOrSecondNameOrPwz,"%%' ",
                     "OR pwzNumber like '%%",nameOrSecondNameOrPwz,"%%'");
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
 *Funkcja wyswietla listê wszystkich lekarzy
 *
 * @param sortByColumnName nazwa columny wedlug ktorej maja zostac posortowane wyniki
 * @param sortOrder rodzaj sortowania
 * @return void
*/
void showAllDoctors(char sortByTableName[], char sortOrder[]) {
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
    sql = "SELECT * from doctors order by ";

    snprintf(setData, sizeof(setData),
             "%s%s %s",
             sql,sortByTableName,sortOrder);

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



int insertDataDoctors() {
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
    sql = "INSERT INTO doctors (ID,name,secondName,pesel,birthDate,pwzNumber,title,specialization) "  \
         "VALUES (1, 'Dobrogost', 'Ostrowski', '77110683593', '11-06-1977','998234','prof.','kardiochirurg' ); " \
         "INSERT INTO doctors (ID,name,secondName,pesel,birthDate,pwzNumber,title,specialization) "  \
         "VALUES (2, 'Zofia', 'Kaczmarek', '83050422967', '05-04-1983','119203','dr.','internista'); "     \
         "INSERT INTO doctors (ID,name,secondName,pesel,birthDate,pwzNumber,title,specialization)" \
         "VALUES (3, 'Ziemowit', 'Kwiatkowski', '93061694871', '06-11-1993','553455','dr. mgr.', 'neurolog');" \
         "INSERT INTO doctors (ID,name,secondName,pesel,birthDate,pwzNumber,title,specialization)" \
         "VALUES (4, 'Zuzanna', 'Borkowska', '96080134063', '96-01-96','234523','dr.','ortopeda');";

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