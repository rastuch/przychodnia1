#include <stdio.h>
#include "sqlite3.h"
#include "views.h"

/*!
 * Funckja g³ówna ktora zarzadza wylaczaniem aplikacji
 * @note Wywo³anie w petli funkcji wyboru sekcji
 * @return integer
 */
int appWorker(){
    printf("Hello, Przychodnio!\n");
    int isAppTurnOn = 1;
    while(isAppTurnOn) {
       isAppTurnOn = choiceActionTable();
    }
}


/*!
 * Funckja g³ówna uruchamiajaca appWorker();
 *
 */
int main() {
    appWorker();
    return 0;
}