#include "UnitDiskCoverCenters.h"
#include "CgalComponents.h"

UnitDiskCoverCenters::UnitDiskCoverCenters(vector<Point> &P, vector<Point> &C) {

  DelunayTriangulation T;
  bool isEmptyTriangulation = true;

  for( Point p : P ) {
        if(isEmptyTriangulation) {
          isEmptyTriangulation = false;
          C.push_back(p);
          T.insert(p);
        }
        else {
          Vertex_handle handleToTheNearestDiskCenter = T.nearest_vertex(p);
          if(squared_distance(p,handleToTheNearestDiskCenter->point()) > 1) {
            C.push_back(p);
            T.insert(p);
          }
        }
  }
  T.clear();
}

/*UnitDiskCoverCenters::UnitDiskCoverCenters(vector<Point> &P, vector<Point> &C){
    for(int i = 0; i < P.length-1; ++i){
        bool isCovered = false;
        for(int j = i+1; j < P.length; ++j){

            Circle_2<K> circle(x, y, 1);
            Circle_2<K> circle(x+(sqrt(3)/2), y+1.5, 1);
            Circle_2<K> circle(x+sqrt(3), y, 1);
            Circle_2<K> circle(x+(sqrt(3)/2), y-1.5, 1);
            for(Point c : C){
                    if(circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY){
                        isCovered = true;
                        break;
                    }
            }
            if(!isCovered){
                C.push_back(p);
            }
        }
    }
    }
}*/

/*UnitDiskCoverCenters::UnitDiskCoverCenters(vector<Point> &P, vector<Point> &C) {
  for( Point p : P ) {
        bool isAlreadyCovered = false;
        for( Point c : C) {
            Circle_2<K> circle(c,1);
            if( circle.bounded_side(p) == ON_BOUNDED_SIDE || circle.bounded_side(p) == ON_BOUNDARY) {
                isAlreadyCovered = true;
                break;
            }
        }
        if( !isAlreadyCovered )
            C.push_back(p);
    }
}*/
