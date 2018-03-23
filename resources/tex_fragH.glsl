#version 330 core

in vec2 texCoord;
out vec4 color;
uniform sampler2D texBuf;
uniform vec2 dir;
uniform int uWidth;
uniform int uHeight;
uniform int effect;

uniform float offset[5] = float[]( 0.0, 1.0, 2.0, 3.0, 4.0 );
uniform float weight[5] = float[]( 0.2270270270, 0.1945945946, 0.1216216216, 
											0.0540540541, 0.0162162162 );

void main(){
	
	if(effect == 0)
	{
		vec4 glow = vec4(0.0, 0.0, 0.0, 0.0);
		for (int i=1; i <5; i ++) {
			for(int j = 1; j < 5; j++)
			{
				glow += vec4(texture( texBuf, texCoord + vec2(offset[i], offset[j])/1024).rgb, 1);
				glow += vec4(texture( texBuf, texCoord - vec2(offset[i], offset[j])/1024).rgb, 1);
				glow += vec4(texture( texBuf, texCoord + vec2(offset[i], -offset[j])/1024).rgb, 1);
				glow += vec4(texture( texBuf, texCoord + vec2(-offset[i], offset[j])/1024).rgb, 1);
			}
		}
		glow = glow / 64;
	   color = glow;
	}
	
	else if(effect == 1)
	{
		vec4 glow = vec4(0.0, 0.0, 0.0, 0.0);
		for (int i=1; i <5; i ++) {
			for(int j = 1; j < 5; j++)
			{
				glow += vec4(texture( texBuf, texCoord + vec2(offset[i], offset[j])/1024).rgb, 1);
				glow += vec4(texture( texBuf, texCoord - vec2(offset[i], offset[j])/1024).rgb, 1);
				glow += vec4(texture( texBuf, texCoord + vec2(offset[i], -offset[j])/1024).rgb, 1);
				glow += vec4(texture( texBuf, texCoord + vec2(-offset[i], offset[j])/1024).rgb, 1);
			}
		}
		glow = glow / 64;
		glow = glow * vec4(0.8, 0.8, 1.0, 1.0);
	   color = vec4(texture( texBuf, texCoord ).rgb, 1) + glow;
   }
   else{
	   color = vec4(texture( texBuf, texCoord ).rgb, 1);
	   }
	
}
