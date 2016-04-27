#version 330

out vec4 outputColor;

uniform float fragloopDuration;
uniform float time;
smooth in vec4 theColor;
const vec4 firstColor = vec4(0, 0, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.80f, 1.0f, 0.0f, 1.0f);

void main()
{
    float currTime = mod(time, fragloopDuration);
    float currLerp = (sin(currTime*3.1415) / fragloopDuration);
    
    outputColor = mix(firstColor+theColor, secondColor+theColor, currLerp);
}
