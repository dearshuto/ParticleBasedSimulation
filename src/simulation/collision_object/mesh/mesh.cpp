//
//  mesh.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/10/13.
//
//

#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <ConvexDecomposition/cd_wavefront.h>
#include "particle_based_simulation/simulation/collision_object/mesh/mesh.hpp"

bool fj::Mesh::Iterator::hasNext()const
{
    return false;
}

std::array<btVector3, 3> fj::Mesh::Iterator::next()
{
    std::array<btVector3, 3> mesh;
    return mesh;
}

bool fj::Mesh::loadFromFile(const std::string &filename)
{
    // 読み込んだメッシュの数が返ってくる. 何も読み込めなかったらエラー
    if ( !m_obj.loadObj(filename.c_str()) )
    {
        return false;
    }
    
    std::unique_ptr<btTriangleIndexVertexArray> vertexArray(new btTriangleIndexVertexArray(
                                                                                   m_obj.mTriCount,
                                                                                   m_obj.mIndices,
                                                                                   3*sizeof(int), //Indices Stride
                                                                                   m_obj.mVertexCount,
                                                                                   m_obj.mVertices,
                                                                                   3*sizeof(float) // Vertices Stride
                                                                                   ));
    updateMeshShape(std::move(vertexArray));
    return true;
}

void fj::Mesh::reconstructWithRawData(const std::vector<btVector3> &vertices, const std::vector<uint32_t> &indices)
{
    // 頂点とインデックスがわかっているので、 btTriangleMesh にデータを渡すだけでOK
    std::unique_ptr<btTriangleMesh> mesh(new btTriangleMesh());
    
    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        mesh->addTriangle(vertices[i], vertices[i+1], vertices[i+2]);
    }
    
    for (const auto& kIndex : indices)
    {
        mesh->addIndex(kIndex);
    }
    
    // 頂点情報でメッシュを再構成
    updateMeshShape(std::move(mesh));
}

void fj::Mesh::updateMeshShape(std::unique_ptr<btTriangleIndexVertexArray> meshData)
{
    // btCollisionShape の再構築と再登録
    btGImpactMeshShape* meshShape = new btGImpactMeshShape(meshData.get());
    meshShape->updateBound();
    std::unique_ptr<btCollisionShape> collisionShape(meshShape);
    setCollisionShape(std::move(collisionShape));
    
    // 頂点情報も取っておく
    m_vertexArray = std::move(meshData);
}
