#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;


uniform sampler2DRect tex0;


uniform vec2 u_resolution;

// this is something we're creating for this shader
out vec2 texCoordVarying;

const float dSpace =100;


// the time value is passed into the shader by the OF app.
uniform float time;

uniform float mouseX;




void main(){
    
    
   
   // texCoordVarying = vec2(pnt);

    
    //vec2 count=u_resolution/dSpace;
   //texCoordVarying=(floor(texcoord/count))*count;
    
    //texCoordVarying = vec2(texcoord.x,texcoord.y);

    
 /*   vec4 modifiedPosition = modelViewProjectionMatrix * position;
    // we need to scale up the values we get from the texture
    float scale = 100;
    
    // here we get the red channel value from the texture
    // to use it as vertical displacement
   float displacementY = texture(tex0, texcoord).r;
    // use the displacement we created from the texture data
    // to modify the vertex position
    modifiedPosition.y += displacementY * scale;
    
    // this is the resulting vertex position
    gl_Position = modifiedPosition;
    

    // pass the texture coordinates to the fragment shader
    texCoordVarying = texcoord;
  //  gl_Position = modifiedPosition;
   */
    
    // the sine wave travels along the x-axis (across the screen),
    // so we use the x coordinate of each vertex for the calculation,
    // but we displace all the vertex along the y axis (up the screen)/
  //float displacementHeight = 100.0;
   // float displacementY = sin(time + (position.x / 100.0)) * displacementHeight;
    
    
    //vec2 count=u_resolution/dSpace;
  // vec2 varpos=(floor(vec2(position)/count))*count;
    
    // here we move the texture coordinates
    //texCoordVarying = vec2(position);

    
    vec4 modifiedPosition = modelViewProjectionMatrix * position;
   // modifiedPosition.y += displacementY;
    gl_Position = modifiedPosition;
    texCoordVarying = texcoord;



}
