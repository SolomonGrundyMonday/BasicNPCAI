/*
 *   Ground Class declaration.
 *   Created by Jeff Colgan, January 8, 2022. 
 */

#pragma once

#include "GameObject.h"

class Ground : public GameObject
{
   
   // Private member variables for textures, position, rotation and scaling.
   private:
      unsigned int texture;

    public:

      /*
       *   Function prototype for Ground object default constructor. 
       */
      Ground();

      /*
       *   Function prototype for Ground object constructor. 
       */
      Ground(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for Ground object Initialize function override. 
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for Render function implementation.
       */
      void Render();

      /*
       *   Function prototype for resolvecollision function implementation. 
       */
      void resolveCollision(Camera* camera);

};
