

//materialbase.hpp
#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include "../qbTextures/texturebase.hpp"
#include "../qbPrimatives/objectbase.hpp"
#include "../qbLights/lightbase.hpp"
#include "../../qbLinAlg/qbVector.h"
#include "../ray.hpp"

namespace qbRT
{
    class MaterialBase
    {
        public:
           MaterialBase();
           virtual ~MaterialBase();

           // Function to terurn the color of the material
           virtual qbVector<double> ComputeColor ( const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                   const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                   const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                   const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                   const qbRT::Ray &cameraRay);

        // Function to compute diffuse color.
        static qbVector<double> ComputeDiffuseColor( const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                     const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                     const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                     const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                     const qbVector<double> &baseColor);

        // Function to compute the reflection color.
        qbVector<double> ComputeReflectionColor(   const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                                                   const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
                                                   const std::shared_ptr<qbRT::ObjectBase> &currentObject,
                                                   const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                   const qbRT::Ray &incidentRay);

        // Function to cast a ray into the scene.
        bool CastRay( const qbRT::Ray &castray, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
                      const std::shared_ptr<qbRT::ObjectBase> &thisObject,
                      std::shared_ptr<qbRT::ObjectBase> &closestObject,
                      qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
                      qbVector<double> &closestLocalColor);

      // Function to assign the texture
      void AssignTexture(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture);

      public:
        // Counter for the number of reflection rays.
        inline static int m_maxReflectionRays;
        inline static int m_reflectionRayCount;

      // List of texture assigned to this material.
      std::vector<std::shared_ptr<qbRT::Texture::TextureBase>> m_textureList;

      // Flag to indicate whether at latest one texture has been assigned.
      bool m_hasTexture = false;

      private:
    };
}


#endif
