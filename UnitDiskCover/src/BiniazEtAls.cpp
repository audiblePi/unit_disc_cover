#include "BiniazEtAls.h"
#include "CgalComponents.h"

BiniazEtAls::BiniazEtAls(vector<Point> &P, vector<Point> &C){
    vector<Point> I;

    DelunayTriangulation T;
    bool isEmptyTriangulation = true;

    sort(P.begin(), P.end(), [](const Point& pi, const Point& pj) {
                                    return (pi.x() < pj.x()) || ( pi.x() == pj.x() && pi.y() < pj.y());
                            });

    for( Point p : P) {
        if(isEmptyTriangulation) {
          isEmptyTriangulation = false;
          C.push_back(p);
          C.push_back( Point( p.x() + std::sqrt(3), p.y() ) );
          C.push_back( Point( p.x() + std::sqrt(3)/2, p.y() - 1.5 ) );
          C.push_back( Point( p.x() + std::sqrt(3)/2, p.y() + 1.5 ) );

          T.insert(p);
        }
        else {
          Vertex_handle handleToTheNearestPoint = T.nearest_vertex(p);
          if(squared_distance(p,handleToTheNearestPoint->point()) > 2) {
            C.push_back(p);
            C.push_back( Point( p.x() + std::sqrt(3), p.y() ) );
            C.push_back( Point( p.x() + std::sqrt(3)/2, p.y() - 1.5 ) );
            C.push_back( Point( p.x() + std::sqrt(3)/2, p.y() + 1.5 ) );

            T.insert(p);
          }
        }
    }
}
