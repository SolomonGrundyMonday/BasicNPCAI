#include "Camera.h"

// Function definition for Camera class constructor.
Camera::Camera()
{
   // Default starting coordinates are (-25, 1.5, -25).
   this->EyePos[0] = -10.0;
   this->EyePos[1] = 1.0;
   this->EyePos[2] = -10.0;

   // Default look at point coordinates are (0, 0.5, 0).
   this->CenterPos[0] = 0.0;
   this->CenterPos[1] = 0.5;
   this->CenterPos[2] = 0.0;

   // Default up vector is (0, 1, 0).
   this->UpPos[0] = 0.0;
   this->UpPos[1] = 1.0;
   this->UpPos[2] = 0.0;

   // Default values for focal length, aspect ratio, field of view.
   this->dim = 6.0;
   this->asp = 1.0;
   this->theta = 0;

   this->lightOn = false;
}

// Function definition for MoveForward method of Camera class.
void Camera::MoveForward()
{
   // Compute new x, z coordinates for forward movement. 
   float x = this->EyePos[0] + (Sin(this->theta) * MOVE_DISTANCE);
   float z = this->EyePos[2] + (-Cos(this->theta) * MOVE_DISTANCE);

   this->setEyePos(x, this->EyePos[1], z);
}

// Function definition for MoveBackward method of Camera class.
void Camera::MoveBackward()
{
   // Compute new x, z coordinates for backward movement.
   float x = this->EyePos[0] - (Sin(this->theta) * MOVE_DISTANCE);
   float z = this->EyePos[2] - (-Cos(this->theta) * MOVE_DISTANCE);

   this->setEyePos(x, this->EyePos[1], z);
}

// Function definition for StrafeLeft method of Camera class.
void Camera::StrafeLeft()
{
   // Compute new x, z coordinates for left strafing.
   float x = this->EyePos[0] - (Cos(this->theta) * MOVE_DISTANCE);
   float z = this->EyePos[2] - (Sin(this->theta) * MOVE_DISTANCE);

   this->setEyePos(x, this->EyePos[1], z);
}

// Function definition for StrafeRight method of Camera class.
void Camera::StrafeRight()
{
   // Compute new x, z coordinates for right strafing.
   float x = this->EyePos[0] + (Cos(this->theta) * MOVE_DISTANCE);
   float z = this->EyePos[2] + (Sin(this->theta) * MOVE_DISTANCE);

   this->setEyePos(x, this->EyePos[1], z);
}

// Function definition for Turn method of Camera class.
void Camera::Turn()
{
   float x = 2 * this->dim * Sin(this->theta);
   float z = -2 * this->dim * Cos(this->theta);

   this->setCenterPos(x, this->CenterPos[1], z);
}

// Function definition for shineLight method of Camera class.
void Camera::shineLight()
{
   // If light is active.
   if (this->lightOn)
   {
      // Set up the light properties.
      float Ambient[] = { 0.0, 0.0, 0.0, 1.0 };
      float Diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
      float Specular[] = { 1.0, 1.0, 1.0, 1.0 };
      float spotPosition[] = {this->EyePos[0], this->EyePos[1], this->EyePos[2], 1.0 };
      float exponent[] = { 128.0 };
      float cutoff[] = { 45.0 };

      // Enable a spotlight located at the Camera eye position.
      glEnable(GL_LIGHT1);
      glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
      glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
      glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);
      glLightfv(GL_LIGHT1, GL_POSITION, spotPosition);
      glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);
      glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
   }
   // If light is not active.
   else
      glDisable(GL_LIGHT1);
}

// Function definition for toggleLight method of Camera class.
void Camera::toggleLight()
{
   // Toggle light between active/deactive.
   if (lightOn)
      this->lightOn = false;
   else
      this->lightOn = true;
}

// Function definition for Project method of Camera class.
void Camera::Project(float fov)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if (fov)
      gluPerspective(fov, this->asp, this->dim/16, 16*this->dim);
   else
      glOrtho(-this->asp * this->dim, this->asp * this->dim, -this->dim, this->dim, -this->dim, this->dim);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Function definition for setEyePos method of Camera class.
void Camera::setEyePos(double x, double y, double z)
{
   // Set Camera eye position vector.
   this->EyePos[0] = x;
   this->EyePos[1] = y;
   this->EyePos[2] = z;
}

// Function definition for setCenterPos method of Camera class.
void Camera::setCenterPos(double x, double y, double z)
{
   // Set Camera center position vector.
   this->CenterPos[0] = x;
   this->CenterPos[1] = y;
   this->CenterPos[2] = z;
}

// Function definition for setUpPos method of Camera class.
void Camera::setUpPos(double x, double y, double z)
{
   // Set Camera up vector.
   this->UpPos[0] = x;
   this->UpPos[1] = y;
   this->UpPos[2] = z;
}

// Function definition for setDim setter method of Camera class.
void Camera::setDim(double dim)
{
   this->dim = dim;
}

// Function definition for setAsp setter method of Camera class.
void Camera::setAsp(double asp)
{
   this->asp = asp;
}

// Function definition for setTheta setter method of Camera class.
void Camera::setTheta(int theta)
{
   this->theta = theta;
}

// Function definition for getEyeX getter method of Camera class.
double Camera::getEyeX()
{
   return this->EyePos[0];
}

// Function definition for getEyeY getter method of Camera class.
double Camera::getEyeY()
{
   return this->EyePos[1];
}

// Function definition for getEyeZ getter method of Camera class.
double Camera::getEyeZ()
{
   return this->EyePos[2];
}

// Function definition for getCenterX getter method of Camera class.
double Camera::getCenterX()
{
   return this->CenterPos[0];
}

// Function definition for getCenterY getter method of Camera class.
double Camera::getCenterY()
{
   return this->CenterPos[1];
}

// Function definition for getCenterZ getter method of Camera class.
double Camera::getCenterZ()
{
   return this->CenterPos[2];
}

// Function definition for getUpX getter method of Camera class.
double Camera::getUpX()
{
   return this->UpPos[0];
}

// Function definition for getUpY getter method of Camera class.
double Camera::getUpY()
{
   return this->UpPos[1];
}

// Function definition for getUpZ getter method of Camera class.
double Camera::getUpZ()
{
   return this->UpPos[2];
}

// Function definition for getDimn getter method of Camera class.
double Camera::getDim()
{
   return this->dim;
}

// Function definition for getAsp getter method of Camera class.
double Camera::getAsp()
{
   return this->asp;
}

// Function definition for getTheta getter method of camera class.
double Camera::getTheta()
{
   return this->theta;
}

// Function definition for getFlashlight getter method of Camera class.
bool Camera::getFlashlight()
{
   return this->lightOn;
}