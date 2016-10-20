#version 120

uniform sampler2D texture;
uniform sampler2D shadow_map_texture;

// varying vec2 texCoordVarying;



void main(){
    vec2 pos = gl_TexCoord[0].st;
    // vec2 pos = texCoordVarying;
    vec3 src = texture2D(texture, pos).rgb;
    float mask = texture2D(shadow_map_texture, pos).r;

    gl_FragColor = vec4(src, mask);
    // gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}