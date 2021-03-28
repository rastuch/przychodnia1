//
// Created by programista on 28.03.2021.
//

#include "doctors.h"
#include <string.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>

struct Doctor {
    int id;
    char name[200];
    char secondName[200];
    char pesel[50];
    char pwzNumber[50];
    char title[200];
    char specialization[200];
    char email[200];
    char birthDate[200];
    char address[200];
    char phone[50];
    char weight[200];
    char height[200];
    char nfz[200];
};

static int callback(void *data, int argc, char **argv, char **azColName) {
    printf("All good\n");
    return 0;
}

struct Doctor doctor;
struct Doctor emptyDoctor;

/* Funkcja usuwająca lekarza z bazy przyjmująca za argument id */
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


/* Funkcja aktualizujaca lekarza w bazie, przyjmuje za argumeny id użytkownika oraz strukture Doctor
 * jako obiekt do ktorego ma zostac zaktualizowany */
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

/* Funkcja dodająca pacjenta do bazy przyjmująca za argument strukture "doctor" */
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



static int cbGetDoctor(void *data, int argc, char **argv, char **colName) {

    /* Funkcja korzysta ze zmiennej globalnej "doctor" więc wymaga upewnienia się że jest pusta
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


/* Funkcja zwracająca strukture doctor z bazy danych na podstawie podanego parametru id */
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


/* Funkcja wywołania zwrotnego wyświetlająca liste wszystkich lekarzy */
static int cbShowAllPatients(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

    }
    printf("\n");
    return 0;
}

/* Funkcja wyświetla listę wszystkich lekarzy */
void showAllDoctors() {
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
    sql = "SELECT * from doctors";

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