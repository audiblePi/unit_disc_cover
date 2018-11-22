#include "LinesAlgorithm.h"
#include "CgalComponents.h"

LinesAlgorithm::LinesAlgorithm(vector<Point> &P, vector<Point> &C) {

    vector<Segment> Segments;

    sort(P.begin(), P.end(), [](const Point& pi, const Point& pj) {
                                    return (pi.x() < pj.x()) || ( pi.x() == pj.x() && pi.y() < pj.y());
                            });
    bool sorted = false;
    double root = 3;
    double constant = -19;
    double counter = -39;
    int index = 0;
    while(sorted == false){
        for(Point p: P){
            index++;

            if((p.x() <= constant*sqrt(root) && p.x() >= (constant - 1)*sqrt(root))){
                Point onRestrLine((counter*sqrt(root)/2), p.y());
                double distance = sqrt(squared_distance(p, onRestrLine));
                double pointLength = sqrt(1-pow(distance, 2));

                Point topPoint(onRestrLine.x(), onRestrLine.y() + pointLength);
                Point bottomPoint(onRestrLine.x(), onRestrLine.y() - pointLength);
                Segment seg(topPoint, bottomPoint);
                Segments.push_back(seg);
                //sort(P.begin(), index, [](const Point& pi, const Point& pj) {
                //                                return pi.y() < pj.y();
                //                  });
            }
        }
        for(int i = 0; i < Segments.size(); i++){
            if(Segments[i].min() > Segments[i+1].max()){
                C.push_back(midpoint(Segments[i].min(), Segments[i+1].max()));
            }else{
                C.push_back(midpoint(Segments[i].min(), Segments[i].max()));
                i++;
            }
        }
        constant++;
        counter += 2;
        if(constant*sqrt(root) > P.back().x()){
            sorted = true;
        }

    }
    cout << Segments.size() << endl;
}
