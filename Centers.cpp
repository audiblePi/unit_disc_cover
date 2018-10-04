#include <Centers.h>

void Centers::generateRandomPoints(int num){
    points.reserve(num);
    Random_points_in_square_2<Point,Creator> g( 10.0);
    CGAL::cpp11::copy_n( g, num, std::back_inserter(points));
    cout << " Generated " << points.size() << " random points" << endl;
}

void Centers::loadFromFile(){
    json jsonData;
    ifstream inputFile("data.json");
    inputFile >> jsonData;

    for(long unsigned int i=0; i<jsonData["points"].size(); i++) {
        Point p(jsonData["points"][i]["x"], jsonData["points"][i]["y"]);
        points.push_back(p);
    }
}

void Centers::init(){
    addUnitCircle(points[0]);
}

void Centers::addUnitCircle(Point center){
    Circle unitDisc(center, unitSize, CGAL::COUNTERCLOCKWISE);
    unitDiscs.push_back(unitDisc);
}

void Centers::setUnitSize(int num){
    unitSize = num;
}

void Centers::showPoints(){
    cout << endl << " [Centers] points" << endl; 
    
    for(long unsigned int i=0; i<points.size(); i++) {
        cout << " Point[" << i << "] " 
            << points[i].x() << ", " << points[i].y() << endl; 
    }
}

void Centers::showUnitDiscCenters(){
    cout << endl << " [Centers] unit disc centers" << endl; 
    
    for(long unsigned int i=0; i<unitDiscs.size(); i++) {
        cout << " Unit Disc[" << i << "] " 
            << unitDiscs[i].center().x() << ", " 
            << unitDiscs[i].center().y(); 
        cout << "        RadiusSquared: " 
           << unitDiscs[i].squared_radius() << endl;
    }
}

void Centers::findDiscCenters(){
    cout << endl << " [Centers] findDiscCenters " << endl;

    for(long unsigned int i=0; i<points.size(); i++) {
        cout << " Testing Point[" << i << "] " 
            << points[i].x() << ", " << points[i].y(); 
        
        bool isNotCovered = true;

        for(long unsigned int j=0; j<unitDiscs.size(); j++) {
            if (!unitDiscs[j].has_on_unbounded_side(points[i])){
                cout << " -- is covered by  Unit Disc[" << j << "] " << endl;
                isNotCovered = false;
                break;
            }
        }

        if (isNotCovered) {
            cout << " -- is not covered" << endl;
            addUnitCircle(points[i]);
        }
    }
}