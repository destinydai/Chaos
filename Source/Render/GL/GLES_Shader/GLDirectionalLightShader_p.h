
#include "Render/GL/GlesSyntax.h"


struct directional_light 
{
	vec3 direction; // normalized light direction in eye space
	vec3 halfplane; // normalized half-plane vector
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
};

struct material_properties 
{
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
	float specular_exponent;
};

const float c_zero = 0.0;
const float c_one = 1.0;
uniform material_properties material;
uniform directional_light light;
// normal has been transformed into eye space and is a normalized
// value returns the computed color.
void directional_light(vec3 normal)
{
	vec4 computed_color = vec4(c_zero, c_zero, c_zero, c_zero);
	float ndotl; // dot product of normal & light direction
	float ndoth; // dot product of normal & half-plane vector
	ndotl = max(c_zero, dot(normal, light.direction));
	ndoth = max(c_zero, dot(normal, light.halfplane));
	computed_color += (light.ambient_color * material.ambient_color);
	computed_color += (ndotl * light.diffuse_color* material.diffuse_color);

		if (ndoth > c_zero)
		{
			computed_color += (pow(ndoth, material.specular_exponent) *
				material.specular_color * light.specular_color);
		}
		return computed_color;
}