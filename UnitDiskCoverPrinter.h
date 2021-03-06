#ifndef UNITDISKCOVERPRINTER_H
#define UNITDISKCOVERPRINTER_H

#include <vector>

#include <Centers.h>

//using namespace std;

class UnitDiskCoverPrinter
{
    private:
        vector<Point> pointSet, centersOfPlacedDisks;
        double r = 0.0;
        string fileName;

    public:
        UnitDiskCoverPrinter(vector<Point> &P, vector<Point> &centersOfPlacedDisks, double radiusOfDisks, string outputFileName);
        void displayPDF();
};

#endif
