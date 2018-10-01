//Unit Disk Cover - Brute Force
#include <CGAL/Simple_cartesian.h>
#include <cassert>
#include <vector>
#include <algorithm>
#include <CGAL/point_generators_2.h>
#include <CGAL/algorithm.h>
#include <CGAL/random_selection.h>

#include <nlohmann/json.hpp>

#include <fstream>

using namespace CGAL;
using namespace std;
using json = nlohmann::json;

typedef Simple_cartesian<double>         R;
typedef R::Point_2                       Point;
typedef Creator_uniform_2<double,Point>  Creator;
typedef std::vector<Point>               Vector;

void generateRandomPoints(Vector& points, int num){
    points.reserve(num);
    Random_points_in_square_2<Point,Creator> g( 200.0);
    CGAL::cpp11::copy_n( g, num, std::back_inserter(points));
    cout << " Generated " << points.size() << " random points" << endl;
}

void showPoints(Vector& points){
    for(long unsigned int i=0; i<points.size(); i++) {
        cout << " Point[" << i << "] " << points[i].x() << ", " << points[i].y() << endl; 
    }
}

void loadFromFile(Vector& points){
    json jsonData;
    ifstream inputFile("data.json");
    inputFile >> jsonData;

    for(long unsigned int i=0; i<jsonData["points"].size(); i++) {
        Point p(jsonData["points"][i]["x"], jsonData["points"][i]["y"]);
        points.push_back(p);
    }
}

/**
 * Psuedo Code
 * Create Points (either random or form file)
 * For each point
 *      If point does not belong to an existing disc
 *          Create a new disc
 */
int main(){
    int menuChoice, sampleSize, unitSize;
    Vector points;

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
            generateRandomPoints(points, sampleSize);
            break;
        case 2 : 
            loadFromFile(points);
            break;            
        case 3 : 
        default :
            return 0;
    }

    showPoints(points);

    cout << endl << " What is the size of a unit? : ";
    cin >> unitSize;
}
