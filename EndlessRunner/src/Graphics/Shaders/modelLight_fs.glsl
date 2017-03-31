"#version 330 core\n"

"#define INFINITE_LIGHT 0\n"
"#define POINT_LIGHT 1\n"
"#define SPOT_LIGHT 2\n"

"struct Light\n"
"{\n"
	 "vec3 direction;\n"
	 "vec3 position;\n"
	 "vec4 color;\n"
	 "float linear;\n"
	 "float quadratic;\n"
	 "float cutOff;\n"
	 "float outerCutOff;\n"
	 "float illuminance;\n"
	 "int type;\n"
"};\n"

"struct Material\n"
"{\n"
	 "sampler2D texture_diffuse1;\n"
	 "sampler2D texture_specular1;\n"
	 "float shininess;\n"
"};\n"

"in vec3 Normal;\n"
"in vec3 FragPos;\n"
"in vec2 TexCoords;\n"

"out vec4 color;\n"

"uniform Material material;\n"
"uniform Light light[50];\n"
"uniform int lightsCount;\n"

"vec3 calcLight(Light, vec3, vec3);\n"
"vec3 calcInfiniteLight(Light, vec3, vec3);\n"
"vec3 calcPointLight(Light, vec3, vec3);\n"
"vec3 calcSpotLight(Light, vec3, vec3);\n"

"void main()\n"
"{\n"
	 "color = texture(material.texture_diffuse1, TexCoords);\n"
	 "if(color.a == 0)\n"
		  "discard;\n"

	 "vec3 normal = normalize(Normal);\n"
	 "vec3 viewDir = normalize(vec3(400, 300, 726) - FragPos);\n"

	 "vec3 result;\n"
	 "for(int i = 0; i < lightsCount; i++)\n"
		  "result += calcLight(light[i], normal, viewDir);\n"

	 "color *= vec4(result, 1.f);\n"
"}\n"

"vec3 calcLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
	 "vec3 ret;\n"
	 "if(_light.type == INFINITE_LIGHT)\n"
		  "ret = calcInfiniteLight(_light, _normal, _viewDir);\n"
	 "else if(_light.type == POINT_LIGHT)\n"
		  "ret = calcPointLight(_light, _normal, _viewDir);\n"
	 "else if(_light.type == SPOT_LIGHT)\n"
		  "ret = calcSpotLight(_light, _normal, _viewDir);\n"
	 "return ret * _light.illuminance;\n"
"}\n"

"vec3 calcInfiniteLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
	 "vec3 lightDir = normalize(-_light.direction);\n"
	 "float diff = max(dot(_normal, lightDir), 0.f);\n"
	 "vec3 reflectDir = normalize(reflect(-lightDir, _normal));\n"
	 "float spec = pow(max(dot(_viewDir, reflectDir), 0.f), material.shininess);\n"

	 "vec3 diffuse = _light.color.xyz * diff;\n"
	 "vec3 specular = _light.color.xyz * spec;\n"

	 "return diffuse + specular;\n"
"}\n"

"vec3 calcPointLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
	 "vec3 lightDir = normalize(_light.position - FragPos);\n"
	 "float diff = max(dot(_normal, lightDir), 0.f);\n"
	 "vec3 reflectDir = normalize(reflect(-lightDir, _normal));\n"
	 "float spec = pow(max(dot(_viewDir, reflectDir), 0.f), material.shininess);\n"

	 "vec3 diffuse = _light.color.xyz * diff;\n"
	 "vec3 specular = _light.color.xyz * spec;\n"
	 "float distance = length(_light.position - FragPos);\n"
	 "float attenuation = 1.f / (1.f + _light.linear * distance + _light.quadratic * pow(distance, 2));\n"

	 "return (diffuse + specular) * attenuation;\n"
"}\n"

"vec3 calcSpotLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
	 "vec3 lightDir = normalize(_light.position - FragPos);\n"
	 "vec3 ret = calcPointLight(_light, _normal, _viewDir);\n"

	 "float angleCos = dot(lightDir, normalize(-_light.direction));\n"
	 "float intensity = clamp((angleCos - _light.outerCutOff) / (_light.cutOff - _light.outerCutOff), 0.f, 1.f);\n"

	 "return ret * intensity;\n"
"}"
