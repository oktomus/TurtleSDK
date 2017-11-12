#include "model.h"
#include <list>


Model::Model(const std::string &path)
{
    loadModel(path);
}

void Model::draw(const Shader & shader) const
{
    for(unsigned int i = 0; i < meshes.size(); ++i)
    {
        meshes.at(i).draw(shader);
    }
}

void Model::loadModel(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        fprintf(stderr, "ERROR::ASSIMP::%s\n", importer.GetErrorString());
        return;
    }

    std::list<aiNode *> processStack;
    processStack.push_back(scene->mRootNode);

    // Recursive check

    while(processStack.size())
    {
        aiNode * node = processStack.front();
        processStack.pop_front();

        // Process current node meshes
        for(unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processAiMesh(mesh, scene));
        }

        // Find childrens and add them to the stack
        for(unsigned int i = 0; i < node->mNumChildren; ++i)
        {
            processStack.push_back(node->mChildren[i]);
        }
    }

}

Mesh Model::processAiMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> points;
    std::vector<GLuint> indices;

    // Vertex process
    points.reserve(mesh->mNumVertices);

    for (size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex point;
        // Position
        point.Position.x = mesh->mVertices[i].x;
        point.Position.y = mesh->mVertices[i].y;
        point.Position.z = mesh->mVertices[i].z;

        points.push_back(point);
    }

    // indices process
    indices.reserve(mesh->mNumFaces); // Not really usefull

    for (size_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace & face = mesh->mFaces[i];
        for(size_t j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(points, indices, {});
}
