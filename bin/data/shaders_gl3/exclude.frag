#version 150




uniform sampler2DRect tex1;
uniform sampler2DRect tex2;

in vec2 texCoordVarying;

out vec4 outputColor;

uniform vec4 globalColor;






void main(){
    /*vec2 st = gl_FragCoord.xy/u_resolution;
    
    
    float windowWidth = 1024.0;
    float windowHeight = 768.0;
    
    float r = st.x;
    float g = st.y;
    float b = 1.0;
    float a = 1.0;
    outputColor = vec4(r, g, b, a);*/
   // outputColor=texture(tex0, vec2(st.x,u_resolution-st.y));
    
   // vec4 color1 = texture(tex0, vec2(st.x,u_resolution-st.y));
   // vec4 color2 = texture(tex1, vec2(st.x,u_resolution-st.y));
    
    vec4 color1 = texture(tex1, texCoordVarying).rgba;
    vec4 color2 = texture(tex2, texCoordVarying).rgba;
    vec4 color3 = vec4(1,0,0,1);
    vec4 mx=abs((color1+color2)-(2.0*color1*color2));
   // vec4 mx=abs(color1+color2)-0.5*color1;

    vec4 color = vec4(mx);
    outputColor = color;

}

