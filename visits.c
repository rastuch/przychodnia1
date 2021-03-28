//
// Created by programista on 28.03.2021.
//

#include "visits.h"
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>

struct Visit {
    int id;
    char patientId[50];
    char doctorId[50];
    char date[50];
    char time[50];
    char duration[50];
    char status[200];
};

struct Visit visit;
struct Visit emptyVisit;

static int callback(void *data, int argc, char **argv, char **azColName) {
    printf("All good\n");
    return 0;
}

/* Funkcja usuwająca wizyte z bazy przyjmująca za argument id */
void deleteVisitById(char id[50]) {
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
    char sql[200] = "DELETE from visits where ID=";
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


/* Funkcja aktualizujaca wizyte w bazie, przyjmuje za argumeny id użytkownika oraz strukture Visit
 * jako obiekt do ktorego ma zostac zaktualizowany */
void updateVisitById(char id[50], struct Visit newVisit) {
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
    char sql[5050] = "UPDATE visits set ";
    struct Visit up = newVisit;
    char setData[5000];

    snprintf(setData, sizeof(setData),
             "patientId = '%s' , doctorId = '%s' , date = '%s' , time = '%s', duration = '%s', status = '%s' " \
             "where id=%s;",
             up.patientId, up.doctorId, up.date, up.time, up.duration, up.status, id);
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


/* Funkcja dodająca pacjenta do bazy przyjmująca za argument strukture "visit" */
void addVisit(struct Visit newVisit) {
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
    char sql[50500] = "INSERT INTO visits (patientId,doctorId,date,time,duration,status) "  \
         "VALUES ";
    char setData[1000];
    struct Visit up = newVisit;
    snprintf(setData, sizeof(setData),
             "('%s', '%s', '%s', '%s', '%s', '%s');",
             up.patientId, up.doctorId, up.date, up.time, up.duration, up.status);
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


/* Funkcja wywołania zwrotnego przypisujaca informacje z bazy danych do stuktury visit */
static int cbGetVisit(void *data, int argc, char **argv, char **colName) {

    /* Funkcja korzysta ze zmiennej globalnej "patient" więc wymaga upewnienia się że jest pusta
     * poprzez przypisanie obiektu "emptyPatient" */
    visit = emptyVisit;
    strcpy(visit.patientId, argv[1] ? argv[1] : "NULL");
    strcpy(visit.doctorId, argv[2] ? argv[2] : "NULL");
    strcpy(visit.date, argv[3] ? argv[3] : "NULL");
    strcpy(visit.time, argv[4] ? argv[4] : "NULL");
    strcpy(visit.duration, argv[5] ? argv[5] : "NULL");
    strcpy(visit.status, argv[6] ? argv[6] : "NULL");
    return 0;
}

/* Funkcja zwracająca strukture wizyte z bazy danych na podstawie podanego parametru id */
struct Visit getVisitById(char id[50]) {
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
    char sql[] = "SELECT * from visits where id=";
    strcat(sql, id);
    strcat(sql, ";");

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, cbGetVisit, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        // fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
    return visit;
}


/* Funkcja wywołania zwrotnego wyświetlająca liste wszystkich wizyt */
static int cbShowAllVisits(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

    }
    printf("\n");
    return 0;
}

/* Funkcja wyświetla listę wszystkich wizyt */
void showAllVisits() {
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
    sql = "SELECT * from visits";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, cbShowAllVisits, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        //   fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
}

//Insert data i callback to funkcje pomocnicze do uzupełniania tabeli
int insertVisitData() {
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
    sql = "INSERT INTO visits (ID,patientId,doctorId,date,time,duration,status) "  \
         "VALUES (1, '4', '3', '11-05-2021', '10:30', '00:30', 'zaplanowana'); " \
         "INSERT INTO visits (ID,patientId,doctorId,date,time,duration,status) "  \
         "VALUES (2, '2', '1', '11-05-2021', '12:30', '00:15', 'zaplanowana'); " \
         "INSERT INTO visits (ID,patientId,doctorId,date,time,duration,status) "  \
         "VALUES (3, '3', '3', '11-05-2021', '13:10', '00:10', 'zaplanowana'); " \
         "INSERT INTO visits (ID,patientId,doctorId,date,time,duration,status) "  \
         "VALUES (4, '5', '2', '11-05-2021', '10:30', '01:00', 'zaplanowana'); ";

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
