//Unit Disk Cover - Brute Force
#include <Centers.h>
#include <UnitDiskCoverPrinter.h>

#include <QtGui>
#include <QApplication> 
#include <QGraphicsScene>
#include <QGraphicsView> 
#include <QPointF>

#include <ctime>
#include <math.h> 

using namespace std;

void showMenu(Centers* obj, int graphSize){
    int menuChoice, sampleSize;

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
            obj->generateRandomPoints(sampleSize, graphSize);
            break;
        case 2 : 
            obj->loadFromFile();
            break;            
        case 3 : 
        default :
            return;
    }

    // cout << endl << " Size of a unit? : ";
    // cin >> unitSize;
    
    obj->setUnitSize(1);
}

int main(int argc, char **argv){
    int graphSize = 10;
    clock_t begin, end;
    double elapsed_secs;

    Centers obj;
    PointVector points;
    PointVector unitDiscCentersPoints;
    PointVector unitDiscCentersGridPoints;
    CircleVector unitDiscsCenters;
    CircleSet unitDiscsGrid;

    showMenu(&obj, graphSize);

    points = obj.getPoints();

    begin = clock();
    unitDiscsCenters = obj.findDiscCenters();
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << " Time taken: " << elapsed_secs << endl;
    cout << " Number of disks placed: " << unitDiscsCenters.size() << endl;

    unitDiscCentersPoints = obj.getUnitDiscCenters();
    // UnitDiskCoverPrinter newPrinter1(points, unitDiscCentersPoints, 1.0, "testoutput1");
    // newPrinter1.displayPDF();

    obj.clear();
    begin = clock();
    unitDiscsGrid = obj.findDiscCentersGrid();
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << " Time taken: " << elapsed_secs << endl;
    cout << " Number of disks placed: " << unitDiscsGrid.size() << endl;
    unitDiscCentersGridPoints = obj.getUnitDiscCentersGrid();
    // UnitDiskCoverPrinter newPrinter2(points, unitDiscCentersGridPoints, 1, "test_output2");
    // newPrinter2.displayPDF();

    return 1;
}
