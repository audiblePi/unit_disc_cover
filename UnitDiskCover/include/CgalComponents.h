#ifndef CGALCOMPONENTS_H
#define CGALCOMPONENTS_H

#include <vector>
#include <algorithm>
#include <ctime>
#include <unordered_set>

/**********************CGAL headers files**************************/
#include <CGAL/point_generators_2.h>
#include <CGAL/algorithm.h>
#include <CGAL/random_selection.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
/******************************************************************/

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K>  DelunayTriangulation;
typedef K::Point_2                       Point;
typedef Creator_uniform_2<double,Point>  Creator;
typedef DelunayTriangulation::Vertex_handle Vertex_handle;
typedef Circle_2<K> Circle;
typedef Segment_2<K> Segment;

using namespace std;

#endif

