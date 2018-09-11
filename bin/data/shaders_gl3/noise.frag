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
const float numDots=20;
const float dSpace = 30;

uniform sampler2DRect tex1;




// Plot a line on Y using a value between 0.0-1.0
float plot(vec2 st, float pct){
    return  smoothstep( pct-0.05, pct, st.y) -
    smoothstep( pct, pct+0.05, st.y);
    
   // return  smoothstep( pct-0, pct, st.y) -
   // smoothstep( pct, pct+0, st.y);
}


void main(){
   // vec2 st = gl_FragCoord.st/u_resolution;
    vec2 st = gl_FragCoord.xy/u_resolution;
    
    
    float windowWidth = 1024.0;
    float windowHeight = 768.0;
    
    float r = st.x;
    float g = st.y;
    float b = 1.0;
    float a = 1.0;
    outputColor = vec4(r, g, b, a);
    
    
    
    vec2 spacing;
    spacing=u_resolution/u_numDots;
   
    
    
    vec2 pnt = ( floor(gl_FragCoord.xy/ spacing) +.5 ) * spacing;
    // flipping y
    vec4 color2 = texture(tex1, vec2(pnt.x,u_resolution-pnt.y));
    
    float d =(length(gl_FragCoord.xy-pnt)/dotSize);
    //outputColor=vec4(smoothstep(dotSize,0, d),0.0,0.0,1.0);
   outputColor = mix(vec4(.9),color2, smoothstep(dotSize, 0, d));

    //outputColor = texture(tex0, );

///outputColor = color2;

    
    // vec2 pnttxt = ( floor(gl_FragCoord.xy/ dSpace) +.5 ) * dSpace;
     //float d = length(gl_FragCoord.xy-pnttxt) / dotSize;
    
    
    
   // vec4 color2 = texture(tex0, pnttxt);
  //outputColor = mix(color2, vec4(0.0), smoothstep(0, 1, d));
    


}

