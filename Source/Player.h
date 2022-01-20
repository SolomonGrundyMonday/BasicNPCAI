/*
 *   Class declaration for Player class.
 *   Created by Jeff Colgan, January 13, 2022. 
 */

#pragma once

#include "GameObject.h"

class Player : public GameObject
{
   // Private member variables for translation, scale and rotation.
   private:
      unsigned char texture;

   public:
      /*
       *   Function prototype for Player class default constructor. 
       */
      Player();

      /*
       *   Function prototype for Player class constructor. 
       */
      Player(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for Player class Initialize function implementation. 
       */
      int Initialize(const char* filename);

      /*
       *   Function prototype for Player class Render function implementation. 
       */
      void Render();

      /*
       *   Function prototype for Player class detectCollision funciton implementation. 
       */
      void resolveCollision(Camera* camera);
};