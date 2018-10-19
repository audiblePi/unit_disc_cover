#include <UnitDiskCoverPrinter.h>
#include <iostream>

using namespace std;

UnitDiskCoverPrinter::UnitDiskCoverPrinter(vector<Point> &P, vector<Point> &centersOfPlacedDisks, double radiusOfDisks, string outputFileName) {
    pointSet = P;
    this->centersOfPlacedDisks = centersOfPlacedDisks;
    r = radiusOfDisks;
    fileName = outputFileName;
}

double const radiusOfPoints = 0.05;

void UnitDiskCoverPrinter::displayPDF() {
    string fName = fileName + ".tex";
    FILE *fp = fopen(fName.c_str() ,"w");
    fprintf(fp,"\\documentclass{standalone} \n\\usepackage{tikz} \n \n\n\\begin{document}\n");
    fprintf(fp,"\n\n\n\\begin{tikzpicture}\n\n");

    for(Point p : pointSet)
        fprintf(fp,"\\draw [fill=red,stroke=red] (%f,%f) circle [radius=%f];\n",p.x(),p.y(),radiusOfPoints);

     for(Point p : centersOfPlacedDisks)
        fprintf(fp,"\\draw (%f,%f) circle [radius=1];\n",p.x(),p.y());

    fprintf(fp,"\n\n\\end{tikzpicture}");
    fprintf(fp,"\n\n\\end{document}");
    fclose(fp);

    cout << "\nOutput PDF generation started...\n";
    string command = "pdflatex " + fName + " > /dev/null";
    system(command.c_str());
    cout << "PDF generation terminated...\n";

    command = "atril " + fileName + ".pdf &";
    system(command.c_str());
}
