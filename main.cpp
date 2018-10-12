//Unit Disk Cover - Brute Force
#include <Centers.h>

#include <QtGui>
#include <QApplication> 
#include <QGraphicsScene>
#include <QGraphicsView> 
#include <QPointF>

#include <math.h> 

using namespace std;

int showMenu(Centers* obj, int graphSize){
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
            return 0;
    }

    cout << endl << " Size of a unit? : ";
    cin >> unitSize;
    
    obj->setUnitSize(unitSize * unitSize);

    cout << endl;
    cout << " Choose " << endl;
    cout << " 1. Brute Force " << endl;
    cout << " 2. Greedy" << endl;
    cout << " Enter your choice : ";
    cin >> menuChoice;

   return menuChoice;
}

int main(int argc, char **argv){
    double unitSize;
    int graphSize = 10;
    int pointScale = 30;
    int pointSize = 5;
    int which;

    QApplication app(argc, argv);
    QGraphicsScene scene;
    QGraphicsView* view = new QGraphicsView(&scene);
    
    Centers obj;
    PointVector points;
    CircleVector unitDiscs;
    //CircleVector unitDiscBucket;

    which = showMenu(&obj, graphSize);

    if (which == 1){
        obj.init();
        obj.findDiscCenters();
    } else if (which == 2) {
        obj.findDiscCentersGreedy();
    }

    //obj.showPoints();
    //obj.generateUnitDiscBucket(graphSize);
    //obj.showUnitDiscCenters();

    unitSize = sqrt( (double) obj.getUnitSize() );
    points = obj.getPoints();
    unitDiscs = obj.getUnitDiscs();
    //unitDiscBucket = obj.getUnitDiscBucket();

    





    //draw graph
    scene.setSceneRect(-graphSize * pointScale, -graphSize * pointScale, graphSize * 2 * pointScale, graphSize * 2 * pointScale);
    scene.addRect(QRectF(-graphSize * pointScale, -graphSize * pointScale, graphSize * 2 * pointScale, graphSize * 2 * pointScale));
    
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








    //plot unitDiscBucket
    // for(long unsigned int i=0; i<unitDiscBucket.size(); i++) {
    //     scene.addEllipse(QRectF(
    //         (unitDiscBucket[i].center().x() * pointScale) - (unitSize * pointScale),
    //         ((-unitDiscBucket[i].center().y() * pointScale) - (unitSize * pointScale)), 
    //         (unitSize * pointScale) * 2, 
    //         (unitSize * pointScale) * 2));
    // }

    //plot unitDiscBucketCenters
    // for(long unsigned int i=0; i<unitDiscBucket.size(); i++) {
    //     scene.addEllipse(
    //         QRectF(
    //             (unitDiscBucket[i].center().x() * pointScale) - (pointSize * 0.5),
    //             ((-unitDiscBucket[i].center().y() * pointScale) - (pointSize * 0.5)), 
    //             pointSize, 
    //             pointSize),
    //         QPen(),
    //         QBrush(Qt::black));
    // }

    //plot points
    for(long unsigned int i=0; i<points.size(); i++) {
        scene.addEllipse(
            QRectF(
                (points[i].x() * pointScale) - (pointSize * 0.5),
                ((-points[i].y() * pointScale) - (pointSize * 0.5)), 
                pointSize, 
                pointSize),
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
