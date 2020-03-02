#shader vertex
#version 330 core
layout(location = 0) in vec3 position; // Устанавливаем позицию атрибута в 0
layout(location = 1) in vec2 texCoord;

out vec4 vertexColor; // Передаем цвет во фрагментный шейдер
out vec2 TexCoord;

out vec3 fragmentCoord;/////////////

uniform mat4 u_MVP;


uniform mat4 modelMatr;



void main()
{
	gl_Position = u_MVP * vec4(position, 1.0); // Напрямую передаем vec3 в vec4
	vertexColor = vec4(2 * position.x, 2 * position.z, 0.0f, 1.0f); // Устанавливаем значение выходной переменной в темно-красный цвет.
	TexCoord = texCoord;

	fragmentCoord = vec3(modelMatr * vec4(position , 1.0f));
}

#shader fragment
#version 330 core
in vec4 vertexColor; // Входная переменная из вершинного шейдера (то же название и тот же тип)
in vec2 TexCoord;

in vec3 fragmentCoord;

uniform sampler2D ourTexture;
uniform sampler2D specularTexture;


uniform vec3 summlightColor;
uniform vec3 diffComp;


uniform vec3 camPos;
uniform vec3 normal;

uniform mat4x3 lightPositions;
uniform mat4x3 lightColors;


out vec4 color;

void main()
{
	float specularStrength = 0.5f;	//можно сделать вектором и регулировать отдельно для каждой компоненты света(более реалистично)
	float ambientStrength = 0.1f;//можно сделать вектором и регулировать отдельно для каждой компоненты света(более реалистично)
	float diffStrength = 0.4f;//можно сделать вектором и регулировать отдельно для каждой компоненты света(более реалистично)
	
	vec3 specSumm = vec3(0.0f);
	for (int i = 0; i < 4; i++)
	{
		vec3 lightPos = vec3(lightPositions[i][0], lightPositions[i][1], lightPositions[i][2]);
		vec3 lightCol = lightColors[i];
		vec3 reverselightDir = normalize(-fragmentCoord + lightPos);
		vec3 dirFromFragToCam = normalize(camPos - fragmentCoord);
		vec3 reflectDir = reflect(-reverselightDir, normalize(normal));
		specSumm += lightCol * pow(max(dot(reflectDir, dirFromFragToCam), 0.0), 16);
	};
	
	//color = vec4(0.5f, 0.3f, 0.7f, 1.0f)*(vec4(summlightColor*ambientStrength, 1.0f) + vec4(diffComp * diffStrength, 1.0f) + vec4(specularStrength * specSumm, 1.0f));// +vec4(specComp, 1.0f));///*spec * (lightColor,1.0f)*/ *specularStrength);
	
	
	color = texture(ourTexture, TexCoord)*(vec4(summlightColor*ambientStrength, 1.0f) + vec4(diffComp * diffStrength, 1.0f))
		+ texture(specularTexture, TexCoord)*( vec4(specularStrength * specSumm, 1.0f));
}