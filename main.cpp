//Unit Disk Cover - Brute Force
#include <cassert>
#include <vector>
#include <algorithm>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/algorithm.h>
#include <CGAL/random_selection.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Circle_2.h>

#include <nlohmann/json.hpp>

#include <fstream>

using namespace CGAL;
using namespace std;
using json = nlohmann::json;

typedef Simple_cartesian<double>        R;
typedef R::Point_2                      Point;
typedef R::Circle_2                     Circle;
typedef Creator_uniform_2<double,Point> Creator;
typedef std::vector<Point>              PointVector;
typedef std::vector<Circle>             CircleVector;


/**
 * Takes input points
 * For each point
 *      If point does not belong to an existing disc
 *          Create a new disc
 * Return the set of unit disc centers
 */
class Centers{
    private:
        PointVector points;
        CircleVector unitDiscs;
        int unitSize;
    
    public:
        Centers(){}

        Centers(PointVector points, int unitSize){
            points = points;
            unitSize = unitSize;
        }
        
        void generateRandomPoints(int);
        void loadFromFile();
        void init();
        void addUnitCircle(Point);
        void setUnitSize(int);
        void showPoints();
        void showUnitDiscCenters();
        CircleVector findDiscCenters();
};

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

CircleVector Centers::findDiscCenters(){
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

    return unitDiscs;
}








/**
 * Psuedo Code
 * Create Points (either random or form file)
 * Create new Centers object with data (or file)
 * Call ob.findUnitDiskCover()
 * Output to json file
 */
int main(){
    int menuChoice, sampleSize, unitSize;
    Centers obj;
    CircleVector output;

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
    output = obj.findDiscCenters();
    obj.showUnitDiscCenters();
}
