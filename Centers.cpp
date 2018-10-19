#include <Centers.h>

bool ltCircle::operator()(const Circle &c1, const Circle &c2) {
    if (c1.center().x() == c2.center().x()) {
        return c1.center().y() < c2.center().y();
    }
    else {
        return c1.center().x() < c2.center().x();
    }
}

bool Centers::compare(const Circle &c1, const Circle &c2){
    if (c1.center().x() == c2.center().x()) {
        return c1.center().y() < c2.center().y();
    }
    else {
        return c1.center().x() < c2.center().x();
    }
}

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

void Centers::clear(){
    unitDiscs.clear();
}

void Centers::addUnitDisc2(Circle circle){    
    if( std::binary_search( unitDiscSet.begin(), unitDiscSet.end(), circle, ltCircle() )) {
   
    } else {
        unitDiscSet.insert(circle);
    }
}

void Centers::addUnitDisc(Point center){
    Circle unitDisc(center, unitSize, CGAL::COUNTERCLOCKWISE);
    
    if(std::find(unitDiscs.begin(), unitDiscs.end(), unitDisc) != unitDiscs.end()) {
        cout << " Disc Found " << endl;
    } else {
        unitDiscs.push_back(unitDisc);
    }
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

CircleVector Centers::findDiscCenters(){
    init();
    cout << endl << " [Centers] findDiscCenters " << endl;

    for(long unsigned int i=0; i<points.size(); i++) {
        bool isNotCovered = true;

        for(long unsigned int j=0; j<unitDiscs.size(); j++) {
            if (!unitDiscs[j].has_on_unbounded_side(points[i])){
                isNotCovered = false;
                break;
            }
        }

        if (isNotCovered) {
            addUnitDisc(points[i]);
        }
    }

    return unitDiscs;
}

CircleSet Centers::findDiscCentersGrid(){
    cout << endl << " [Centers] findDiscCentersGrid " << endl;
    
    for(long unsigned int i=0; i<points.size(); i++) {
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
            //unitDiscs.push_back(testDisc1);
            addUnitDisc2(testDisc1);
        } else if (!testDisc2.has_on_unbounded_side(points[i])) {
            //unitDiscs.push_back(testDisc2);
            addUnitDisc2(testDisc2);
        } 
        // else if (!testDisc1.has_on_unbounded_side(points[i]) && !testDisc2.has_on_unbounded_side(points[i])){
        //     //unitDiscs.push_back(testDisc1);
        //     //unitDiscs.push_back(testDisc2);
        //     addUnitDisc2(testDisc1);
        //     addUnitDisc2(testDisc2);
        // }
    }

    return unitDiscSet;
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

PointVector Centers::getUnitDiscCenters(){
    PointVector unitDiscCenters;
    unitDiscCenters.reserve(unitDiscs.size()+1);
    
    for(long unsigned int i=0; i<unitDiscs.size(); i++) {
        Point p(unitDiscs[i].center().x(), unitDiscs[i].center().y());
        unitDiscCenters.push_back(p);
    }
    return unitDiscCenters;
}

PointVector Centers::getUnitDiscCentersGrid(){
    PointVector unitDiscCentersGrid;
    unitDiscCentersGrid.reserve(unitDiscSet.size()+1);

    for (auto elem : unitDiscSet){
        Point p(elem.center().x(), elem.center().y());
        unitDiscCentersGrid.push_back(p);
    }
    return unitDiscCentersGrid;
}


int Centers::getUnitSize(){
    return unitSize;
}
