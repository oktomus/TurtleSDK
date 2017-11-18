#include "model.h"
#include <list>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Model::Model(const std::string &path)
{
    scale_ = {1, 1, 1};
    translate_ = {0, 0, 0};
    rotate_ = {0, 0, 0};

    loadModel(path);
}

void Model::draw(const Shader & shader)
{
    transform_ = glm::mat4();

    // Revert order !
    transform_ = glm::translate(transform_, translate_);
    transform_ = glm::rotate(transform_, glm::radians(rotate_[0]), glm::vec3(1, 0, 0));
    transform_ = glm::rotate(transform_, glm::radians(rotate_[1]), glm::vec3(0, 1, 0));
    transform_ = glm::rotate(transform_, glm::radians(rotate_[2]), glm::vec3(0, 0, 1));
    transform_ = glm::scale(transform_, scale_);

    shader.setMat4("model", transform_);
    for(unsigned int i = 0; i < meshes.size(); ++i)
    {
        meshes.at(i).draw(shader);
    }
}

void Model::ui()
{
    ImGui::SliderFloat3("Model position", glm::value_ptr(translate_), -10.f, 10.f);
    ImGui::SliderFloat3("Model rotation", glm::value_ptr(rotate_), 0.f, 360.f);
    ImGui::SliderFloat3("Model size", glm::value_ptr(scale_), 0.f, 5.f);
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
    directory = path.substr(0, path.find_last_of('/'));

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

        // Normal
        point.Normal.x = mesh->mNormals[i].x;
        point.Normal.y = mesh->mNormals[i].y;
        point.Normal.z = mesh->mNormals[i].z;

        // Tex coords
        if (mesh->mTextureCoords[0])
        {
            point.TexCoords.x = mesh->mTextureCoords[0][i].x;
            point.TexCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            point.TexCoords.x = 0;
            point.TexCoords.y = 0;
        }

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
    std::vector<Texture> textures;

    // materials process
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
                                                           aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTextures(material,
                                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(points, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = textureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        //texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}

GLuint textureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename(path);
    filename = directory + '/' + filename;

    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        fprintf(stderr, "Texture failed to load at path: %s\n", path);
        stbi_image_free(data);
    }

    return textureID;
}
