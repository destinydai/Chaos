

/////////////////////////////open gl es 2.0 /////////////////////////

#include "glm/glm.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;

using glm::mat2;
using glm::mat3;
using glm::mat4;

using glm::ivec2;
using glm::ivec3;
using glm::ivec4;

using glm::bvec2;
using glm::bvec3;
using glm::bvec4;

#define in
#define out
#define inout

#define precision
#define highp
#define mediump
#define lowp

#define uniform
#define attribute
#define varying

#define gl_Position  
#define gl_FrontFacing
#define gl_PointSize

#define invariant 

struct sampler2D;


//zhe only build-in uniform 
struct gl_DepthRangeParameters
{
	highp float near;
	highp float far;
	highp float diff;
};
uniform gl_DepthRangeParameters gl_DepthRange;

//Built-In Constants
const mediump int gl_MaxVertexAttribs = 8;
const mediump int gl_MaxVertexUniformVectors = 128;
const mediump int gl_MaxVaryingVectors = 8;
const mediump int gl_MaxVertexTextureImageUnits = 0;
const mediump int gl_MaxCombinedTextureImageUnits = 8;


//function
using glm::dot;
using glm::pow;

////////////////////////////////////////////////////////////////////////