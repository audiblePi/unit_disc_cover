//Centers.h
#ifndef CENTERS
#define CENTERS

#include <cassert>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
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

typedef Exact_predicates_inexact_constructions_kernel R;
//typedef Simple_cartesian<double>        R;
typedef R::Point_2                      Point;
typedef R::Circle_2                     Circle;
typedef Creator_uniform_2<double,Point> Creator;
typedef vector<Point>              PointVector;
typedef vector<Circle>             CircleVector;
struct ltCircle {
    bool operator()(const Circle &c1, const Circle &c2);
};
typedef std::set<Circle, ltCircle>      CircleSet;



class Centers{
    private:
        PointVector points;
        CircleVector unitDiscs;
        CircleVector unitDiscBucket;
        CircleSet unitDiscSet;
        int unitSize;
    
    public:
        Centers(){}
        
        void generateRandomPoints(int, int);
        void generateUnitDiscBucket(int);
        void loadFromFile();
        void init();
        void clear();
        void addUnitDisc(Point);
        void addUnitDisc2(Circle);
        void setUnitSize(int);
        void showPoints();
        void showUnitDiscCenters();
        CircleVector findDiscCenters();
        CircleSet findDiscCentersGrid();
        PointVector getPoints();
        CircleVector getUnitDiscs();
        CircleVector getUnitDiscBucket();
        PointVector getUnitDiscCenters();
        PointVector getUnitDiscCentersGrid();
        int getUnitSize();
        bool compare(const Circle &c1, const Circle &c2);
};



#endif
