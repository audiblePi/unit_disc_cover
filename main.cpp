//Unit Disk Cover - Brute Force
#include <cassert>
#include <vector>
#include <algorithm>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/algorithm.h>
#include <CGAL/random_selection.h>
#include <CGAL/squared_distance_2.h>

#include <nlohmann/json.hpp>

#include <fstream>

using namespace CGAL;
using namespace std;
using json = nlohmann::json;

typedef Simple_cartesian<double>         R;
typedef R::Point_2                       Point;
typedef Creator_uniform_2<double,Point>  Creator;
typedef std::vector<Point>               Vector;


/**
 * Takes input points
 * For each point
 *      If point does not belong to an existing disc
 *          Create a new disc
 * Return the set of unit disc centers
 */
class Centers{
    private:
        Vector points;
        Vector unitDiscCenters;
        int unitSize;
    
    public:
        Centers(){}

        Centers(Vector points, int unitSize){
            points = points;
            unitSize = unitSize;
        }
        
        void generateRandomPoints(int);
        void loadFromFile();
        void init();
        void setUnitSize(int);
        void showPoints();
        void showUnitDiscCenters();
        void findDiscCenters();
};

void Centers::generateRandomPoints(int num){
    points.reserve(num);
    Random_points_in_square_2<Point,Creator> g( 200.0);
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
    //start with the first point as a center for the first disc
    unitDiscCenters.push_back(points[0]);
}

void Centers::setUnitSize(int num){
    unitSize = num;
}

void Centers::showPoints(){
    cout << endl << " [Centers] points" << endl; 
    
    for(long unsigned int i=0; i<points.size(); i++) {
        cout << " Point[" << i << "] " << points[i].x() << ", " << points[i].y() << endl; 
    }
}

void Centers::showUnitDiscCenters(){
    cout << endl << " [Centers] unit disc centers" << endl; 
    
    for(long unsigned int i=0; i<unitDiscCenters.size(); i++) {
        cout << " Unit Disc Center[" << i << "] " << unitDiscCenters[i].x() << ", " << unitDiscCenters[i].y() << endl; 
    }
}

void Centers::findDiscCenters(){
    cout << endl << " [Centers] findDiscCenters " << endl;

    // for(long unsigned int i=0; i<points.size(); i++) {
    //     //cout << " Point[" << i << "] " << points[i].x() << ", " << points[i].y() << endl; 
    // }
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

    obj.init();
    obj.setUnitSize(unitSize);
    obj.showPoints();
    obj.showUnitDiscCenters();
    obj.findDiscCenters();
}
