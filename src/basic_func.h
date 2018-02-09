#include <cstdlib>


int get_random_integer(int a, int b)
{
  return a + rand() % b;
}

float get_absolute_value(float a)
{
  if(a<0) return -a;
  else return a;
}

float distance(float x1, float y1, float x2, float y2)
{
  return sqrt( pow(x1-x2,2) + pow(y1-y2,2) );
}

float getRandomBetween(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
