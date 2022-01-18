/*
 *   Camera class declaration.
 *
 *   Created by Jeff Colgan, October 25, 2021,
 *   CSCI-4229 Computer Graphics : Final Project.
 *
 *   This class controls all of the parameters for the player
 *   camera.  Only one such object should ever be instantiated
 *   in one application, otherwise undefined behavior will result. 
 */

#pragma once

#include "NPCAI.h"

#define MOVE_DISTANCE 0.1
#define VECTOR_SIZE 3

class Camera
{
   // Member variables for eye position, center position, up vector, focal length and field of view.
   private:
      int theta;
      float EyePos[VECTOR_SIZE];
      float CenterPos[VECTOR_SIZE];
      float UpPos[VECTOR_SIZE];
      double dim;
      double asp;
      bool lightOn;

   public:
      /*
       *   Function prototype for Camera class default constructor.
       *   Precondition:  None.
       *   Postcondition: A Camera object has been instantiated in the default position,
       *                  looking at the default point and with the default up direction.  
       */
      Camera();

      /*
       *   Function prototype for Camera class MoveForward function.
       *   Precondition:  An instance of a Camera object has been instantiated, and the Camera object
       *                  needs to move forward.
       *   Postcondition: The camera has been moved forward in the world by a factor of MOVE_DISTANCE.  
       */
      void MoveForward();

      /*
       *   Function prototype for Camera class MoveBackward function.
       *   Precondition:  An instance of a Camera object has been instantiated, and the Camera object
       *                  needs to move backward.  
       *   Postcondition: The Camera has been moved backward in the world by a factor of MOVE_DISTANCE.
       */
      void MoveBackward();

      /*
       *   Function prototype for Camera class StrafeLeft function.
       *   Precondition:  An instance of a Camera object has been instantiated, and the Camera object needs
       *                  to move to the left.
       *   Postcondition: The Camera has been moved left of its previous location.  
       */
      void StrafeLeft();

      /*
       *   Function prototype for Camera class StrafeRight function.
       *   Precondition:  An instance of a Camera object has been instantiated, and the Camera object needs to
       *                  move to the right.
       *   Postcondition: The Camera has been moved right of its previous location.  
       */
      void StrafeRight();

      /*
       *   Function prototype for Camera class Turn function.
       *   Precondition:  An instance of a camera object has been instantiated, and the Camera object
       *                  needs to turn.
       *   Postcondition: The Camera object has been turned.  
       */
      void Turn();

      /*
       *   Function prototype for Camera class shineLight function.
       *   Precondition:  A Camera object has been instantiated, and the user has activated their flashlight.
       *   Postcondition: The spotlight associated with this camera is activated.  
       */
      void shineLight();

      /*
       *   Function prototype for Camera class toggleLight function.
       *   Precondition:  A Camera object has been instantiated, and the user has pressed the flashlight key.
       *   Postcondition: The flashlight component has been toggled on or off.  
       */
      void toggleLight();

      /*
       *   Function prototype for Camera class Project function. 
       */
      void Project(float fov);

      /*
       *   Function prototype for Camera class setEyePos setter function.
       *   Precondition:  None.
       *   Postcondition: The Eye position vector has been changed to the specified (x, y, z) values. 
       *   Parameters:    (x, y, z)-coordinates for the new Eye position vector. 
       */
      void setEyePos(double x, double y, double z);

      /*
       *   Function prototype for Camera class setCenterPos setter function.
       *   Precondition:  None.
       *   Postcondition: The Center position vector has been changed to the specified (x, y, z) values. 
       *   Parameters:    (x, y, z)-coordinates for the new Center position vector.
       */
      void setCenterPos(double x, double y, double z);

