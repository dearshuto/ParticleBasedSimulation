//
//  mesh.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/10/13.
//
//

#ifndef mesh_hpp
#define mesh_hpp

#include <memory>
#include <string>
#include <vector>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <ConvexDecomposition/cd_wavefront.h>
#include "particle_based_simulation/simulation/collision_object/collision_object.hpp"

namespace fj {
    class Mesh;
}

/** 三角メッシュのみで構成されるWavefront OBJ形式のみをサポート */
class fj::Mesh : public fj::CollisionObject
{
    typedef fj::CollisionObject Super;
public:
    Mesh() = delete;
    ~Mesh() = default;
    
    /**
     * @param filename .objのファイル 
     * @param mass 質量
     * @param motionState
     * @param localInertia 回転のしにくさ*/
    Mesh(const btScalar mass, std::unique_ptr<btMotionState> motionState, const btVector3& localInertia = btVector3(0, 0, 0))
    : Super(mass, std::move(motionState), nullptr/*collisionShape*/, localInertia)
    {
        
    }
    
    /** ファイルシステムから Wavefront OBJ 形式のファイルを読み込む
     * @return メッシュの読み込みが成功したかどうか */
    bool loadFromFile(const std::string& filename);

    void reconstructWithRawData(const std::vector<btVector3>& vertices, const std::vector<uint32_t>& indices);
    
protected:
    void updateMeshShape(std::unique_ptr<btTriangleIndexVertexArray> meshData);
private:
    ConvexDecomposition::WavefrontObj m_obj;
    std::unique_ptr<btTriangleIndexVertexArray> m_vertexArray;
};

#endif /* mesh_hpp */
