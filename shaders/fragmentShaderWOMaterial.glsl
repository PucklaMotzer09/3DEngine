#version 330

struct ShadowMap
{
	sampler2D texture;
	mat4 lightSpaceMatrix;
};

struct PointLight
{
	vec3 position;
    
	float quadratic; 
    float linear;
    float constant;

    vec3 diffuse;
    vec3 specular;
	ShadowMap shadowMap;
	bool castsShadow;
};

vec3 calculatePointLight(PointLight light,vec3 fragPos,vec3 normal);

struct DirectionalLight
{
	vec3 direction;
  
    vec3 diffuse;
    vec3 specular;
	ShadowMap shadowMap;
	bool castsShadow;
};

vec3 calculateDirectionalLight(DirectionalLight light,vec3 fragPos,vec3 normal);

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
	float innerCutOff;
	float outerCutOff;
	float quadratic;
	float linear;
	float constant;
	ShadowMap shadowMap;
	bool castsShadow;
};

vec3 calculateSpotLight(SpotLight light,vec3 fragPos,vec3 normal);

in vec3 vertexPositionOut;
in vec3 vertexNormalOut;
in vec2 vertexUVOut;

out vec4 fragColor;

#define NUM_POINT_LIGHTS 4
#define NUM_DIRECTIONAL_LIGHTS 1
#define NUM_SPOT_LIGHTS 1

#if NUM_POINT_LIGHTS > 0
uniform PointLight pointLights[NUM_POINT_LIGHTS];
#endif
#if NUM_DIRECTIONAL_LIGHTS > 0
uniform DirectionalLight directionalLights[NUM_DIRECTIONAL_LIGHTS];
#endif
#if NUM_SPOT_LIGHTS > 0
uniform SpotLight spotLights[NUM_SPOT_LIGHTS];
#endif
uniform vec4 ambientLight;
uniform vec3 eyePosition;

float ambientTransperancy;
float diffuseTransperancy;
float specularTransperancy;
vec4 ambientColor;
vec3 viewDir;

void calculateVariables();
float shadowCalculation(vec4 fragPos,vec3 lightDir,vec3 normal,ShadowMap shadowMap);

void main()
{
	calculateVariables();
	
	vec4 resultingColor;

	#if NUM_POINT_LIGHTS > 0
	for(int i = 0;i<NUM_POINT_LIGHTS;i++)
		resultingColor += vec4(calculatePointLight(pointLights[i],vertexPositionOut,vertexNormalOut),1.0);
	#endif
	#if NUM_DIRECTIONAL_LIGHTS > 0
	for(int i = 0;i<NUM_DIRECTIONAL_LIGHTS;i++)
		resultingColor += vec4(calculateDirectionalLight(directionalLights[i],vertexPositionOut,vertexNormalOut),1.0);
	#endif
	#if NUM_SPOT_LIGHTS > 0
	for(int i = 0;i<NUM_SPOT_LIGHTS;i++)
		resultingColor += vec4(calculateSpotLight(spotLights[i],vertexPositionOut,vertexNormalOut),1.0);
	#endif
	
	#if NUM_POINT_LIGHTS <= 0 && NUM_DIRECTIONAL_LIGHTS <= 0 && NUM_SPOT_LIGHTS <= 0

	resultingColor.xyz = ambientColor.xyz * ambientColor.w * eyePosition / eyePosition;

	#endif

	resultingColor.w = 1.0;

	fragColor = resultingColor;
}

void calculateVariables()
{
	// Calculate all variables
	ambientTransperancy = ambientLight.w;
	diffuseTransperancy = 1.0;
	specularTransperancy = 1.0;
	ambientColor = vec4(ambientLight.xyz,ambientTransperancy);
	viewDir = normalize(eyePosition-vertexPositionOut);
}

vec3 calculatePointLight(PointLight light,vec3 fragPos,vec3 normal)
{
	vec3 lightVector = light.position - fragPos;
	vec3 normalizedLightVector = normalize(lightVector);
	float distance = length(lightVector);
	float a = light.quadratic,b = light.linear,c = light.constant;

	// Diffuse Light
	float brightness = clamp(dot(normalizedLightVector,normal),0.0,1.0)/(a*distance*distance+b*distance+c);
	vec3 diffuseLight = vec3(brightness,brightness,brightness) * light.diffuse;

	// Specular Light
	vec3 reflectedLightVector = reflect(-normalizedLightVector,normal);
	float sBright = pow(clamp(dot(viewDir,reflectedLightVector),0.0,1.0),30.0)/(a*distance*distance+b*distance+c);
	vec3 specularLight = vec3(sBright,sBright,sBright) * light.specular;

	vec4 specularColor = vec4(specularLight,specularTransperancy);
	vec4 diffuseColor = vec4(diffuseLight,diffuseTransperancy);
	vec4 resultingColor;

	float shadow = light.castsShadow ? shadowCalculation(vec4(fragPos,1.0),-normalizedLightVector,normal,light.shadowMap) : 0.0;

	resultingColor = ambientColor * ambientTransperancy;
	resultingColor = diffuseColor * diffuseTransperancy * (1.0 - shadow) + resultingColor;
	resultingColor = specularColor * specularTransperancy * (1.0 - shadow) + resultingColor;

	return resultingColor.xyz;
}

