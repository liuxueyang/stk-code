uniform sampler2D tex;
uniform vec3 ambient;

void main()
{
	vec2 texc = gl_TexCoord[0].xy;

	vec4 col = texture2D(tex, texc);

	col.xyz += ambient;

	gl_FragColor = col;
}