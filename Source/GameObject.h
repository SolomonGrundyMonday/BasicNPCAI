/*
 *   GameObject abstract superclass declaration.
 *   
 *   Updated by Jeff Colgan, January 19, 2022,
 *   CSCI-4229 Computer Graphics: Final Project.
 *
 *   This is the abstract superclass for all rendered GameObjects
 *   All rendered 3D objects should inherit from this class. 
 */
#pragma once
#include "Camera.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

// Enum for the walls of a GameObject's hit boxe.
enum wall {
   FRONT,
   FRONT_RIGHT,
   FRONT_LEFT,
   LEFT,
   RIGHT,
   BACK,
   NONE
};

class GameObject
{

   private:
      float posX;
      float posY;
      float posZ;
      float scaleX;
      float scaleY;
      float scaleZ;
      float rotX;
      float rotY;
      float rotZ;

      /*
       *   Function prototype for GameObject class Reverse helper function. 
       */
      static void Reverse(void* x, const int n);

   public:

      /*
       *   Function prototype for GameObject default constructor.
       */
      GameObject();

      /*
       *   Function prototype for GameObject constructor. 
       */
      GameObject(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz);

      /*
       *   Function prototype for pure virtual Initialize function.  
       *   All subclasses of GameObject must implement this function.
       */
      static int Initialize(const char* filename);

      /*
       *    Function prototype for pure virtual Render function.
       *    All subclasses of GameObject must implement this function. 
       */
      virtual void Render() = 0;

      /*
       *    Function prototype for pure virtual resolveCollision function.
       *    All subclasses of Gameobject must implement this function. 
       */
      virtual void resolveCollision(Camera* camera) = 0;

      /*
       *    Function prototype for GameObject setPosition function. 
       */
      void setPosition(float x, float y, float z);

      /*
       *    Function prototype for GameObject setScaling function. 
       */
      void setScaling(float dx, float dy, float dz);

      /*
       *    Function prototype for GameObject setRotation function. 
       */
      void setRotation(float rx, float ry, float rz);

      /*
       *    Function prototype for GameObject getPosX function. 
       */
      float getPosX();

      /*
       *    Function prototype for GameObject getPosY function. 
       */
      float getPosY();

      /*
       *    Function prototype for GameObject getPosZ function. 
       */
      float getPosZ();

      /*
       *    Function prototype for GameObject getScaleX function.  
       */
      float getScaleX();

      /*
       *    Function prototype for GameObject getScaleY function. 
       */
      float getScaleY();

      /*
       *    Function prototype for GameObject getScaleZ function. 
       */
      float getScaleZ();

      /*
       *    Function prototype for GameObject getRotX function. 
       */
      float getRotX();

      /*
       *    Function prototype for GameObject getRotY function.   
       */
      float getRotY();

      /*
       *    Function prototype for GameObject getRotZ function. 
       */
      float getRotZ();
};
