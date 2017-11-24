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
    Terrain::calculateNormals(vertices, pGrid.indices);

    meshes.push_back(Mesh(vertices, pGrid.indices, {}));

}

void Terrain::draw(const Shader & shader)
{
    glm::mat4 tr;
    shader.setMat4("model", tr);
    Model::draw(shader);
}

void Terrain::randomize()
{
    Terrain::randomize(meshes.at(0).points_, slicing_);
    Terrain::calculateNormals(meshes.at(0).points_, meshes.at(0).indices_);
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
        pPoints.at(i).Position.y = -9 + 25 *
                pn.noise(
                    pPoints.at(i).Position.x / 20,
                    pPoints.at(i).Position.z / 20,
                    0.8)
                + pn.noise(
                    pPoints.at(i).Position.x / 4,
                    pPoints.at(i).Position.z / 4,
                    10.4
                    ) * 0.5;
    }

}

void Terrain::calculateNormals(
        std::vector<Vertex>& pPoints, 
        const std::vector<unsigned int>& pTriangles)
{
    for(Vertex & v : pPoints)
    {
        v.Normal = glm::vec3(0);
    }

    for(size_t i = 0; i < pTriangles.size(); i += 3)
    {
        unsigned int indA = pTriangles.at(i);
        unsigned int indB = pTriangles.at(i + 1);
        unsigned int indC = pTriangles.at(i + 2);

        glm::vec3 normal = 
            glm::cross(
                    pPoints.at(indB).Position - pPoints.at(indA).Position,
                    pPoints.at(indC).Position - pPoints.at(indA).Position
                    );


        pPoints.at(indA).Normal += normal;
        pPoints.at(indB).Normal += normal;
        pPoints.at(indC).Normal += normal;
    }

    for(Vertex & v : pPoints)
    {
        v.Normal = glm::normalize(v.Normal);
    }
}
