#include "UnitDiskCoverUnitGrid.h"
#include "CgalComponents.h"

struct pair_hash {
    inline size_t operator()(const pair<int,int> &v) const {
        return v.first*31+v.second;
    }
};

/*UnitDiskCoverUnitGrid::UnitDiskCoverUnitGrid(vector<Point> &P,vector<Point> &C) {
    C.clear();

    //unordered_set< pair<int,int>,  pair_hash> hashTableForDiskCenters;

    for( Point p : P ) {
        bool isAlreadyCovered = false;
        for( Point c : C) {
            Circle circle(c,1);
            if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY) {
                isAlreadyCovered = true;
                break;
            }
        }
        if( !isAlreadyCovered ) {
            int col = floor(p.y()), row = floor(p.x());

            if( row % 2 == 0) {
                if( col % 2 != 0) {
                    Circle circle(Point(row+1,col),1);
                    if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY)
                        C.push_back(Point(row+1,col));
                    else
                        C.push_back(Point(row,col+1));
                }
                else {
                    Circle circle(Point(row,col),1);
                    if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY)
                        C.push_back(Point(row,col));
                    else
                        C.push_back(Point(row+1,col+1));
                }
            }
            else {
                if( col % 2 != 0) {
                    Circle circle(Point(row,col),1);
                    if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY)
                        C.push_back(Point(row,col));
                    else
                        C.push_back(Point(row+1,col+1));
                }
                else {
                    Circle circle(Point(row,col+1),1);
                    if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY)
                        C.push_back(Point(row,col+1));
                    else
                        C.push_back(Point(row+1,col));
                }
            }
        }
    }
}*/

UnitDiskCoverUnitGrid::UnitDiskCoverUnitGrid(vector<Point> &P,vector<Point> &C) {
    C.clear();

    unordered_set< pair<int,int>, pair_hash> hashTableForDiskCenters;

    for( Point p : P ) {
            int col = floor(p.y()), row = floor(p.x());

            if( row % 2 == 0) {
                if( col % 2 != 0) {

                    Circle c1(Point(row+1,col),1), c2(Point(row,col+1),1);

                    /* p belongs to c1 but not to c2*/
                    if( !c1.has_on_unbounded_side(p) && c2.has_on_unbounded_side(p)) {
                        auto search = hashTableForDiskCenters.find(make_pair(row+1,col));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row+1,col));
                             C.push_back(Point(row+1,col));
                        }

                    }
                    /* p belongs to c2 but not to c1*/
                    else if(c1.has_on_unbounded_side(p) && !c2.has_on_unbounded_side(p) ){
                        auto search = hashTableForDiskCenters.find(make_pair(row,col+1));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row,col+1));
                             C.push_back(Point(row,col+1));
                        }
                    }
                    /* p belongs to both of them */
                    else {
                        auto search1 = hashTableForDiskCenters.find(make_pair(row+1,col));
                        auto search2 = hashTableForDiskCenters.find(make_pair(row,col+1));

                        if( search1 == hashTableForDiskCenters.end() && search2 == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row+1,col));
                             C.push_back(Point(row+1,col));
                        }
                    }
                }
                else {
                    /*Circle circle(Point(row,col),1);
                    if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY)
                        C.push_back(Point(row,col));
                    else
                        C.push_back(Point(row+1,col+1));*/

                    Circle c1(Point(row,col),1), c2(Point(row+1,col+1),1);

                    /* p belongs to c1 but not to c2*/
                    if( !c1.has_on_unbounded_side(p) && c2.has_on_unbounded_side(p)) {
                        auto search = hashTableForDiskCenters.find(make_pair(row,col));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row,col));
                             C.push_back(Point(row,col));
                        }

                    }
                    /* p belongs to c2 but not to c1*/
                    else if(c1.has_on_unbounded_side(p) && !c2.has_on_unbounded_side(p) ){
                        auto search = hashTableForDiskCenters.find(make_pair(row+1,col+1));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row+1,col+1));
                             C.push_back(Point(row+1,col+1));
                        }
                    }
                    /* p belongs to both of them */
                    else {
                        auto search1 = hashTableForDiskCenters.find(make_pair(row,col));
                        auto search2 = hashTableForDiskCenters.find(make_pair(row+1,col+1));

                        if( search1 == hashTableForDiskCenters.end() && search2 == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row,col));
                             C.push_back(Point(row,col));
                        }
                    }


                }
            }
            else {
                if( col % 2 != 0) {
                    /*Circle circle(Point(row,col),1);
                    if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY)
                        C.push_back(Point(row,col));
                    else
                        C.push_back(Point(row+1,col+1));*/


                   Circle c1(Point(row,col),1), c2(Point(row+1,col+1),1);

                    /* p belongs to c1 but not to c2*/
                    if( !c1.has_on_unbounded_side(p) && c2.has_on_unbounded_side(p)) {
                        auto search = hashTableForDiskCenters.find(make_pair(row,col));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row,col));
                             C.push_back(Point(row,col));
                        }

                    }
                    /* p belongs to c2 but not to c1*/
                    else if(c1.has_on_unbounded_side(p) && !c2.has_on_unbounded_side(p) ){
                        auto search = hashTableForDiskCenters.find(make_pair(row+1,col+1));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row+1,col+1));
                             C.push_back(Point(row+1,col+1));
                        }
                    }
                    /* p belongs to both of them */
                    else {
                        auto search1 = hashTableForDiskCenters.find(make_pair(row,col));
                        auto search2 = hashTableForDiskCenters.find(make_pair(row+1,col+1));

                        if( search1 == hashTableForDiskCenters.end() && search2 == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row,col));
                             C.push_back(Point(row,col));
                        }
                    }

                }
                else {
                    /*Circle circle(Point(row,col+1),1);
                    if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY)
                        C.push_back(Point(row,col+1));
                    else
                        C.push_back(Point(row+1,col));*/

                    Circle c1(Point(row,col+1),1), c2(Point(row+1,col),1);

                    /* p belongs to c1 but not to c2*/
                    if( !c1.has_on_unbounded_side(p) && c2.has_on_unbounded_side(p)) {
                        auto search = hashTableForDiskCenters.find(make_pair(row,col+1));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row,col+1));
                             C.push_back(Point(row,col+1));
                        }

                    }
                    /* p belongs to c2 but not to c1*/
                    else if(c1.has_on_unbounded_side(p) && !c2.has_on_unbounded_side(p) ){
                        auto search = hashTableForDiskCenters.find(make_pair(row+1,col));
                        if( search == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row+1,col));
                             C.push_back(Point(row+1,col));
                        }
                    }
                    /* p belongs to both of them */
                    else {
                        auto search1 = hashTableForDiskCenters.find(make_pair(row,col+1));
                        auto search2 = hashTableForDiskCenters.find(make_pair(row+1,col));

                        if( search1 == hashTableForDiskCenters.end() && search2 == hashTableForDiskCenters.end()) {
                             hashTableForDiskCenters.emplace(pair<int,int>(row,col+1));
                             C.push_back(Point(row,col+1));
                        }
                    }

                }
            }
    }
    hashTableForDiskCenters.clear();
}
