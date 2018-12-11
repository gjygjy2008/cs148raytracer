#include "assignment7/Assignment7.h"
#include "common/core.h"
#include "common/Utility/Texture/TextureLoader.h"
#include "common/Utility/Mesh/Loading/MeshLoader.h"
#include "assimp/material.h"




std::shared_ptr<Camera> Assignment7::CreateCamera() const
{
    const glm::vec2 resolution = GetImageOutputResolution();
    std::shared_ptr<Camera> camera = std::make_shared<PerspectiveCamera>(resolution.x / resolution.y, 35.9f);
    PerspectiveCamera* pcamera = static_cast<PerspectiveCamera*>(camera.get());
    pcamera->SetZNear(1.f);
    pcamera->SetZFar(1000.f);
    //camera->SetPosition(glm::vec3(4.367f,3.275f,4.367f));
    //camera->Rotate(glm::vec3(1.f, 0.f, 0.f), -27.938f * PI /180.f);
    //camera->Rotate(glm::vec3(0.f, 1.f, 0.f), 45.f * PI /180.f);
    //camera->Rotate(glm::vec3(0.f, 0.f, 1.f), 0.f * PI /180.f);
    camera->SetPosition(glm::vec3(17.727f*1.2f,7.247f*1.2f,22.74f*1.2f));
    camera->Rotate(glm::vec3(1.f, 0.f, 0.f), -22.255f * PI /180.f);
    camera->Rotate(glm::vec3(0.f, 1.f, 0.f), 45.93f * PI /180.f);
    camera->Rotate(glm::vec3(0.f, 0.f, 1.f), 0.0f * PI /180.f);
    return camera;
}


// Assignment 7 Part 1 TODO: Change the '1' here.
// 0 -- Naive.
// 1 -- BVH.
// 2 -- Grid.
#define ACCELERATION_TYPE 2

