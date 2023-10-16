#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform int t;

void main() {
  vec4 tex;
  switch (t) {
    case 0: tex = texture(texture0, TexCoord); break;
    case 1: tex = texture(texture1, TexCoord); break;
    case 2: tex = texture(texture2, TexCoord); break;
    case 3: tex = texture(texture1, TexCoord); break;
    default: tex = texture(texture0, TexCoord);
  }

  FragColor = tex;
}
