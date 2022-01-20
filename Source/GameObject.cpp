/*
 *   GameObject superclass definition.
 *   Created by Jeff Colgan, January 19, 2022.  
 */
#include "GameObject.h"

// Definition for GameObject class default constructor.
GameObject::GameObject()
{
   // Set the default translation coordinates at the origin.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Set the default scaling values at 1.0 on each axis.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Set the default rotation at 0.0 about each axis.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Definition for GameObject class constructor.
GameObject::GameObject(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Set the specified translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Set the specified scaling values.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Set the specified rotation about each axis.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Definition for GameObject class Initialize function.
int GameObject::Initialize(const char* filename)
{
   // Load texture from input filename here.
   unsigned int text;
   unsigned short magic;
   unsigned int x, y, size;
   unsigned short planes, bits;
   unsigned char* image;
   unsigned int off;
   unsigned int k;
   unsigned int max;
   FILE* input;

   input = fopen(filename, "rb");

   if (!input)
   {
      printf("Failed to open texture file!\n");
      return 1;
   }

   if (fread(&magic, 2, 1, input) != 1)
   {
      printf("Failed to read texture file!\n");
      return 1;
   }

   if (magic != 0x4D42 && magic != 0x424D)
   {
      printf("Wrong magic value!\n");
      return 1;
   }

   if (fseek(input, 8, SEEK_CUR) || fread(&off, 4, 1, input) != 1 ||
       fseek(input, 4, SEEK_CUR) || fread(&x, 4, 1, input) != 1 || fread(&y, 4, 1, input) != 1 ||
       fread(&planes, 2, 1, input) != 1 || fread(&bits, 2, 1, input) != 1 || fread(&k, 4, 1, input) != 1)
   {
      printf("Failed to read texture dimensions!\n");
      return 1;
   }

   if (magic == 0x424D)
   {
      Reverse(&off, 4);
      Reverse(&x, 4);
      Reverse(&y, 4);
      Reverse(&planes, 2);
      Reverse(&bits, 2);
      Reverse(&k, 4);
   }

   glGetIntegerv(GL_MAX_TEXTURE_SIZE, (int*)&max);
   if (x < 1 || x > max)
   {
      printf("Incorrect x-dimension!\n");
      return 1;
   }
   if (y < 1 || y > max)
   {
      printf("Incorrect y-dimension!\n");
      return 1;
   }
   if (planes != 1)
   {
      printf("Incorrect number of planes per pixel!\n");
      return 1;
   }
   if (bits != 24)
   {
      printf("Incorrect number of bits per pixel!\n");
      return 1;
   }
   if (k != 0)
   {
      printf("Incorrect counter value!\n");
      return 1;
   }

#ifndef GL_VERSION_2_0
   for (k = 1; k < x; k *= 2);
      if (k != x)
      {
         printf("Image x-dimension not a power of 2!\n");
         return 1;
      }
   for (k = 1; k < y; k *= 2);
      if (k != y)
      {
         printf("Image y-dimension not a power of 2!\n");
         return 1;
      }
#endif

   size = 3 * x * y;
   image = (unsigned char*)malloc(size);
   if (!image)
   {
      printf("Failed to allocate memory for image!\n");
      return 1;
   }

   if (fseek(input, off, SEEK_SET) || fread(image, size, 1, input) != 1)
   {
      printf("Failed to read image!\n");
      return 1;
   }
   fclose(input);

   for (k = 0; k < size; k += 3)
   {
      unsigned char temp = image[k];
      image[k] = image[k + 2];
      image[k + 2] = temp;
   }

   glGenTextures(1, &text);
   glBindTexture(GL_TEXTURE_2D, text);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
   if (glGetError())
   {
      printf("OpenGL error in generating texture!\n");
      return 1;
   }

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   free(image);
   return text;
}

// Definition for GameObject class setPosition function.
void GameObject::setPosition(float x, float y, float z)
{
   // Update the GameObject's translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Definition for GameObject class setScaling function.
void GameObject::setScaling(float dx, float dy, float dz)
{
   // Update the GameObject's scaling values.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;
}

// Definition for GameObject class setRotation function.
void GameObject::setRotation(float rx, float ry, float rz)
{
   // Update the GameObject's rotation about each axis.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Definition for GameObject getPosX getter function.
float GameObject::getPosX()
{
   return this->posX;
}

// Definition for GameObject getPosY getter function.
float GameObject::getPosY()
{
   return this->posY;
}

// Definition for GameObject getPosZ getter function.
float GameObject::getPosZ()
{
   return this->posZ;
}

// Definition for GameObject getScaleX getter function.
float GameObject::getScaleX()
{
   return this->scaleX;
}

// Definition for GameObject getScaleY getter function.
float GameObject::getScaleY()
{
   return this->scaleY;
}

// Definition for GameObject getScaleZ getter function.
float GameObject::getScaleZ()
{
   return this->scaleZ;
}

// Definition for GameObject getRotX getter function.
float GameObject::getRotX()
{
   return this->rotX;
}

// Definition for GameObject getRotY getter function.
float GameObject::getRotY()
{
   return this->rotY;
}

// Definition for GameObject getRotZ getter function.
float GameObject::getRotZ()
{
   return this->rotZ;
}

// Definition for GameObject class Reverse helper function.
void GameObject::Reverse(void* x, const int n)
{
   char* ch = (char*)x;
   for (int k = 0; k < n / 2; k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n - 1 - k];
      ch[n - 1 - k] = tmp;
   }
}