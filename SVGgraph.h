#ifndef SVGGRAPH_H
#define SVGGRAPH_H
#include "Points.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class SVGGraph{
public:
    SVGGraph();
    SVGGraph(queue<Points*> coordsSet);
    string GetSVGGraph();
private:
};


SVGGraph::SVGGraph():myCoordsSet()
{

}
SVGGraph::SVGGraph( queue<Points *> coordsSet):myCoordsSet(coordsSet)
{

}

string SVGGraph::GetSVGGraph()
{
    ofstream fout;
        fout.open("outFile.svg");
        if (fout.fail())
        {
            cout << "outFile.svg failed to open.";
            exit(1);
        }
        fout << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
        fout << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n";
        fout << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
        fout << "<svg width=\"2000\" height=\"2000\"\n";
        fout << "xmlns=\"http://www.w3.org/2000/svg\">\n\n";
        fout << "<svg width=\"400px\" height=\"400px\" viewBox=\"0 0 400 400\">\n";
        fout << "<!-- axes -->" << endl;
        fout << "<line x1=\"0\" y1=\"400\" x2=\"400\" y2=\"400\" style=\"stroke: black;\"/>\n";
        fout << "<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"400\" style=\"stroke: black;\"/>\n";
        fout << "<polyline points = \"";
        while(!myCoordsSet.empty()){
            Points* temp = coordsSet.front();
            fout << (temp->getX()*20.0) << "," << (400-400-temp->getY()) << " ";
            myCoordsSet.pop();
        }
        fout << "\"\n";
        fout << "style=\"fill:none;stroke:black;stroke-width:3;\"/>\n";
        fout << "</svg>";
        fout.close();
}

#endif // SVGGRAPH_H


