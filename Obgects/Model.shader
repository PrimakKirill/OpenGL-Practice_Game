#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;


uniform mat4 u_MVP;
uniform mat4 modelTransMatr;
uniform mat4 m_Matrix;
uniform vec3 scaleCoof;

out vec3 fragmentCoord;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	gl_Position = u_MVP * vec4(position.x*scaleCoof.x, position.y*scaleCoof.y, position.z*scaleCoof.z, 1.0f);
	fragmentCoord = vec3(modelTransMatr * vec4(position.x*scaleCoof.x, position.y*scaleCoof.y, position.z*scaleCoof.z, 1.0f));
	Normal = normal;
	TexCoord = vec2(texCoord.x,1.0f-texCoord.y);
}

#shader fragment
#version 330 core

in vec3 fragmentCoord;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D DiffTexture; 
uniform sampler2D SpecTexture;
uniform vec3 camPos;

//DirLights
uniform mat4x3 dirLightCollor;
uniform mat4x3 dirLightDirection;
//Point Lights
uniform mat4x3 pointLightCollor;
uniform mat4x3 pointLightPos;
//FlashLights
uniform mat4x3 flashLightCollor;
uniform mat4x3 flashLightPos;
uniform mat4 flashLightDirAndAngle;

out vec4 color;

void main()
{
	vec4 DiffTextexColor = texture(DiffTexture, TexCoord);
	if (DiffTextexColor.a < 0.1)
		discard;
	//Lights
	float ambientStrength = 0.05f;//можно сделать вектором и регулировать отдельно для каждой компоненты света(более реалистично)
	float diffStrength = 0.85f;//можно сделать вектором и регулировать отдельно для каждой компоненты света(более реалистично)
	float specularStrength = 0.5f;	//можно сделать вектором и регулировать отдельно для каждой компоненты света(более реалистично)

	float theta;//угол между фрагментом и направлением flashLight

	vec3 summlightColor = vec3(0.0f);
	vec3 summDifComp = vec3(0.0f);
	vec3 summSpecComp = vec3(0.0f);

	vec3 dirFromFragToCam = normalize(camPos - fragmentCoord);

	for (int i = 0; i < 4; i++)
	{
		//ambient
		summlightColor += dirLightCollor[i] + pointLightCollor[i] + flashLightCollor[i];

		//diffuse
		vec3 flashLightDir = normalize(fragmentCoord - flashLightPos[i]);
		theta = dot(flashLightDir, vec3(flashLightDirAndAngle[i]));

		vec3 pointLightDir = normalize(fragmentCoord - pointLightPos[i]);
		float pointLightDistCoof = 1.0 / (1.0 + 0.002 * dot(fragmentCoord - pointLightPos[i], fragmentCoord - pointLightPos[i]));
		summDifComp += max(dot(Normal, -dirLightDirection[i]), 0.0) * dirLightCollor[i] +
			+max(dot(Normal, -pointLightDir), 0.0) * pointLightDistCoof * pointLightCollor[i];
		if (theta > flashLightDirAndAngle[i][3])
		{
			float coof = (-flashLightDirAndAngle[i][3] + theta) / (1.0 - flashLightDirAndAngle[i][3]) / (0.3 + 0.002 * dot(fragmentCoord - flashLightPos[i], fragmentCoord - flashLightPos[i]));
			summDifComp += max(dot(Normal, -flashLightDir), 0.0) * flashLightCollor[i] * coof;//diffuse for flashlight
			summSpecComp += pow(max(dot(reflect(flashLightDir, normalize(Normal)), dirFromFragToCam), 0.0), 32) * flashLightCollor[i] * coof;//spec for flashlight
		}
	}

	
	color = DiffTextexColor * (vec4(summlightColor*ambientStrength, 1.0f)/*ambient*/ + vec4(summDifComp*diffStrength, 1.0f)/*diffuse*/) + texture(SpecTexture, TexCoord)*vec4(summSpecComp*specularStrength, 1.0f)/*specular*/;
}
