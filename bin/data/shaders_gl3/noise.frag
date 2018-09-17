#version 150
out vec4 outputColor;
uniform vec2 u_resolution;
uniform vec3 u_mouse;
uniform float u_time;
uniform vec4 globalColor;

uniform float u_numDots;




uniform sampler2DRect tex0;
in vec2 texCoordVarying;

const float dotSize = 4;



uniform sampler2DRect tex1;




void main(){
  
    vec2 spacing;
    spacing=(u_resolution/u_numDots);
   
    
    
    vec2 pnt = ( floor(gl_FragCoord.xy/ spacing) +.5 ) * spacing;
    // flipping y -> no need if shader draws to fbo. dont really get this...
    // vec4 color2 = texture(tex1, vec2(pnt.x,u_resolution-pnt.y));
    vec4 color2 = texture(tex1, vec2(pnt.x,pnt.y));

    
    float d =(length(gl_FragCoord.xy-pnt)/dotSize);
    //outputColor=vec4(smoothstep(dotSize,0, d),0.0,0.0,1.0);
    
    
    outputColor = mix(vec4(0),color2, smoothstep(dotSize, 0, d));
    //vec4 color;

   
    
    
    

    //outputColor = texture(tex0, );

///outputColor = color2;

    
    // vec2 pnttxt = ( floor(gl_FragCoord.xy/ dSpace) +.5 ) * dSpace;
     //float d = length(gl_FragCoord.xy-pnttxt) / dotSize;
    
    
    
   // vec4 color2 = texture(tex0, pnttxt);
  //outputColor = mix(color2, vec4(0.0), smoothstep(0, 1, d));
    


}

