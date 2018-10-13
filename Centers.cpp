#include <Centers.h>

void Centers::generateRandomPoints(int num, int graphSize){
    points.reserve(num);
    Random_points_in_square_2<Point,Creator> g(graphSize);
    CGAL::cpp11::copy_n( g, num, std::back_inserter(points));
    cout << " Generated " << points.size() << " random points" << endl;
}

void Centers::generateUnitDiscBucket(int graphSize){
    for(int i=-graphSize; i<=graphSize; i+=2) {
        for(int j=-graphSize; j<=graphSize; j+=2) {
            Point center(i, j);
            Circle unitDisc(center, unitSize, CGAL::COUNTERCLOCKWISE);
            unitDiscBucket.push_back(unitDisc);
        }
    }
    for(int i=-graphSize+1; i<=graphSize; i+=2) {
        for(int j=-graphSize+1; j<=graphSize; j+=2) {
            Point center(i, j);
            Circle unitDisc(center, unitSize, CGAL::COUNTERCLOCKWISE);
            unitDiscBucket.push_back(unitDisc);
        }
    }
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
    addUnitDisc(points[0]);
}

void Centers::addUnitDisc(Point center){
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
    //cout << endl << " [Centers] findDiscCenters " << endl;

    for(long unsigned int i=0; i<points.size(); i++) {
        //cout << " Testing Point[" << i << "] " 
        //    << points[i].x() << ", " << points[i].y(); 
        
        bool isNotCovered = true;

        for(long unsigned int j=0; j<unitDiscs.size(); j++) {
            if (!unitDiscs[j].has_on_unbounded_side(points[i])){
                //cout << " -- is covered by  Unit Disc[" << j << "] " << endl;
                isNotCovered = false;
                break;
            }
        }

        if (isNotCovered) {
            //cout << " -- is not covered" << endl;
            addUnitDisc(points[i]);
        }
    }
}

void Centers::findDiscCentersGreedy(){
    //cout << endl << " [Centers] findDiscCentersGreedy " << endl;

    for(long unsigned int i=0; i<points.size(); i++) {
        //cout << " Testing Point[" << i << "] " 
        //    << points[i].x() << ", " << points[i].y() << endl;

        
        int x_floor = floor(points[i].x());
        int x_ceil = ceil(points[i].x());
        int y_floor = floor(points[i].y());
        int y_ceil = ceil(points[i].y());

        bool x_floor_is_even = (x_floor % 2 == 0);
        bool y_floor_is_even = (y_floor % 2 == 0);

        int x1, x2, y1, y2;

        if (x_floor_is_even == y_floor_is_even){
            x1 = x_floor;
            y1 = y_floor;
            x2 = x_ceil;
            y2 = y_ceil;
        } else {
            x1 = x_floor;
            y1 = y_ceil;  
            x2 = x_ceil;
            y2 = y_floor; 
        }

        Point testDiscCenter1(x1, y1);  
        Point testDiscCenter2(x2, y2); 

        Circle testDisc1(testDiscCenter1, unitSize, CGAL::COUNTERCLOCKWISE);
        Circle testDisc2(testDiscCenter2, unitSize, CGAL::COUNTERCLOCKWISE);

        if (!testDisc1.has_on_unbounded_side(points[i])) {
            unitDiscs.push_back(testDisc1);
        } else if (!testDisc2.has_on_unbounded_side(points[i])) {
            unitDiscs.push_back(testDisc2);
        } else if (!testDisc1.has_on_unbounded_side(points[i]) && !testDisc2.has_on_unbounded_side(points[i])){
            unitDiscs.push_back(testDisc1);
            unitDiscs.push_back(testDisc2);
        }
    }
}

PointVector Centers::getPoints(){
    return points;
}

CircleVector Centers::getUnitDiscs(){
    return unitDiscs;
}

CircleVector Centers::getUnitDiscBucket(){
    return unitDiscBucket;
}

int Centers::getUnitSize(){
    return unitSize;
}