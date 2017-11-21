#include "terrain.h"
#include "PerlinNoise.h"
#include <imgui.h>

Terrain::Terrain(const Grid & pGrid)
{

    width_ = pGrid.size();
    height_ = pGrid.size();
    slicing_ = pGrid.slicing();

    std::vector<Vertex> vertices;
    for(size_t i = 0; i < pGrid.points.size(); ++i)
    {
        Vertex v;
        v.Position.x = pGrid.points[i].x;
        v.Position.y = 0;
        v.Position.z = pGrid.points[i].y;
        vertices.push_back(v);
    }

    Terrain::randomize(vertices, slicing_);

    meshes.push_back(Mesh(vertices, pGrid.indices, {}));

}

void Terrain::randomize()
{
    Terrain::randomize(meshes.at(0).points_, slicing_);
    meshes.at(0).updateDataBuffer();
}

void Terrain::ui()
{
    Model::ui();
    if(ImGui::Button("Randomize height"))
        randomize();
}

void Terrain::randomize(std::vector<Vertex> &pPoints, unsigned int pSlicing)
{
    unsigned int seed = rand() % 6000;
    PerlinNoise pn(seed);

    for(size_t i = 0; i < pPoints.size(); ++i)
    {
        pPoints.at(i).Position.y = -9 + 15 *
                pn.noise(
                    pPoints.at(i).Position.x / 20,
                    pPoints.at(i).Position.z / 20,
                    0.8)
                + pn.noise(
                    pPoints.at(i).Position.x,
                    pPoints.at(i).Position.z,
                    10.4
                    ) * 2;
    }
}
