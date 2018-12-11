#include "common/Scene/Lights/Point/PointLight.h"


void PointLight::ComputeSampleRays(std::vector<Ray>& output, glm::vec3 origin, glm::vec3 normal) const
{
    origin += normal * LARGE_EPSILON;
    const glm::vec3 lightPosition = glm::vec3(GetPosition());
    const glm::vec3 rayDirection = glm::normalize(lightPosition - origin);
    const float distanceToOrigin = glm::distance(origin, lightPosition);
    output.emplace_back(origin, rayDirection, distanceToOrigin);
}

float PointLight::ComputeLightAttenuation(glm::vec3 origin) const
{
    return 1.f;
}

void PointLight::GenerateRandomPhotonRay(Ray& ray) const
{
    const glm::vec3 lightPosition = glm::vec3(GetPosition());
    ray.SetPosition(lightPosition);
    float x;
    float y;
    float z;
    do {
          //x= (rand()*2.0/RAND_MAX-1.0);
          //y= (rand()*2.0/RAND_MAX-1.0);
          //z= (rand()*2.0/RAND_MAX-1.0);
       // x= ((rand()%100))/50.f-1.0;
       // y= ((rand()%100))/50.f-1.0;
       // z= ((rand()%100))/50.f-1.0;
         x= ((rand()%200-100))/100.f;
         y= ((rand()%200-100))/100.f;
         z= ((rand()%200-100))/100.f;
        
    } while((x*x+y*y+z*z)>1.0);
    const glm::vec3 rayDirection=glm::normalize(glm::vec3(x,y,z));
    ray.SetRayDirection(rayDirection);
    // Assignment 8 TODO: Fill in the random point light samples here.
}
