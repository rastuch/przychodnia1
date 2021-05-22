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


static int callback(void *data, int argc, char **argv, char **azColName) {
    printf("All good\n");
    return 0;
}

struct Doctor doctor;
struct Doctor emptyDoctor;

/* Funkcja usuwaj¹ca lekarza z bazy przyjmuj¹ca za argument id */
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


/* Funkcja aktualizujaca lekarza w bazie, przyjmuje za argumeny id u¿ytkownika oraz strukture Doctor
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

/* Funkcja dodaj¹ca pacjenta do bazy przyjmuj¹ca za argument strukture "doctor" */
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


/* Funkcja zwracaj¹ca strukture doctor z bazy danych na podstawie podanego parametru id */
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


/* Funkcja wywo³ania zwrotnego wyœwietlaj¹ca liste wszystkich lekarzy */
static int cbShowAllPatients(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

    }
    printf("\n");
    return 0;
}

/* Funkcja wyœwietla listê wszystkich lekarzy */
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