#version 330 core 

// as 2d maybe only take in vec2 
layout (location = 0) in vec2 aPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 mvp;

void main()
{
  // z coord should always be 0
 gl_Position = projection * view * model * vec4(aPos.xy, 0.0f, 1.0f);

}
