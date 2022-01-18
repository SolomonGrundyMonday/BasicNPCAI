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
       *   Function prototype for Player class Reverse function. 
       */
      void Reverse(void* x, const int n);

      /*
       *   Function prototype for Player class Render function implementation. 
       */
      void Render();

      /*
       *   Function prototype for Player class detectCollision funciton implementation. 
       */
      void resolveCollision(Camera* camera);

      /*
       *   Function prototype for Player class setPosition setter funciton. 
       */
      void setPosition(float x, float y, float z);

      /*
       *   Function prototype for Player class setScale setter function. 
       */
      void setScale(float x, float y, float z);

      /*
       *   Function prototype for Player class setRotation setter function. 
       */
      void setRotation(float x, float y, float z);

      /*
       *   Function prototype for Player class getPosX getter function.  
       */
      float getPosX();

	  /*
       *   Function prototype for Player class getPosY getter function. 
       */
      float getPosY();

      /*
       *   Function prototype for Player class getPosZ getter function. 
       */
      float getPosZ();

      /*
       *   Function prototype for Player class getScaleX getter function. 
       */
      float getScaleX();

      /*
       *   Function prototype for Player class getScaleY getter function. 
       */
      float getScaleY();

      /*
       *   Function prototype for Player class getScaleZ getter function. 
       */
      float getScaleZ();

      /*
       *   Function prototype for Player class getRotX getter function. 
       */
      float getRotX();

      /*
       *   Function prototype for Player class getRotY getter function.  
       */
      float getRotY();

      /*
       *   Function prototype for Player class getRotZ getter function.
       */
      float getRotZ();
};