#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;


// this is something we're creating for this shader
out vec2 texCoordVarying;



void main(){
    
    texCoordVarying = texcoord;
    vec4 modifiedPosition = modelViewProjectionMatrix * position;
    gl_Position = modifiedPosition;
    

}
