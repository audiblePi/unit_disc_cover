//Unit Disk Cover - Brute Force
#include <Centers.h>

#include <QtGui>
#include <QApplication> 
#include <QGraphicsScene>
#include <QGraphicsView> 
#include <QPointF>

#include <math.h> 

using namespace std;

void showMenu(Centers* obj, int graphSize){
    int menuChoice, sampleSize, unitSize;

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

    cout << endl << " Size of a unit? : ";
    cin >> unitSize;
    
    obj->setUnitSize(unitSize * unitSize);
}

int main(int argc, char **argv){
    double unitSize;
    int graphSize = 25;
    int pointScale = 10;

    QApplication app(argc, argv);
    QGraphicsScene scene;
    QGraphicsView* view = new QGraphicsView(&scene);
    Centers obj;
    PointVector points;
    CircleVector unitDiscs;

    showMenu(&obj, graphSize);
    obj.init();
    //obj.showPoints();
    obj.findDiscCenters();
    obj.showUnitDiscCenters();

    unitSize = sqrt( (double) obj.getUnitSize() );
    points = obj.getPoints();
    unitDiscs = obj.getUnitDiscs();


    





    //draw graph
    scene.setSceneRect(-graphSize * pointScale, -graphSize * pointScale, graphSize * 2 * pointScale, graphSize * 2 * pointScale);
    scene.addRect(QRectF(-graphSize * pointScale, -graphSize * pointScale, graphSize * 2 * pointScale, graphSize * 2 * pointScale));
    
    //dot graph
    // for(int i=-graphSize; i<=graphSize; i++) {
    //     for(int j=-graphSize; j<=graphSize; j++) {
    //         scene.addEllipse(QRectF(
    //             (i * pointScale) - (0.5 * pointScale),
    //             ((-j * pointScale) - (0.5 * pointScale)), 
    //             pointScale, 
    //             pointScale));
    //     }
    // }

    for(int i=-graphSize; i<=graphSize; i++) {
        scene.addLine(
            QLineF(-graphSize * pointScale, i * pointScale, graphSize * pointScale, i * pointScale),
            QPen(Qt::gray));
    }

    for(int i=-graphSize; i<=graphSize; i++) {
        scene.addLine(
            QLineF(i * pointScale, -graphSize * pointScale, i * pointScale, graphSize * pointScale),
            QPen(Qt::gray));
    }
    scene.addLine(QLineF(-graphSize * pointScale, 0 * pointScale, graphSize * pointScale, 0 * pointScale));
    scene.addLine(QLineF(0 * pointScale, -graphSize * pointScale, 0 * pointScale, graphSize * pointScale));

    //plot points
    for(long unsigned int i=0; i<points.size(); i++) {
        scene.addEllipse(
            QRectF(
                (points[i].x() * pointScale) - (0.5 * pointScale),
                ((-points[i].y() * pointScale) - (0.5 * pointScale)), 
                pointScale, 
                pointScale),
            QPen(),
            QBrush(Qt::black));
    }

    //plot unit circles
    for(long unsigned int i=0; i<unitDiscs.size(); i++) {
        scene.addEllipse(QRectF(
            (unitDiscs[i].center().x() * pointScale) - (unitSize * pointScale),
            ((-unitDiscs[i].center().y() * pointScale) - (unitSize * pointScale)), 
            (unitSize * pointScale) * 2, 
            (unitSize * pointScale) * 2));
    }

    view->show();

    return app.exec();
}
