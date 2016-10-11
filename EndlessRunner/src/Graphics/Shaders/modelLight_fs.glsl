"#version 330 core\n"
"\n"
"struct Light\n"
"{\n"
"	vec3 direction;\n"
"	vec3 position;\n"
"	vec4 color;\n"
"	float linear;\n"
"	float quadratic;\n"
"	float cutOff;\n"
"	float outerCutOff;\n"
"	float illuminance;\n"
"	int type;\n"
"};\n"
"\n"
"struct Material\n"
"{\n"
"	sampler2D texture_diffuse1;\n"
"	sampler2D texture_specular1;\n"
"	float shininess;\n"
"};\n"
"\n"
"in vec3 Normal;\n"
"in vec3 FragPos;\n"
"in vec2 TexCoords;\n"
"\n"
"out vec4 color;\n"
"\n"
"uniform Material material;\n"
"uniform Light light[20];\n"
"uniform int lightsCount;\n"
"\n"
"vec3 calcLight(Light _light, vec3 _normal, vec3 _viewDir);\n"
"vec3 calcDirLight(Light _light, vec3 _normal, vec3 _viewDir);\n"
"vec3 calcPointLight(Light _light, vec3 _normal, vec3 _viewDir);\n"
"vec3 calcSpotLight(Light _light, vec3 _normal, vec3 _viewDir);\n"
"\n"
"void main()\n"
"{	\n"
"	vec3 normal = normalize(Normal);\n"
"	vec3 viewDir = normalize(vec3(400, 300, 330) - FragPos);\n"
"	\n"
"	vec3 result;\n"
"	for(int i = 0; i < lightsCount; i++)\n"
"		result += calcLight(light[i], normal, viewDir);\n"
"\n"
"	color = texture(material.texture_diffuse1, TexCoords) * vec4(result, 1.f);\n"
"}\n"
"\n"
"vec3 calcLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
"	vec3 ret;\n"
"	if(_light.type == 0)\n"
"		ret = calcDirLight(_light, _normal, _viewDir);\n"
"	else if(_light.type == 1)\n"
"		ret = calcPointLight(_light, _normal, _viewDir);\n"
"	else if(_light.type == 2)\n"
"		ret = calcSpotLight(_light, _normal, _viewDir);\n"
"	return ret * _light.illuminance;\n"
"}\n"
"\n"
"vec3 calcDirLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
"	vec3 lightDir = normalize(-_light.direction);\n"
"	\n"
"	float diff = max(dot(_normal, lightDir), 0.f);\n"
"	\n"
"	vec3 reflectDir = normalize(reflect(-lightDir, _normal));\n"
"	float spec = pow(max(dot(_viewDir, reflectDir), 0.f), material.shininess);\n"
"	\n"
"	vec3 diffuse = _light.color.xyz * diff;\n"
"	vec3 specular = _light.color.xyz * spec;\n"
"	\n"
"	return diffuse + specular;\n"
"}\n"
"\n"
"vec3 calcPointLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
"	vec3 lightDir = normalize(_light.position - FragPos);\n"
"	\n"
"	float diff = max(dot(_normal, lightDir), 0.f);\n"
"\n"
"	vec3 reflectDir = normalize(reflect(-lightDir, _normal));\n"
"	float spec = pow(max(dot(_viewDir, reflectDir), 0.f), material.shininess);\n"
"	\n"
"	vec3 diffuse = _light.color.xyz * diff;\n"
"	vec3 specular = _light.color.xyz * spec;\n"
"	\n"
"	float distance = length(_light.position - FragPos);\n"
"	float attenuation = 1.f / (1.f + _light.linear * distance + _light.quadratic * pow(distance, 2));\n"
"	\n"
"	return (diffuse + specular) * attenuation;\n"
"}\n"
"\n"
"vec3 calcSpotLight(Light _light, vec3 _normal, vec3 _viewDir)\n"
"{\n"
"	vec3 lightDir = normalize(_light.position - FragPos);\n"
"	vec3 ret = calcPointLight(_light, _normal, _viewDir);\n"
"	\n"
"	float angleCos = dot(lightDir, normalize(-_light.direction));\n"
"	float intensity = clamp((angleCos - _light.outerCutOff) / (_light.cutOff - _light.outerCutOff), 0.f, 1.f);\n"
"	\n"
"	return ret * intensity;\n"
"}\n"
