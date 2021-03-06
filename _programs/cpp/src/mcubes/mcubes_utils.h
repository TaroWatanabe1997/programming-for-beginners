#pragma once

#include "common/vec3.h"

typedef Vec3 XYZ;

struct TRIANGLE {
    XYZ p[3];
};

struct GRIDCELL {
    XYZ p[8];
    double val[8] = {0};
};

struct TETRAHEDRON {
    XYZ p[4];
    double val[4] = {0};
};

/*
 * Linearly interpolate the position where an isosurface cuts
 * an edge between two vertices, each with their own scalar value
 */
XYZ VertexInterp(double isolevel, XYZ p1, XYZ p2, double valp1, double valp2);

/*
 * Given a grid cell and an isolevel, calculate the triangular
 * facets required to represent the isosurface through the cell.
 * Return the number of triangular facets, the array "triangles"
 * will be loaded up with the vertices at most 5 triangular facets.
 * 0 will be returned if the grid cell is either totally above
 * of totally below the isolevel.
 */
int Polygonise(GRIDCELL grid, double isolevel, TRIANGLE *triangles);

int PolygonizeTet(TETRAHEDRON tet, double isolevel, TRIANGLE *triangles);
