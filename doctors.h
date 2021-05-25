//
// Created by programista on 28.03.2021.
//
/* Deklaracja funkcji typu CRUD dla struktury "Doctor" */
#ifndef PRZYCHODNIA_DOCTORS_H
#define PRZYCHODNIA_DOCTORS_H

int insertDataDoctors();

const char* columnNameDoctorChoice();

const char* sortDoctorOrder();

void showAllDoctors();

void searchDoctors(char nameOrSecondName[100] );

struct Doctor getDoctorById(char id[50]);

void addDoctor(struct Doctor newDoctor);

void updateDoctorById(char id[50], struct Doctor newDoctor);

void deleteDoctorById(char id[50]);

#endif //PRZYCHODNIA_DOCTORS_H