vec3 calculateDirectionalLight(DirectionalLight light,vec3 fragPos,vec3 normal)
{
	vec3 normalizedLightVector = normalize(-light.direction);

	// Diffuse Light
	float brightness = clamp(dot(normalizedLightVector,normal),0.0,1.0);
	vec3 diffuseLight = vec3(brightness,brightness,brightness) * light.diffuse;

	// Specular Light
	vec3 reflectedLightVector = reflect(-normalizedLightVector,normal);
	float sBright = pow(clamp(dot(viewDir,reflectedLightVector),0.0,1.0),30.0);
	vec3 specularLight = vec3(sBright,sBright,sBright) * light.specular;

	vec4 specularColor = vec4(specularLight,specularTransperancy);
	vec4 diffuseColor = vec4(diffuseLight,diffuseTransperancy);
	vec4 resultingColor;

	float shadow = light.castsShadow ? shadowCalculation(vec4(fragPos,1.0),-normalizedLightVector,normal,light.shadowMap) : 0.0;

	resultingColor = ambientColor * ambientTransperancy;
	resultingColor = diffuseColor * diffuseTransperancy * (1.0 - shadow) + resultingColor;
	resultingColor = specularColor * specularTransperancy * (1.0 - shadow) + resultingColor;

	return resultingColor.xyz;
}

vec3 calculateSpotLight(SpotLight light,vec3 fragPos,vec3 normal)
{
	vec3 lightVector = light.position - fragPos;
	vec3 normalizedLightVector = normalize(lightVector);
	float distance = length(lightVector);
	float a = light.quadratic,b = light.linear,c = light.constant;

	float theta = dot(normalizedLightVector,normalize(-light.direction));
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon,0.0,1.0);

	// Diffuse Light
	float brightness = clamp(dot(normalizedLightVector,normal),0.0,1.0)/(a*distance*distance+b*distance+c);
	vec3 diffuseLight = vec3(brightness,brightness,brightness) * light.diffuse * intensity;

	// Specular Light
	vec3 reflectedLightVector = reflect(-normalizedLightVector,normal);
	float sBright = pow(clamp(dot(viewDir,reflectedLightVector),0.0,1.0),30.0)/(a*distance*distance+b*distance+c);
	vec3 specularLight = vec3(sBright,sBright,sBright) * light.specular * intensity;

	vec4 specularColor = vec4(specularLight,specularTransperancy);
	vec4 diffuseColor = vec4(diffuseLight,diffuseTransperancy);
	vec4 resultingColor;

	float shadow = light.castsShadow ? shadowCalculation(vec4(fragPos,1.0),-normalizedLightVector,normal,light.shadowMap) : 0.0;

	resultingColor = ambientColor * ambientTransperancy;
	resultingColor = diffuseColor * diffuseTransperancy * (1.0 - shadow) + resultingColor;
	resultingColor = specularColor * specularTransperancy * (1.0 - shadow) + resultingColor;

	return resultingColor.xyz;
}

float shadowCalculation(vec4 fragPos,vec3 lightDir,vec3 normal,ShadowMap shadowMap)
{
	vec4 fragPosLightSpace = shadowMap.lightSpaceMatrix * fragPos;
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float fshadow;
	if(projCoords.z > 1.0)
		fshadow = 0.0;
	else
	{
		float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
		float currentDepth = projCoords.z;
		vec2 texelSize = 1.0 / textureSize(shadowMap.texture, 0);
		for(int x = -1; x <= 1; ++x)
		{
			for(int y = -1; y <= 1; ++y)
			{
				float pcfDepth = texture(shadowMap.texture, projCoords.xy + vec2(x, y) * texelSize).r; 
				fshadow += currentDepth - 0.005 > pcfDepth ? 1.0 : 0.0;        
			}    
		}
		fshadow /= 9.0;
	}
	return fshadow;
}