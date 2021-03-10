//
// Created by programista on 09.03.2021.
//
#include "patients.h"
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>

struct Patient {
    char name[200];
    char secondName[200];
    char pesel[50];
    char birthDate[200];
    char address[200];
    char email[200];
    char phone[50];
    char weight[200];
    char height[200];
    char nfz[200];
};

struct Patient patient;
struct Patient emptyPatient;


static int callback(void *data, int argc, char **argv, char **azColName) {
    printf("All good\n");
    return 0;
}

/* Funkcja usuwająca pacjenta z bazy przyjmująca za argument id */
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

/* Funkcja dodająca pacjenta do bazy przyjmująca za argument strukture "patient" */
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


/* Funkcja aktualizujaca pacjenta w bazie, przyjmuje za argumeny id użytkownika oraz strukture Patient
 * jako obiekt do ktorego ma zostac zaktualizowany */
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


/* Funkcja wywołania zwrotnego przypisujaca informacje z bazy danych do stuktury pacjent */
static int cbGetPatient(void *data, int argc, char **argv, char **colName) {

    /* Funkcja korzysta ze zmiennej globalnej "patient" więc wymaga upewnienia się że jest pusta
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


/* Funkcja zwracająca strukture patient z bazy danych na podstawie podanego parametru id */
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


/* Funkcja wywołania zwrotnego wyświetlająca liste wszystkich pacjentów */
static int cbShowAllPatients(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

    }
    printf("\n");
    return 0;
}

/* Funkcja wyświetla listę wszystkich pacjentów */
void showAllpatients() {
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
    sql = "SELECT * from patients";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, cbShowAllPatients, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //   fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}



//Insert data i callback to funkcje pomocnicze do uzupełniania tabeli


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
