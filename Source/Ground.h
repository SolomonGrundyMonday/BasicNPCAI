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
      unsigned char texture;
      float posX;
      float posY;
      float posZ;
      float scaleX;
      float scaleY;
      float scaleZ;
      float rotX;
      float rotY;
      float rotZ;

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
       *   Function prototype for Initialize function implementation. 
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for Reverse function.  
       */
      void Reverse(void* x, const int n);

      /*
       *   Function prototype for Render function implementation.
       */
      void Render();

      /*
       *   Function prototype for resolvecollision function implementation. 
       */
      void resolveCollision(Camera* camera);

      /*
       *   Function prototype for getPosX getter function.
       */
      float getPosX();

      /*
       *   Function prototype for getPosY getter function. 
       */
      float getPosY();

      /*
       *   Function prototype for getPosZ getter funciton.  
       */
      float getPosZ();

      /*
       *   Function prototype for getScaleX getter function.
       */
      float getScaleX();

      /*
       *   Function prototype for getScaleY getter function. 
       */
      float getScaleY();

      /*
       *   Function prototype for getScaleZ getter function. 
       */
      float getScaleZ();

      /*
       *   Function prototype for getRotX getter function. 
       */
      float getRotX();

      /*
       *   Function prototype for getRotY getter function. 
       */
      float getRotY();

      /*
       *   Function prototype for getRotZ getter function. 
       */
      float getRotZ();
};
