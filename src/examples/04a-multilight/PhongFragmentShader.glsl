#version 450

#define MAX_LIGHTS 4
struct Light
{
  vec4 color;
};
uniform Light lights[MAX_LIGHTS];

out vec4 frag_color;

void main () {

   vec4 finalColor=vec4(0.0,0.0,0.1,1);
   for (int index = 0; index < MAX_LIGHTS; index++) // for all light sources
   {
      finalColor+=lights[index].color;
   }
   frag_color = finalColor;

}

