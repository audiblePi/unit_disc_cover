//Unit Disk Cover - Brute Force
#include <Centers.h>

#include <QtGui>
#include <QApplication> 
#include <QGraphicsScene>
#include <QGraphicsView> 

using namespace std;

int main(){
    int menuChoice, sampleSize, unitSize;
    Centers obj;

    cout << endl;
    cout << " Unit Disk Covers - Brute Force " << endl;
    cout << " ----------------------------- " << endl;
    cout << " 1. Load Random Points " << endl;
    cout << " 2. Load Points from File ./data.json" << endl;
    cout << " 3. Exit \n" << endl;
    cout << " Enter your choice : ";
    cin >> menuChoice;

    switch(menuChoice){
        case 1 :
            cout << endl << " How many points should be generated? : ";
            cin >> sampleSize;
            obj.generateRandomPoints(sampleSize);
            break;
        case 2 : 
            obj.loadFromFile();
            break;            
        case 3 : 
        default :
            return 0;
    }

    cout << endl << " What is the size of a unit? : ";
    cin >> unitSize;

    obj.setUnitSize(unitSize);
    obj.init();
    obj.showPoints();
    obj.findDiscCenters();
    obj.showUnitDiscCenters();
}
