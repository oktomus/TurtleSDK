#include "terrain.h"

Terrain::Terrain(const Grid & pGrid)
{

    std::vector<Vertex> vertices;
    for(size_t i = 0; i < pGrid.points.size(); ++i)
    {
        Vertex v;
        v.Position.x = pGrid.points[i].x;
        v.Position.y = 0;
        v.Position.z = pGrid.points[i].y;
        vertices.push_back(v);
    }

    meshes.push_back(Mesh(vertices, pGrid.indices, {}));

}
