#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
    // Sample the texture color
    vec4 texColor = texture(texture_diffuse1, TexCoords);

    // Calculate the diffuse lighting intensity
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-lightDirection);
    float diffuseIntensity = max(dot(normal, lightDir), 0.0);

    // Apply diffuse lighting color
    vec3 diffuseColor = lightColor * diffuseIntensity;
    vec3 finalColor = texColor.rgb * diffuseColor;

    // Set the output color
    FragColor = vec4(finalColor, texColor.a);
}
