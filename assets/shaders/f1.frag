varying vec4 color;
varying vec2 texCoord;

uniform sampler2D tex;
uniform float time;

void main()
{
    vec4 col = texture2D(tex, texCoord);
    col = vec4(col.r * abs(texCoord.x), col.g * abs(texCoord.y), col.b, col.a);
    gl_FragColor = vec4(abs(col.r * sin(time * 0.0025)), col.g, col.b, col.a * .25);
    //gl_FragColor = vec4(1.0, abs(sin(time * 0.0025)), 1.0, 1.0);
    //gl_FragColor = col;
}