std::shared_ptr<Scene> Assignment7::CreateScene() const
{
    std::shared_ptr<Scene> newScene = std::make_shared<Scene>();

    // Material
    std::shared_ptr<BlinnPhongMaterial> material = std::make_shared<BlinnPhongMaterial>();
    material->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    material->SetSpecular(glm::vec3(0.2f, 0.2f, 0.2f), 80.f);
    material->SetAmbient(glm::vec3(0.f,0.f,0.f));

    // Objects
     std::vector<std::shared_ptr<aiMaterial>> loadedMaterials;
    std::vector<std::shared_ptr<MeshObject>> meshObjects = MeshLoader::LoadMesh("char_female_1027_meya.obj", &loadedMaterials);
    material->SetTexture("diffuseTexture",TextureLoader::LoadTexture("char_female_tex.png"));
    material->SetTexture("specularTexture",TextureLoader::LoadTexture("char_female_tex.png"));
    material->SetReflectivity(0.1);
    material->SetTransmittance(0.1);
     meshObjects[0]->SetMaterial(material);
   /*for (size_t i = 0; i < meshObjects.size(); ++i) {
     std::shared_ptr<Material> materialCopy = material->Clone();
     materialCopy->LoadMaterialFromAssimp(loadedMaterials[0]);
        if (loadedMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString aiDiffusePath;
            loadedMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &aiDiffusePath);
            std::string diffusePath(aiDiffusePath.C_Str());
            material->SetTexture("diffuseTexture", TextureLoader::LoadTexture("char_female_tex.png"));
            meshObjects[i]->SetMaterial(material);
        }
        
               }*/

    // material->SetTexture("char_female_1027_meya.obj",TextureLoader::LoadTexture("char_female_tex.png"));
     
    /*
       for (size_t i = 0; i < meshObjects.size(); ++i) {
        std::shared_ptr<Material> materialCopy = material->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        meshObjects[i]->SetMaterial(material);}*/

        std::shared_ptr<SceneObject> cubeSceneObject = std::make_shared<SceneObject>();
        cubeSceneObject->AddMeshObject(meshObjects);
        cubeSceneObject->AddScale(3.0f);
        cubeSceneObject->Translate(glm::vec3(-3.439f, -0.671f, 8.529f));
        cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), -31.308*PI / 180.f);
        cubeSceneObject->Rotate(glm::vec3(0.f, 1.f, 0.f), 46.814*PI / 180.f);
        cubeSceneObject->Rotate(glm::vec3(0.f, 0.f, 1.f), -11.073*PI / 180.f);

        cubeSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
        cubeSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });

        cubeSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });
        newScene->AddSceneObject(cubeSceneObject);
    

    // Material
    std::shared_ptr<BlinnPhongMaterial> material_b = std::make_shared<BlinnPhongMaterial>();
    //material_b->SetDiffuse(glm::vec3(0.f, 0.f, 0.f));
    //material->SetSpecular(glm::vec3(0.f, 0.f, 0.f), 80.f);
   
    material_b->SetAmbient(glm::vec3(0.2f,0.2f,0.2f));
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials_b;
 
    std::vector<std::shared_ptr<MeshObject>> meshObjects_b = MeshLoader::LoadMesh("background_1208.obj", &loadedMaterials_b);
    material_b->SetTexture("ambientTexture",TextureLoader::LoadTexture("icesky.jpg"));
    //material_b->SetTexture("specularTexture",TextureLoader::LoadTexture("icesky.jpg"));
    material_b->SetReflectivity(0);
    material_b->SetTransmittance(0);
    meshObjects_b[0]->SetMaterial(material_b);
    
    std::shared_ptr<SceneObject> aSceneObject = std::make_shared<SceneObject>();
    aSceneObject->AddMeshObject(meshObjects_b);
    //aSceneObject->AddScale(2.f);
    //aSceneObject->Translate(glm::vec3(3.738f, -1.815f, -2.377f));
    //SceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    aSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    aSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    aSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(aSceneObject);
 
    // Material
    std::shared_ptr<BlinnPhongMaterial> material_c = std::make_shared<BlinnPhongMaterial>();
    material_c->SetDiffuse(glm::vec3(1.0f, 0.2f, 1.0f));
    material_c->SetReflectivity(0.2);
    material_c->SetTransmittance(0.1);
    material_c->SetSpecular(glm::vec3(0.1f, 0.1f, 0.08f), 2.5f);
    material_c->SetAmbient(glm::vec3(0.2f,0.2f,0.2f));
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials_c;
    
    std::vector<std::shared_ptr<MeshObject>> meshObjects_c = MeshLoader::LoadMesh("cave_refraction.obj", &loadedMaterials_c);
     for (size_t i = 0; i < meshObjects_c.size(); ++i) {
        std::shared_ptr<Material> materialCopy = material_c->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
         materialCopy->SetReflectivity(0.2);
         materialCopy->SetTransmittance(0.1);
        meshObjects_c[i]->SetMaterial(material_c);}
   // material_c->SetTexture("diffuseTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
   // material_c->SetTexture("specularTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
   // material_c->SetTexture("ambientTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    //material_c->SetReflectivity(0.2);
    //material_c->SetTransmittance(0.1);
    //meshObjects_c[0]->SetMaterial(material_c);
    
    
    std::shared_ptr<SceneObject> bSceneObject = std::make_shared<SceneObject>();
    bSceneObject->AddMeshObject(meshObjects_c);
    //aSceneObject->AddScale(2.f);
    //aSceneObject->Translate(glm::vec3(3.738f, -1.815f, -2.377f));
    //SceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    bSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    bSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    bSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(bSceneObject);
    
    
    // Material
    std::shared_ptr<BlinnPhongMaterial> material_d = std::make_shared<BlinnPhongMaterial>();
    material_d->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
    material_d->SetSpecular(glm::vec3(0.8f, 1.0f, 0.8f), 5.f);
    material_d->SetReflectivity(0.8);
    material_d->SetTransmittance(0.2);
    material_d->SetAmbient(glm::vec3(0.5f,0.5f,0.5f));
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials_d;
    
    std::vector<std::shared_ptr<MeshObject>> meshObjects_d = MeshLoader::LoadMesh("snow_ground.obj", &loadedMaterials_d);
     for (size_t i = 0; i < meshObjects_d.size(); ++i) {
     std::shared_ptr<Material> materialCopy = material_d->Clone();
     materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
         materialCopy->SetReflectivity(0.8);
         materialCopy->SetTransmittance(0.2);
     meshObjects_d[i]->SetMaterial(material_d);}
   // material_d->SetTexture("diffuseTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
   // material_d->SetTexture("specularTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
   // meshObjects_d[0]->SetMaterial(material_c);
    
    std::shared_ptr<SceneObject> cSceneObject = std::make_shared<SceneObject>();
    cSceneObject->AddMeshObject(meshObjects_d);
    //aSceneObject->AddScale(2.f);
    //aSceneObject->Translate(glm::vec3(3.738f, -1.815f, -2.377f));
    //SceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    cSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    cSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    cSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(cSceneObject);

    
    // Material
    std::shared_ptr<BlinnPhongMaterial> material_e = std::make_shared<BlinnPhongMaterial>();
    material_e->SetDiffuse(glm::vec3(1.0f, 0.5f, 0.5f));
    material_e->SetSpecular(glm::vec3(0.8f, 0.1f, 0.8f), 5.f);
    material_e->SetReflectivity(0.1);
    material_e->SetTransmittance(0.1);
    material_e->SetAmbient(glm::vec3(0.1f,0.1f,0.1f));
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials_e;
    
    std::vector<std::shared_ptr<MeshObject>> meshObjects_e = MeshLoader::LoadMesh("waterlily.obj", &loadedMaterials_e);
    for (size_t i = 0; i < meshObjects_e.size(); ++i) {
        std::shared_ptr<Material> materialCopy = material_e->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        materialCopy->SetReflectivity(0.1);
        materialCopy->SetTransmittance(0.1);
        meshObjects_e[i]->SetMaterial(material_e);}
    // material_d->SetTexture("diffuseTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // material_d->SetTexture("specularTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // meshObjects_d[0]->SetMaterial(material_c);
    
    std::shared_ptr<SceneObject> dSceneObject = std::make_shared<SceneObject>();
    dSceneObject->AddMeshObject(meshObjects_e);
    //aSceneObject->AddScale(2.f);
    //aSceneObject->Translate(glm::vec3(3.738f, -1.815f, -2.377f));
    //SceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    dSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    dSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    dSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(dSceneObject);

    
    // Material
    std::shared_ptr<BlinnPhongMaterial> material_f = std::make_shared<BlinnPhongMaterial>();
    material_f->SetDiffuse(glm::vec3(1.0f, 0.5f, 0.5f));
    material_f->SetSpecular(glm::vec3(0.8f, 0.0f, 0.8f), 5.f);
    material_f->SetReflectivity(0.15);
    material_f->SetTransmittance(0.15);
    material_f->SetAmbient(glm::vec3(0.1f,0.1f,0.1f));
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials_f;
    
    std::vector<std::shared_ptr<MeshObject>> meshObjects_f = MeshLoader::LoadMesh("waterlily1.obj", &loadedMaterials_f);
    for (size_t i = 0; i < meshObjects_f.size(); ++i) {
        std::shared_ptr<Material> materialCopy = material_f->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        materialCopy->SetReflectivity(0.15);
        materialCopy->SetTransmittance(0.15);
        meshObjects_f[i]->SetMaterial(material_f);}
    // material_d->SetTexture("diffuseTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // material_d->SetTexture("specularTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // meshObjects_d[0]->SetMaterial(material_c);
    
    std::shared_ptr<SceneObject> eSceneObject = std::make_shared<SceneObject>();
    eSceneObject->AddMeshObject(meshObjects_f);
    //aSceneObject->AddScale(2.f);
    //aSceneObject->Translate(glm::vec3(3.738f, -1.815f, -2.377f));
    //SceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    eSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    eSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    eSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(eSceneObject);
    
    
    // Material
    std::shared_ptr<BlinnPhongMaterial> material_g = std::make_shared<BlinnPhongMaterial>();
    material_g->SetDiffuse(glm::vec3(0.8f, 0.5f, 0.5f));
    material_g->SetSpecular(glm::vec3(0.4f, 0.1f, 0.8f), 2.f);
    material_g->SetReflectivity(0.1);
    material_g->SetTransmittance(0.1);
    material_g->SetAmbient(glm::vec3(0.1f,0.1f,0.1f));
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials_g;
    
    std::vector<std::shared_ptr<MeshObject>> meshObjects_g = MeshLoader::LoadMesh("waterlily2.obj", &loadedMaterials_g);
    for (size_t i = 0; i < meshObjects_g.size(); ++i) {
        std::shared_ptr<Material> materialCopy = material_g->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        materialCopy->SetReflectivity(0.1);
        materialCopy->SetTransmittance(0.1);
        meshObjects_g[i]->SetMaterial(material_g);}
    // material_d->SetTexture("diffuseTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // material_d->SetTexture("specularTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // meshObjects_d[0]->SetMaterial(material_c);
    
    std::shared_ptr<SceneObject> fSceneObject = std::make_shared<SceneObject>();
    fSceneObject->AddMeshObject(meshObjects_g);
    //aSceneObject->AddScale(2.f);
    //aSceneObject->Translate(glm::vec3(3.738f, -1.815f, -2.377f));
    //SceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    fSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    fSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    fSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(fSceneObject);

    
    // Material
    std::shared_ptr<BlinnPhongMaterial> material_h = std::make_shared<BlinnPhongMaterial>();
    material_h->SetDiffuse(glm::vec3(1.0f, 0.2f, 1.0f));
    material_h->SetReflectivity(0.1);
    material_h->SetTransmittance(0.01);
    material_h->SetSpecular(glm::vec3(0.1f, 0.1f, 0.08f), 2.5f);
    material_h->SetAmbient(glm::vec3(0.2f,0.2f,0.2f));
    
    // Objects
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials_h;
    
    std::vector<std::shared_ptr<MeshObject>> meshObjects_h = MeshLoader::LoadMesh("cave_1208.obj", &loadedMaterials_h);
    for (size_t i = 0; i < meshObjects_h.size(); ++i) {
        std::shared_ptr<Material> materialCopy = material_h->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        materialCopy->SetReflectivity(0.1);
        materialCopy->SetTransmittance(0.01);
        meshObjects_h[i]->SetMaterial(material_h);}
    // material_c->SetTexture("diffuseTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // material_c->SetTexture("specularTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    // material_c->SetTexture("ambientTexture",TextureLoader::LoadTexture("textures_iceground1.jpg"));
    //material_c->SetReflectivity(0.2);
    //material_c->SetTransmittance(0.1);
    //meshObjects_c[0]->SetMaterial(material_c);
    
    
    std::shared_ptr<SceneObject> gSceneObject = std::make_shared<SceneObject>();
    gSceneObject->AddMeshObject(meshObjects_h);
    //aSceneObject->AddScale(2.f);
    //aSceneObject->Translate(glm::vec3(3.738f, -1.815f, -2.377f));
    //SceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    gSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    gSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    gSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(gSceneObject);
    // Lights
  //  std::shared_ptr<Light> pointLight = std::make_shared<PointLight>();
  //  pointLight->SetPosition (glm::vec3(-2.654f, -7.168f, 6.966f));
  // pointLight->SetLightColor(glm::vec3(1.f, 1.f, 1.f));
    
    
  std::shared_ptr<AreaLight> areaLight = std::make_shared<AreaLight>(glm::vec2(25.f, 25.f));
   areaLight->SetSamplerAttributes(glm::vec3(4.f, 4.f, 1.f), 10);
   areaLight->SetPosition(glm::vec3(9.310f, 8.793f, 14.331f));
   areaLight->Rotate(glm::vec3(1.f, 0.f, 0.f), -83.134f*PI / 180.f);
   areaLight->Rotate(glm::vec3(0.f, 1.f, 0.f), 20.742f*PI / 180.f);
   areaLight->Rotate(glm::vec3(0.f, 0.f, 1.f), 29.101f*PI / 180.f);
   areaLight->SetLightColor(glm::vec3(2.f, 2.f, 2.f));
    //newScene->AddLight(pointLight);
    
   // std::shared_ptr<Light> directLight = std::make_shared<DirectionalLight>();
   // directLight->SetPosition(glm::vec3(-8.974f, -7.596f, 14.671f));
   // directLight->SetLightColor(glm::vec3(1.f, 1.f, 1.f));

