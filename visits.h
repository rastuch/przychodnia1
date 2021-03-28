//
// Created by programista on 28.03.2021.
//

#ifndef PRZYCHODNIA_VISITS_H
#define PRZYCHODNIA_VISITS_H

int insertVisitData();

void showAllVisits();

struct Visit getVisitById(char id[50]);

void addVisit(struct Visit newVisit);

void updateVisitById(char id[50], struct Visit newVisit);

void deleteVisitById(char id[50]);

#endif //PRZYCHODNIA_VISITS_H
