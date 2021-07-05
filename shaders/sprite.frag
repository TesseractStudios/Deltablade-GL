#version 300 es
precision highp float;
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D tex;
uniform vec2 textureOffset;
void main()
{
	// FragColor = texture(tex, TexCoord + floor(TexCoord * 10.0) / 10.0);
	// vec2 texCoord = TexCoord + 1.0;
	// texCoord.y += 2.0;
	FragColor = texture(tex, (TexCoord / 6.1));
	// FragColor.rg = TexCoord;
	// FragColor.a = 1.0;
	// if(FragColor.a == 0.0)
	// 	discard;
} 