#if ACCELERATION_TYPE == 0
    newScene->GenerateAccelerationData(AccelerationTypes::NONE);
#elif ACCELERATION_TYPE == 1
    newScene->GenerateAccelerationData(AccelerationTypes::BVH);
#else
    UniformGridAcceleration* accelerator = dynamic_cast<UniformGridAcceleration*>(newScene->GenerateAccelerationData(AccelerationTypes::UNIFORM_GRID));
    assert(accelerator);
    // Assignment 7 Part 2 TODO: Change the glm::ivec3(10, 10, 10) here.
    accelerator->SetSuggestedGridSize(glm::ivec3(5, 5, 5));
#endif    
    // newScene->AddLight(pointLight);
   // newScene->AddLight(directLight);
    newScene->AddLight(areaLight);
    
    std::shared_ptr<Light> pointLight1 = std::make_shared<PointLight>();
    pointLight1->SetPosition (glm::vec3(-4.152f, -11.956f, 11.323f));
    pointLight1->SetLightColor(glm::vec3(0.5f, 0.f, 0.f));
    newScene->AddLight(pointLight1);
    
    return newScene;

}
std::shared_ptr<ColorSampler> Assignment7::CreateSampler() const
{    /*
    std::shared_ptr<JitterColorSampler> jitter = std::make_shared<JitterColorSampler>();
    jitter->SetGridSize(glm::ivec3(100, 100, 1));
    //jitter->SetGridSize(glm::ivec3(100, 100, 100));
    return jitter;*/
    std::shared_ptr<JitterColorSampler> jitter = std::make_shared<JitterColorSampler>();
    // ASSIGNMENT 6 TODO: Change the grid size to be glm::ivec3(X, Y, 1).
    jitter->SetGridSize(glm::ivec3(100, 100, 1));
    
    std::shared_ptr<SimpleAdaptiveSampler> sampler = std::make_shared<SimpleAdaptiveSampler>();
    sampler->SetInternalSampler(jitter);
    
    // ASSIGNMENT 6 TODO: Change the '1.f' in '1.f * SMALL_EPSILON' here to be higher and see what your results are. (Part 3)
    sampler->SetEarlyExitParameters(1.f * SMALL_EPSILON, 16);
    
    // ASSIGNMENT 6 TODO: Comment out 'return jitter;' to use the adaptive sampler. (Part 2)
    //return jitter;
    return sampler;
}

std::shared_ptr<class Renderer> Assignment7::CreateRenderer(std::shared_ptr<Scene> scene, std::shared_ptr<ColorSampler> sampler) const
{
    return std::make_shared<BackwardRenderer>(scene, sampler);
}

int Assignment7::GetSamplesPerPixel() const
{
    return 32;
    //return 1;
}

bool Assignment7::NotifyNewPixelSample(glm::vec3 inputSampleColor, int sampleIndex)
{
    return true;
}

int Assignment7::GetMaxReflectionBounces() const
{
    return 3;
}

int Assignment7::GetMaxRefractionBounces() const
{
    return 4;
}

glm::vec2 Assignment7::GetImageOutputResolution() const
{
    return glm::vec2(1280.f, 720.f);
    //return glm::vec2(1960.f, 1280.f);
}
