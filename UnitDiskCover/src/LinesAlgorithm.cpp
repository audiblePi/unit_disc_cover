#include "LinesAlgorithm.h"
#include "CgalComponents.h"

LinesAlgorithm::LinesAlgorithm(vector<Point> &P, vector<Point> &C) {

    vector<Segment> Segments;

    sort(P.begin(), P.end(), [](const Point& pi, const Point& pj) {
                                    return (pi.x() < pj.x()) || ( pi.x() == pj.x() && pi.y() < pj.y());
                            });
    bool sorted = false;
    double counter = 3;
    int index = 0;
    while(sorted == false){
        for(Point p: P){
            index++;
            if((p.x() <= sqrt(counter))){
                Point topPoint(sqrt(counter)/2, p.y() - sqrt(1-pow((sqrt(counter)/2), 2)));
                Point bottomPoint(sqrt(counter)/2, p.y() + sqrt(1-pow((sqrt(counter)/2), 2)));
                Segment seg(topPoint, bottomPoint);
                Segments.push_back(seg);
                //sort(P.begin(), index, [](const Point& pi, const Point& pj) {
                //                                return pi.y() < pj.y();
                //                  });
                sorted = true;
            }
        }
        for(Segment s: Segments){
            C.push_back(pointlol);
            //C.push_back(midpoint(s.max(), s.min()));
        }
        counter *= 2;

    }
    cout << Segments.size() << endl;
}
