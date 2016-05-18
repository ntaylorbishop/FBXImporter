#version 410 core

uniform sampler2D gTexDiffuse; // 0
uniform float gAge;

in vec2 passUV0;

out vec4 outColor;

void main () {
  vec2 uv = passUV0;
  vec4 c = texture2D(gTexDiffuse, uv);
  
  c += texture2D(gTexDiffuse, uv+0.001);
  c += texture2D(gTexDiffuse, uv+0.003);
  c += texture2D(gTexDiffuse, uv+0.005);
  c += texture2D(gTexDiffuse, uv+0.007);
  c += texture2D(gTexDiffuse, uv+0.009);
  c += texture2D(gTexDiffuse, uv+0.011);
 
  c += texture2D(gTexDiffuse, uv-0.001);
  c += texture2D(gTexDiffuse, uv-0.003);
  c += texture2D(gTexDiffuse, uv-0.005);
  c += texture2D(gTexDiffuse, uv-0.007);
  c += texture2D(gTexDiffuse, uv-0.009);
  c += texture2D(gTexDiffuse, uv-0.011);
 
  c.rgb = c.xyz * vec3((c.r+c.g+c.b)/3.0);
  c = c / 9.5;
  outColor = c;
}