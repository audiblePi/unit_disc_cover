//Centers.h
#ifndef CENTERS
#define CENTERS

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

class Centers{
    private:
        PointVector points;
        CircleVector unitDiscs;
        CircleVector unitDiscBucket;
        int unitSize;
    
    public:
        Centers(){}

        Centers(PointVector points, int unitSize){
            points = points;
            unitSize = unitSize;
        }
        
        void generateRandomPoints(int, int);
        void generateUnitDiscBucket(int);
        void loadFromFile();
        void init();
        void addUnitDisc(Point);
        void setUnitSize(int);
        void showPoints();
        void showUnitDiscCenters();
        void findDiscCenters();
        void findDiscCentersGreedy();
        PointVector getPoints();
        CircleVector getUnitDiscs();
        CircleVector getUnitDiscBucket();
        int getUnitSize();
};

#endif