      /*
       *   Function prototype for Camera class setUpPos setter function.
       *   Precondition:  The vector is for use in gluLookAt function, so the three values must add up to 1.0,
       *                  otherwise undefined behavior will result.
       *   Postcondition: The up vector has been changed to the specified (x, y, z) values.  
       *   Parameters:    (x, y, z)-coordinates for the new Up vector. 
       */
      void setUpPos(double x, double y, double z);

      /*
       *   Function prototype for Camera class setDim setter function.
       *   Precondition:  None.
       *   Postcondition: The viewing volume has been changed to the specified value.
       *   Parameters:    The new viewing volume dimension.  
       */
      void setDim(double dim);

      /*
       *   Function prototype for Camera class setAsp setter function.
       *   Precondition:  None.
       *   Postcondition: The aspect ratio has been changed to the specified value.
       *   Parameters:    The new aspect ratio.  
       */
      void setAsp(double asp);

      /*
       *  Function prototype for Camera class setTheta setter function.
       *  Precondition:  None.
       *  Postcondition: The Camera objects angle (about the y-axis) has been changed to the specified value.
       *  Parameters:    The new theta value.  
       */
      void setTheta(int theta);

      /*
       *  Function prototype for Camera class getEyeX getter function.
       *  Precondition:  None.
       *  Postcondition: The Camera objects eye-vector x-value has been returned to the caller.
       *  Return value:  The x-value of the eye position vector.  
       */
      double getEyeX();

      /*
       *  Function prototype for Camera class getEyeY getter function.
       *  Precondition:  None.
       *  Postcondition: The Camera objects eye-vector y-value has been returned to the caller.
       *  Return value:  The y-value of the eye position vector.  
       */
      double getEyeY();

      /*
       *  Function prototype for Camera class getEyeZ getter function.
       *  Precondition:  None.
       *  Postcondition: The Camera objects eye-vector z-value has been returned to the caller.
       *  Return value:  The z-value of the eye position vector.  
       */
      double getEyeZ();

      /*
       *  Function prototype for Camera class getCenterX getter function.
       *  Precondition:  None.
       *  Postcondition: The Camera objects Center-vector x-value has been returned to the caller.
       *  Return value:  The x-value of the center position vector.  
       */
      double getCenterX();

      /*
       *   Function prototype for Camera class getCenterY getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects Center-vector y-value has been returned to the caller.
       *   Return value:  The y-value of the center position vector.  
       */
      double getCenterY();

      /*
       *   Function prototype for Camera class getCenterZ getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects Center-vector z-value has been returned to the caller.
       *   Return value:  The z-value of the center position vector.  
       */
      double getCenterZ();

      /*
       *   Function prototype for Camera class getUpX getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects Up-vector x-value has been returned to the caller.
       *   Return value:  The x-value of the up vector. 
       */
      double getUpX();

      /*
       *   Function prototype for Camera class getUpY getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects Up-vector y-value has been returned to the caller.
       *   Return value:  The y-value of the up vector. 
       */
      double getUpY();

      /*
       *   Function prototype for Camera class getUpZ getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects Up-vector z-value has been returned to the caller.
       *   Return value:  The z-value of the up vector. 
       */
      double getUpZ();

      /*
       *   Function prototype for Camera class getDim getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects viewing volume dimension has been returned to the caller.
       *   Return value:  The viewing volume dimension.  
       */
      double getDim();

      /*
       *   Function prototype for Camera class getAsp getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects aspect ratio has been returned to the caller.
       *   Return value:  The aspect ratio.  
       */
      double getAsp();

      /*
       *   Function prototype for Camera class getTheta getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera objects angle of rotation has been returned to the caller.
       *   Return value:  The angle of rotation (about the y-axis).
       */
      double getTheta();

      /*
       *   Function prototype for Camera class getFlashlight getter function.
       *   Precondition:  None.
       *   Postcondition: The Camera object's flashlight status (on/off) represented as a boolean value has been
       *                  returned to the caller.
       *   Return value:  True if the flashlight is active, false otherwise. 
       */
      bool getFlashlight();
};
