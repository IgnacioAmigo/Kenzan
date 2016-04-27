#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform vec2 offset;
uniform float zNear;
uniform float zFar;
uniform float frustumScale;

void main()
{
    vec4 cameraPos = position + vec4(offset.x, offset.y, 0.0, 0.0);
    vec4 clipPos;
    
    clipPos.xy = cameraPos.xy * frustumScale;
    
    clipPos.z = cameraPos.z * (zNear + zFar) / (zNear - zFar);
    clipPos.z += 2 * zNear * zFar / (zNear - zFar);
    
    clipPos.w = -cameraPos.z;
    
    gl_Position = clipPos;
    theColor = color;
}


/*
--------------------------------------
#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
uniform vec2 offset;
uniform float time;
uniform float loopDuration;

smooth out vec4 theColor;

void main()
{
    float timeScale = 3.14159f * 2.0f / loopDuration;
    
    float currTime = mod(time, loopDuration);
    vec4 totalOffset = vec4(
        cos(currTime * timeScale) * 0.5f,
        sin(currTime * timeScale) * 0.5f,
        0.0f,
        0.0f);
    
    gl_Position = position + totalOffset;
    theColor = color;
}

#version 330

layout(location = 0) in vec4 position;
uniform float loopDuration;
uniform float time;

void main()
{
    float timeScale = 3.14159f * 2.0f / loopDuration;
    
    float currTime = mod(time, loopDuration);
    vec4 totalOffset = vec4(
        cos(currTime * timeScale) * 0.5f,
        sin(currTime * timeScale) * 0.5f,
        0.0f,
        0.0f);
    
    gl_Position = position + totalOffset;
}*/