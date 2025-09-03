#include <float.h> //NOTE: For FLT_MAX

#define PI32 3.14159265358979
#define SIN45 0.70710678118
#define TAU32 6.283185307
#define HALF_PI32 0.5f*PI32
#define D3D_MATRIX 0 //NOTE: Whether to use D3D or OpenGL matrix
// #define INT_MAX 2147483647

static inline float get_abs_value(float value) {
	if(value < 0) {
		value *= -1.0f;
	}
	return value;
}

inline float radiansToDegrees(float radians) {
	float result = (radians / TAU32) * 360;
	return result;

}

inline float degreesToRadians(float degrees) {
	float result = (degrees / 360.0f) * TAU32;
	return result;

}

int MathMin(int a, int b) {
	if(a < b) {
		return a;
	} else {
		return b;
	}

}

int MathMax(int a, int b) {
	if(a > b) {
		return a;
	} else {
		return b;
	}

}

float MathMaxf(float a, float b) {
	if(b < a) {
		return a;
	} else {
		return b;
	}
}

float MathMinf(float a, float b) {
	if(b > a) {
		return a;
	} else {
		return b;
	}

}

float signOf(float val) {
    return (val > 0) - (val < 0);
}

size_t MathMin_sizet(size_t a, size_t b) {
	if(b < a) {
		return b;
	} else {
		return a;
	}

}


size_t MathMax_sizet(size_t a, size_t b) {
	if(a < b) {
		return b;
	} else {
		return a;
	}

}

inline float ATan2_0toTau(float Y, float X) {
    float Result = (float)atan2(Y, X);
    if(Result < 0) {
        Result += TAU32; // is in the bottom range ie. 180->360. -PI32 being PI32. So we can flip it up by adding TAU32
    }
    
    assert(Result >= 0 && Result <= (TAU32 + 0.00001));
    return Result;
}

struct LerpTValue{
	float value;
};

static LerpTValue make_lerpTValue(float value) {
	LerpTValue result = {};
	result.value = value;

	return result;
}

static float lerp(float a, float b, LerpTValue t) {
	return (b - a)*t.value + a;
}

float randomBetween(float min, float max) { //inclusive for both min & max
	return lerp(min, max, make_lerpTValue((float)rand() / (float)RAND_MAX));
}

struct float2
{
    float x, y;
};

struct float3
{
	union {
		struct {
			float x, y, z;	
		};
		struct {
			float2 xy;
			float ignore;	
		};
		struct {
			float E[3];	
		};
	};
}; 

struct float4
{
	union {
		struct {
			float x, y, z, w;
		};
		struct {
			float2 xy;
			float ignore1;	
			float ignore2;	
		};
		struct {
			float3 xyz;
			float ignore;	
		};
		struct {
			float E[4];	
		};
	};
};


static float2 make_float2(float x0, float y0) {
	float2 result = {};

	result.x = x0;
	result.y = y0;

	return result;
}

//NOTE: This is a quaternion multiplication in 2d
static inline float integrateRot2d(float rot, float omegah) {
	float c = cos(rot);
	float s = sin(rot);
	float a = c - omegah * s;
	float result = acos(a);
	return result;
}

static float clamp(float min, float max, float value) {
	if(value < min) { value = min; }
	if(value > max) { value = max; }
	return value;
}

static int maxi(int a, int b) {
	int value = a;
	if(a < b) {
		value = b;
	}
	return value;
}

static float2 scale_float2(float dt, float2 value) {
	return make_float2(dt*value.x, dt*value.y);
}

static float2 plus_float2(float2 a, float2 b) {
	return make_float2(a.x+b.x, a.y+b.y);
}

static float2 minus_float2(float2 a, float2 b) {
	return make_float2(a.x-b.x, a.y-b.y);
}

static float float2_dot(float2 a, float2 b) {
	return (a.x*b.x + a.y*b.y);
}

inline float float2_cross(float2 a, float2 b)
{
	return a.x * b.y - a.y * b.x;
}

inline float2 float2_cross_scalar(float2  a, float s)
{
	return make_float2(s * a.y, -s * a.x);
}

inline float2 float2_cross_scalar(float s, float2 a)
{
	return make_float2(-s * a.y, s * a.x);
}

inline float sqr_float(float a) {
	return a * a;
}


static float2 float2_perp(float2 a) {
	return make_float2(-a.y, a.x);
}

//NOTE: Into different coordinate space
static float2 float2_transform(float2 a, float2 xAxis, float2 yAxis) {
	float x = float2_dot(a, xAxis);
	float y = float2_dot(a, yAxis);

	float2 result = make_float2(x, y);

	return result;
}

static float2 lerp_float2(float2 a, float2 b, float t) {
	return make_float2((b.x - a.x)*t + a.x, (b.y - a.y)*t + a.y);
}

float float2_magnitude(float2 v) {
	float result = (v.x*v.x + v.y*v.y); 

	result = sqrt(result);

	return result;
}



static float3 make_float3(float x0, float y0, float z0) {
	float3 result = {};

	result.x = x0;
	result.y = y0;
	result.z = z0;

	return result;
}

static float3 float3_cross(float3 v1, float3 v2) {
	float3 result = {};

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;

}

static float3 float3_hadamard(float3 a, float3 b) {
	float3 result = {};

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;

	return result;
}

static float3 plus_float3(float3 a, float3 b) {
	return make_float3(a.x+b.x, a.y+b.y, a.z+b.z);
}

static float4 make_float4(float x, float y, float z, float w) {
	float4 result = {};

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;

	return result;
}
static float3 lerp_float3(float3 a, float3 b, float t) {
	return make_float3((b.x - a.x)*t + a.x, (b.y - a.y)*t + a.y, (b.z - a.z)*t + a.z);
}

static float4 lerp_float4(float4 a, float4 b, float t) {
	return make_float4((b.x - a.x)*t + a.x, (b.y - a.y)*t + a.y, (b.z - a.z)*t + a.z, (b.w - a.w)*t + a.w);
}

static float3 scale_float3(float dt, float3 value) {
	return make_float3(dt*value.x, dt*value.y, dt*value.z);
}

static float3 negate_float3(float3 value) {
	return make_float3(-value.x, -value.y, -value.z);
}


static float4 scale_float4(float dt, float4 value) {
	return make_float4(dt*value.x, dt*value.y, dt*value.z, dt*value.w);
}

static float float3_dot(float3 a, float3 b) {
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

struct Rect2f {
	float minX;
	float minY;
	float maxX;
	float maxY;
};

static Rect2f make_rect2f(float minX, float minY, float maxX, float maxY) {
	Rect2f result = {};

	result.minX = minX;
	result.minY = minY;
	result.maxX = maxX;
	result.maxY = maxY;

	return result; 
}

static Rect2f make_rect2f_center_dim(float2 centre, float2 dim) {
	Rect2f result = {};

	result.minX = centre.x - 0.5f*dim.x;
	result.minY = centre.y - 0.5f*dim.y;
	result.maxX = centre.x + 0.5f*dim.x;
	result.maxY = centre.y + 0.5f*dim.y;

	return result; 
}

static Rect2f make_rect2f_min_dim(float minX, float minY, float dimX, float dimY) {
	Rect2f result = {};

	result.minX = minX;
	result.minY = minY;
	result.maxX = minX + dimX;
	result.maxY = minY + dimY;

	return result; 
}
static float2 get_centre_rect2f(Rect2f r) {
	float2 result = {};

	result.x = 0.5f*(r.maxX - r.minX) + r.minX;
	result.y = 0.5f*(r.maxY - r.minY) + r.minY;

	return result;
}

static float2 get_scale_rect2f(Rect2f r) {
	float2 result = {};

	result.x = (r.maxX - r.minX);
	result.y = (r.maxY - r.minY);

	return result;
}

static Rect2f rect2f_union(Rect2f a, Rect2f b) {
	Rect2f result = a;

	if(b.minX < a.minX) {
		result.minX = b.minX;
	}

	if(b.minY < a.minY) {
		result.minY = b.minY;
	}

	if(b.maxX > a.maxX) {
		result.maxX = b.maxX;
	}

	if(b.maxY > a.maxY) {
		result.maxY = b.maxY;
	}

	return result;
}

static Rect2f rect2f_minowski_plus(Rect2f a, Rect2f b, float2 center) {
	float2 a_ = get_scale_rect2f(a);
	float2 b_ = get_scale_rect2f(b);

	float2 scale = plus_float2(a_, b_);

	Rect2f result = make_rect2f_center_dim(center, scale);

	return result;
}	

struct Rect3f {
	union {
		struct {
			float minX;
			float minY;
			float minZ;
			float maxX;
			float maxY;
			float maxZ;
		};
		struct {
			float3 min;
			float3 max;
		};
	};

	
};

float3 rect3f_getCenter(Rect3f r) {
	float3 result = make_float3(lerp(r.minX, r.maxX, make_lerpTValue(0.5f)), lerp(r.minY, r.maxY, make_lerpTValue(0.5f)), lerp(r.minZ, r.maxZ, make_lerpTValue(0.5f)));
	return result;
}

static Rect3f make_rect3f(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	Rect3f result = {};

	result.minX = minX;
	result.minY = minY;
	result.minZ = minZ;
	result.maxX = maxX;
	result.maxY = maxY;
	result.maxZ = maxZ;

	return result; 
}

static Rect3f rect3f_expand_uniform(Rect3f a, float size) {
	a.minX -= size;
	a.maxX += size;

	a.minY -= size;
	a.maxY += size;

	a.minZ -= size;
	a.maxZ += size;

	return a;
}

static Rect3f make_rect3f_center_dim(float3 centre, float3 dim) {
	Rect3f result = {};

	result.minX = centre.x - 0.5f*dim.x;
	result.minY = centre.y - 0.5f*dim.y;
	result.minZ = centre.z - 0.5f*dim.z;
	result.maxX = centre.x + 0.5f*dim.x;
	result.maxY = centre.y + 0.5f*dim.y;
	result.maxZ = centre.z + 0.5f*dim.z;

	return result; 
}

static Rect3f make_rect3f_min_dim(float minX, float minY, float minZ, float dimX, float dimY, float dimZ) {
	Rect3f result = {};

	result.minX = minX;
	result.minY = minY;
	result.minZ = minZ;
	result.maxX = minX + dimX;
	result.maxY = minY + dimY;
	result.maxZ = minZ + dimZ;

	return result; 
}

float3 normalize_float3(float3 v) {
	float len = (v.x*v.x + v.y*v.y + v.z*v.z); 
	len = sqrt(len);
	if(len != 0) {
		v.x /= len;
		v.y /= len;
		v.z /= len;
	} 
	
	return v;
}

static float3 get_scale_rect3f(Rect3f r) {
	float3 result = {};

	result.x = (r.maxX - r.minX);
	result.y = (r.maxY - r.minY);
	result.z = (r.maxZ - r.minZ);

	return result;
}

static Rect3f rect3f_minowski_plus(Rect3f a, Rect3f b, float3 center) {
	float3 a_ = get_scale_rect3f(a);
	float3 b_ = get_scale_rect3f(b);

	float3 scale = plus_float3(a_, b_);

	Rect3f result = make_rect3f_center_dim(center, scale);

	return result;
}

static Rect3f rect3f_minowski_plus(float3 aScale, float3 bScale, float3 center) {
	float3 scale = plus_float3(aScale, bScale);
	Rect3f result = make_rect3f_center_dim(center, scale);
	return result;
}


struct EasyPlane {
    float3 origin;
    float3 normal;
};

struct EasyRay {
    float3 origin;
    float3 direction;
};

static float3 minus_float3(float3 a, float3 b) {
	return make_float3(a.x-b.x, a.y-b.y, a.z-b.z);
}

bool easyMath_castRayAgainstPlane(EasyRay r, EasyPlane p, float3 *hitPoint, float *tAt) {
    bool didHit = false;

    //NOTE(ollie): Normalize the ray & plane normal
    p.normal = normalize_float3(p.normal);
    r.direction = normalize_float3(r.direction);
    //

    float denom = float3_dot(p.normal, r.direction); 
    if (get_abs_value(denom) > 1e-6) {  //ray is perpindicular to the plane, therefore either infinity or zero solutions
        float3 p0l0 = minus_float3(p.origin, r.origin); 
        *tAt = float3_dot(p0l0, p.normal) / denom; 
        
        *hitPoint = plus_float3(r.origin, scale_float3(*tAt, r.direction));
        didHit = true;
    } 


    return didHit;
}

#define NUMDIM  3
#define RIGHT   0
#define LEFT    1
#define MIDDLE  2

static inline bool easyMath_rayVsAABB3f(float3 origin, float3 dir, Rect3f b, float3 *hitPoint, float *tAt, float3 *normal) {
    bool inside = true;
    int quadrant[NUMDIM];
    int i;
    int whichPlane;
    double maxT[NUMDIM];
    double candidatePlane[NUMDIM];
    dir = normalize_float3(dir);

	float3 normals[] = {make_float3(0, -1, 0), make_float3(0, 1, 0), make_float3(-1, 0, 0), make_float3(1, 0, 0), make_float3(0, 0, -1), make_float3(0, 0, 1)};

    /* Find candidate planes */
    for (i=0; i<NUMDIM; i++)
        if(origin.E[i] < b.min.E[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = b.min.E[i];
            inside = false;
        }else if (origin.E[i] > b.max.E[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = b.max.E[i];
            inside = false;
        }else   {
            quadrant[i] = MIDDLE;
        }

    /* Ray origin inside bounding box */
    if(inside)  {
        *hitPoint = origin;
		*tAt = 0;
		// printf("STUCK IN BLOCK\n");
		*normal = make_float3(0, 0, 0);
        return true;
    }


    /* Calculate T distances to candidate planes */
    for (i = 0; i < NUMDIM; i++)
        if (quadrant[i] != MIDDLE && dir.E[i] !=0.) //not in the middle & no parrallel
            maxT[i] = (candidatePlane[i]-origin.E[i]) / dir.E[i];
        else
            maxT[i] = -1.;

    /* Get largest of the maxT's for final choice of intersection */
    whichPlane = 0;
    for (i = 1; i < NUMDIM; i++) {
        if (maxT[whichPlane] < maxT[i]) {
            whichPlane = i;
        }
    }
    *tAt = maxT[whichPlane];
	
    /* Check final candidate actually inside box */
    if (maxT[whichPlane] < 0.) return (false); //behind the ray
    for (i = 0; i < NUMDIM; i++)
        if (whichPlane != i) {
            hitPoint->E[i] = origin.E[i] + maxT[whichPlane]*dir.E[i]; //our lerp
            if (hitPoint->E[i] < b.min.E[i] || hitPoint->E[i] > b.max.E[i]) //outside of the AABB
                return false;
        } else {
            hitPoint->E[i] = candidatePlane[i];
        }

	float3 boxCenter = rect3f_getCenter(b);
	float3 s =  get_scale_rect3f(b);
	float3 testRay = minus_float3(*hitPoint, boxCenter);
	testRay.x /= 0.5f*s.x;
	testRay.y /= 0.5f*s.y;
	testRay.z /= 0.5f*s.z;
	
	float maxShadow = 0.0f;
	float3 normalFound = make_float3(0, 0, 0);
	bool found = false;
	for(int i = 0; i < arrayCount(normals); ++i) {
		normals[i] = normalize_float3(normals[i]);
		float t = float3_dot(normals[i], testRay);

		if(t >= maxShadow) {
			maxShadow = t;
			normalFound = normals[i];
			found = true;
		}
	}

	*normal = normalFound;

    return true;              /* ray hits box */
}

struct float12
{
	union {
		struct {
			float E[12];
		};
		struct {
			float E_[3][3];
		};
	};
    
}; 

struct float16
{
	union {
		struct {
			float E[16];
		};
		struct {
			float E_[4][4];
		};
	};
    
}; 


#define MATH_3D_NEAR_CLIP_PlANE 0.1f
#define MATH_3D_FAR_CLIP_PlANE 1000.0f

static float16 make_ortho_matrix_bottom_left_corner(float planeWidth, float planeHeight, float nearClip, float farClip) {
	//NOTE: The size of the plane we're projection onto
	float a = 2.0f / planeWidth;
	float b = 2.0f / planeHeight;

	//NOTE: We can offset the origin of the viewport by adding these to the translation part of the matrix
	float originOffsetX = -1; //NOTE: Defined in NDC space
	float originOffsetY = -1; //NOTE: Defined in NDC space


	float16 result = {{
	        a, 0, 0, 0,
	        0, b, 0, 0,
	        0, 0, 1.0f/(farClip - nearClip), 0,
	        originOffsetX, originOffsetY, nearClip/(nearClip - farClip), 1
	    }};

	return result;
}

static float16 make_ortho_matrix_bottom_left_corner_01NDC(float planeWidth, float planeHeight, float nearClip, float farClip) {
	//NOTE: The size of the plane we're projection onto
	float a = 1.0f / planeWidth;
	float b = 1.0f / planeHeight;

	//NOTE: We can offset the origin of the viewport by adding these to the translation part of the matrix
	float originOffsetX = 0; //NOTE: Defined in NDC space
	float originOffsetY = 0; //NOTE: Defined in NDC space


	float16 result = {{
	        a, 0, 0, 0,
	        0, b, 0, 0,
	        0, 0, 1.0f/(farClip - nearClip), 0,
	        originOffsetX, originOffsetY, nearClip/(nearClip - farClip), 1
	    }};

	return result;
}

float12 float12_multiply(float12 a, float12 b) {
    float12 result = {};
    
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            
            result.E_[i][j] = 
                a.E_[0][j] * b.E_[i][0] + 
                a.E_[1][j] * b.E_[i][1] + 
                a.E_[2][j] * b.E_[i][2];
        }
    }
    
    return result;
}


float16 float16_multiply(float16 a, float16 b) {
    float16 result = {};
    
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            
            result.E_[i][j] = 
                a.E_[0][j] * b.E_[i][0] + 
                a.E_[1][j] * b.E_[i][1] + 
                a.E_[2][j] * b.E_[i][2] + 
                a.E_[3][j] * b.E_[i][3];
            
        }
    }
    
    return result;
}

static float16 make_ortho_matrix_top_left_corner_y_down(float planeWidth, float planeHeight, float nearClip, float farClip) {
	//NOTE: The size of the plane we're projection onto
	float a = 2.0f / planeWidth;
	float b = 2.0f / planeHeight;

	//NOTE: We can offset the origin of the viewport by adding these to the translation part of the matrix
	float originOffsetX = -1; //NOTE: Defined in NDC space
	float originOffsetY = 1; //NOTE: Defined in NDC space


	float16 result = {{
	        a, 0, 0, 0,
	        0, -b, 0, 0,
	        0, 0, 1.0f/(farClip - nearClip), 0,
	        originOffsetX, originOffsetY, nearClip/(nearClip - farClip), 1
	    }};


	return result;
}

static float16 make_ortho_matrix_top_left_corner(float planeWidth, float planeHeight, float nearClip, float farClip) {
	//NOTE: The size of the plane we're projection onto
	float a = 2.0f / planeWidth;
	float b = 2.0f / planeHeight;

	//NOTE: We can offset the origin of the viewport by adding these to the translation part of the matrix
	float originOffsetX = -1; //NOTE: Defined in NDC space
	float originOffsetY = 1; //NOTE: Defined in NDC space


	float16 result = {{
	        a, 0, 0, 0,
	        0, b, 0, 0,
	        0, 0, 1.0f/(farClip - nearClip), 0,
	        originOffsetX, originOffsetY, nearClip/(nearClip - farClip), 1
	    }};

	return result;
}

static float16 make_ortho_matrix_origin_center(float planeWidth, float planeHeight, float nearClip, float farClip) {
	//NOTE: The size of the plane we're projection onto
	float a = 2.0f / planeWidth;
	float b = 2.0f / planeHeight;

	//NOTE: We can offset the origin of the viewport by adding these to the translation part of the matrix
	float originOffsetX = 0; //NOTE: Defined in NDC space
	float originOffsetY = 0; //NOTE: Defined in NDC space


	float16 result = {{
	        a, 0, 0, 0,
	        0, b, 0, 0,
	        0, 0, 1.0f/(farClip - nearClip), 0,
	        originOffsetX, originOffsetY, nearClip/(nearClip - farClip), 1
	    }};

	return result;
}

float2 perp2d(float2 p) {
	return make_float2(-p.y, p.x);
}

float2 getProjectionPlaneSize(float FOV_degrees, float aspectRatio_y_over_x) {
	//NOTE: Convert the Camera's Field of View from Degress to Radians
	float FOV_radians = (FOV_degrees*PI32) / 180.0f;

	//NOTE: Get the size of the plane the game world will be projected on.
	float t = 2*tan(FOV_radians/2); //plane's height
	float r = t*(1.0f / aspectRatio_y_over_x); //plane's width

	return make_float2(r, t);
}

static float16 make_perspective_matrix_origin_center(float FOV_degrees, float nearClip, float farClip, float aspectRatio_y_over_x) {
	//NOTE: Convert the Camera's Field of View from Degress to Radians
	float FOV_radians = (FOV_degrees*PI32) / 180.0f;

	//NOTE: Get the size of the plane the game world will be projected on.
	float t = tan(FOV_radians/2); //plane's height
	float r = t*(1.0f / aspectRatio_y_over_x); //plane's width

#if D3D_MATRIX
	float16 result = {{
	        1 / r, 0, 0, 0,
	        0, 1 / t, 0, 0,
	        0, 0, farClip/(farClip - nearClip), 1,
	        0, 0, (-nearClip*farClip)/(farClip - nearClip), 0
	    }};
#else
	float16 result = {{
        1 / r, 0, 0, 0,
        0, 1 / t, 0, 0,
        0, 0, (farClip + nearClip)/(farClip - nearClip), 1,
        0, 0, (-2*nearClip*farClip)/(farClip - nearClip), 0
    }};

#endif

	    return result;
}


static bool in_rect2f_bounds(Rect2f bounds, float2 point) {
	bool result = false;

	if(point.x >= bounds.minX && point.x < bounds.maxX && point.y >= bounds.minY && point.y < bounds.maxY) {
		result = true;
	}

	return result;
}

static bool in_rect3f_bounds(Rect3f bounds, float3 point) {
	bool result = false;

	if(point.x >= bounds.minX && point.x < bounds.maxX && point.y >= bounds.minY && point.y < bounds.maxY && point.z >= bounds.minZ && point.z < bounds.maxZ) {
		result = true;
	}

	return result;
}

static float16 float16_identity() {
	float16 result = {};

	result.E_[0][0] = 1;
	result.E_[1][1] = 1;
	result.E_[2][2] = 1;
	result.E_[3][3] = 1;

	return result;
}

static float12 float12_identity() {
	float12 result = {};

	result.E_[0][0] = 1;
	result.E_[1][1] = 1;
	result.E_[2][2] = 1;

	return result;
}

static float16 float16_set_pos(float16 result, float3 pos) {

	result.E_[3][0] = pos.x;
	result.E_[3][1] = pos.y;
	result.E_[3][2] = pos.z;
	result.E_[3][3] = 1;

	return result;
}

static float16 float16_removeTranslation(float16 result) {

	result.E_[3][0] = 0;
	result.E_[3][1] = 0;
	result.E_[3][2] = 0;

	return result;
}

float3 float3_negate(float3 v) {
	v.x *= -1;
	v.y *= -1;
	v.z *= -1;
	return v;
}

float2 float2_negate(float2 v) {
	v.x *= -1;
	v.y *= -1;
	return v;
}

bool float3_equal(float3 a, float3 b) {
	bool result = (a.x == b.x && a.y == b.y && a.z == b.z);

	return result;
}

float2 normalize_float2(float2 v) {
	float len = (v.x*v.x + v.y*v.y); 
	len = sqrt(len);
	if(len != 0) {
		v.x /= len;
		v.y /= len;
	} 
	
	return v;
}


float float3_magnitude_sqr(float3 v) {
	float result = (v.x*v.x + v.y*v.y + v.z*v.z); 
	return result;
}

float float3_magnitude(float3 v) {
	float result = (v.x*v.x + v.y*v.y + v.z*v.z); 

	result = sqrt(result);

	return result;
}


float16 float16_scale(float16 a, float3 scale) {
	a.E_[0][0] *= scale.x;
	a.E_[0][1] *= scale.x;
	a.E_[0][2] *= scale.x;

	a.E_[1][0] *= scale.y;
	a.E_[1][1] *= scale.y;
	a.E_[1][2] *= scale.y;

	a.E_[2][0] *= scale.z;
	a.E_[2][1] *= scale.z;
	a.E_[2][2] *= scale.z;

    return a;
}

float4 float16_transform(float16 i, float4 p) {
	float4 result;

	result.x = p.x*i.E_[0][0] + p.y*i.E_[1][0] + p.z*i.E_[2][0] + p.w*i.E_[3][0];
	result.y = p.x*i.E_[0][1] + p.y*i.E_[1][1] + p.z*i.E_[2][1] + p.w*i.E_[3][1];
	result.z = p.x*i.E_[0][2] + p.y*i.E_[1][2] + p.z*i.E_[2][2] + p.w*i.E_[3][2];
	result.w = p.x*i.E_[0][3] + p.y*i.E_[1][3] + p.z*i.E_[2][3] + p.w*i.E_[3][3];

	return result;
}

float3 float12_scale(float12 i, float3 p) {
	float3 result;

	result.x = p.x*i.E_[0][0] + p.y*i.E_[1][0] + p.z*i.E_[2][0];
	result.y = p.x*i.E_[0][1] + p.y*i.E_[1][1] + p.z*i.E_[2][1];
	result.z = p.x*i.E_[0][2] + p.y*i.E_[1][2] + p.z*i.E_[2][2];

	return result;
}

float12 float12_zeroed() {
	float12 result = {};
	return result;
}


float12 float12_transpose(float12 val) {
    float12 result = float12_identity();
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            result.E_[j][i] = val.E_[i][j];
        }
    }
    return result;
}

float12 float12_inverse(float12 m) {
    float12 result = float12_zeroed();

    float a = m.E_[0][0];
    float b = m.E_[0][1];
    float c = m.E_[0][2];

    float d = m.E_[1][0];
    float e = m.E_[1][1];
    float f = m.E_[1][2];

    float g = m.E_[2][0];
    float h = m.E_[2][1];
    float i = m.E_[2][2];

    float det = a * (e * i - f * h)
              - b * (d * i - f * g)
              + c * (d * h - e * g);

    if (det == 0.0f) {
        // Handle non-invertible matrix case
        // Here: return identity or zero matrix as fallback
        return float12_zeroed(); // or assert, or set to identity
    }

    float invDet = 1.0f / det;

    result.E_[0][0] =  (e * i - f * h) * invDet;
    result.E_[0][1] = -(b * i - c * h) * invDet;
    result.E_[0][2] =  (b * f - c * e) * invDet;

    result.E_[1][0] = -(d * i - f * g) * invDet;
    result.E_[1][1] =  (a * i - c * g) * invDet;
    result.E_[1][2] = -(a * f - c * d) * invDet;

    result.E_[2][0] =  (d * h - e * g) * invDet;
    result.E_[2][1] = -(a * h - b * g) * invDet;
    result.E_[2][2] =  (a * e - b * d) * invDet;
   
    return result;
}


bool rect3fInsideViewFrustrum(Rect3f rect, float3 cameraP, float16 cameraMatrix, float FOV_degrees, float nearClip, float farClip, float aspectRatio_y_over_x) {
	bool result = true;
	
	float3 unitXAxis = make_float3(cameraMatrix.E_[0][0], cameraMatrix.E_[0][1], cameraMatrix.E_[0][2]);
	float3 unitYAxis = make_float3(cameraMatrix.E_[1][0], cameraMatrix.E_[1][1], cameraMatrix.E_[1][2]);
	float3 unitZAxis = make_float3(cameraMatrix.E_[2][0], cameraMatrix.E_[2][1], cameraMatrix.E_[2][2]);

	float3 rectPoints[8] = {
		make_float3(rect.minX, rect.minY, rect.minZ),
		make_float3(rect.minX, rect.maxY, rect.minZ),
		make_float3(rect.maxX, rect.minY, rect.minZ),
		make_float3(rect.maxX, rect.maxY, rect.minZ),
		make_float3(rect.minX, rect.minY, rect.maxZ),
		make_float3(rect.minX, rect.maxY, rect.maxZ),
		make_float3(rect.maxX, rect.minY, rect.maxZ),
		make_float3(rect.maxX, rect.maxY, rect.maxZ),
	}; 

	EasyPlane planes[6];

	float FOV_radians = (FOV_degrees*PI32) / 180.0f;

	//NOTE: Get the size of the plane the game world will be projected on.
	float y = tan(FOV_radians/2); //plane's half height
	float x = y*(1.0f / aspectRatio_y_over_x); //plane's half width

	float yFar = farClip*y; //plane's far half height
	float xFar = farClip*x; //plane's far half width

	//NOTE: Nearest end plane
	planes[0].origin = plus_float3(scale_float3(nearClip, unitZAxis), cameraP);
	planes[0].normal = unitZAxis;

	//NOTE: Furtherest end plane
	planes[1].normal = float3_negate(unitZAxis);
	planes[1].origin = plus_float3(scale_float3(farClip, unitZAxis), cameraP);

	float3 closeCorners[4] = {
		plus_float3(planes[0].origin, float16_transform(cameraMatrix, make_float4(-x, -y, 0, 0)).xyz),
		plus_float3(planes[0].origin, float16_transform(cameraMatrix, make_float4(x, -y, 0, 0)).xyz),
		plus_float3(planes[0].origin, float16_transform(cameraMatrix, make_float4(x, y, 0, 0)).xyz),
		plus_float3(planes[0].origin, float16_transform(cameraMatrix, make_float4(-x, y, 0, 0)).xyz),
	};

	float3 farCorners[4] = {
		plus_float3(planes[1].origin, float16_transform(cameraMatrix, make_float4(-xFar, -yFar, 0, 0)).xyz),
		plus_float3(planes[1].origin, float16_transform(cameraMatrix, make_float4(xFar, -yFar, 0, 0)).xyz),
		plus_float3(planes[1].origin, float16_transform(cameraMatrix, make_float4(xFar, yFar, 0, 0)).xyz),
		plus_float3(planes[1].origin, float16_transform(cameraMatrix, make_float4(-xFar, yFar, 0, 0)).xyz),
	};

	float3 orthoVectors[4] = {unitXAxis, unitYAxis, negate_float3(unitXAxis), negate_float3(unitYAxis)};

	for(int i = 0; i < arrayCount(farCorners); ++i) {
		int index = i + 1;

		if(index >= arrayCount(farCorners)) {
			index = 0;
		}

		float3 a = lerp_float3(closeCorners[i], farCorners[i], 0.5f);
		float3 b = lerp_float3(closeCorners[index], farCorners[index], 0.5f);

		planes[2 + i].origin = lerp_float3(a, b, 0.5f);

		float3 a1 = lerp_float3(closeCorners[i], closeCorners[index], 0.5f);
		float3 b1 = lerp_float3(farCorners[i], farCorners[index], 0.5f);

		float3 v =  normalize_float3(minus_float3(b1, a1));

		planes[2 + i].normal = float3_cross(v, orthoVectors[i]);
	}
	
	for(int i = 0; i < arrayCount(planes) && result; ++i) {
		EasyPlane p = planes[i];
		bool insidePlane = false;
		for(int j = 0; j < arrayCount(rectPoints) && !insidePlane; ++j) {
			float3 point = minus_float3(rectPoints[j], p.origin); 

			//NOTE: Normal points inwards to the center of the frustrum
			if(float3_dot(point, p.normal) >= 0) {
				insidePlane = true;
			}
		}
		if(!insidePlane) {
			result = false;
		}
	}
	return result;

}

float16 float16_angle_aroundX(float angle_radians) {
    float16 result = {{
			1, 0, 0, 0,
			0, (float)cos(angle_radians), (float)sin(angle_radians), 0,
            0, (float)cos(angle_radians + HALF_PI32), (float)sin(angle_radians + HALF_PI32), 0,
            0, 0, 0, 1
        }};
    return result;
}

float16 float16_angle_aroundY(float angle_radians) {
    float16 result = {{
            (float)cos(angle_radians), 0, (float)sin(angle_radians), 0,
			0, 1, 0, 0,
            (float)cos(angle_radians + HALF_PI32), 0, (float)sin(angle_radians + HALF_PI32), 0,
            0, 0, 0, 1
        }};
    return result;
}


float16 float16_angle_aroundZ(float angle_radians) {
    float16 result = {{
            (float)cos(angle_radians), (float)sin(angle_radians), 0, 0,
            (float)cos(angle_radians + HALF_PI32), (float)sin(angle_radians + HALF_PI32), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }};
    return result;
}

float16 float16_transpose(float16 val) {
    float16 result = float16_identity();
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            result.E_[j][i] = val.E_[i][j];
        }
    }
    return result;
}

float16 eulerAnglesToTransform(float y, float x, float z) {
	//NOTE: Incoming in degrees
	float16 result = float16_identity();

	result = float16_multiply(float16_angle_aroundX((x / 360)*TAU32), float16_angle_aroundZ((z / 360)*TAU32));
	result = float16_multiply(float16_angle_aroundY((y / 360)*TAU32), result);

	return result;
}


float4 identityQuaternion() {
    return make_float4(0, 0, 0, 1);
}


float4 easyMath_normalizeQuaternion(float4 q) {
    float n = sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
    
    q.x /= n;
    q.y /= n;
    q.z /= n;
    q.w /= n;

    return q;
}


float12 quaternionToMatrix3x3(float4 q) {
    float12 result = float12_identity();

	q = easyMath_normalizeQuaternion(q);
    
    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;
    
    // Compute commonly used terms to avoid redundant calculations
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    result.E[0] = 1.0f - 2.0f * (y2 + z2);
    result.E[1] = 2.0f * (xy - wz);
    result.E[2] = 2.0f * (xz + wy);

    result.E[3] = 2.0f * (xy + wz);
    result.E[4] = 1.0f - 2.0f * (x2 + z2);
    result.E[5] = 2.0f * (yz - wx);

    result.E[6] = 2.0f * (xz - wy);
    result.E[7] = 2.0f * (yz + wx);
    result.E[8] = 1.0f - 2.0f * (x2 + y2);

    return result;
    
}

float16 quaternionToMatrix(float4 q) {
    float16 result = float16_identity();
    
    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;
    
    // Compute commonly used terms to avoid redundant calculations
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    result.E[0] = 1.0f - 2.0f * (y2 + z2);
    result.E[1] = 2.0f * (xy - wz);
    result.E[2] = 2.0f * (xz + wy);
    result.E[3] = 0.0f;

    result.E[4] = 2.0f * (xy + wz);
    result.E[5] = 1.0f - 2.0f * (x2 + z2);
    result.E[6] = 2.0f * (yz - wx);
    result.E[7] = 0.0f;

    result.E[8] = 2.0f * (xz - wy);
    result.E[9] = 2.0f * (yz + wx);
    result.E[10] = 1.0f - 2.0f * (x2 + y2);
    result.E[11] = 0.0f;

    result.E[12] = 0.0f;
    result.E[13] = 0.0f;
    result.E[14] = 0.0f;
    result.E[15] = 1.0f;

    return result;
    
}

float4 eulerAnglesToQuaternion(float y, float x, float z) {
    // Convert degrees to radians
    y = (y / 360.0f) * TAU32;
    x = (x / 360.0f) * TAU32;
    z = (z / 360.0f) * TAU32;

    // Half angles
    float cy = cosf(y * 0.5f);
    float sy = sinf(y * 0.5f);
    float cx = cosf(x * 0.5f);
    float sx = sinf(x * 0.5f);
    float cz = cosf(z * 0.5f);
    float sz = sinf(z * 0.5f);

    // Combine in Y (yaw), X (pitch), Z (roll) order
    float xq = sx * cy * cz + cx * sy * sz;
    float yq = cx * sy * cz - sx * cy * sz;
    float zq = cx * cy * sz - sx * sy * cz;
    float wq = cx * cy * cz + sx * sy * sz;

    return make_float4(xq, yq, zq, wq);
}

float4 inverseQuaternion(float4 q) {
    return make_float4(-q.x, -q.y, -q.z, q.w);
}

float4 slerp(float4 q1, float4 q2, float t) {
    // Normalize the quaternions to ensure they're unit quaternions
    q1 = easyMath_normalizeQuaternion(q1);
    q2 = easyMath_normalizeQuaternion(q2);

    // Compute the dot product
    float dot = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

    // If the dot product is negative, negate one quaternion to take the shorter path
    if (dot < 0.0f) {
        q2.x = -q2.x;
        q2.y = -q2.y;
        q2.z = -q2.z;
        q2.w = -q2.w;
        dot = -dot; // Update dot product
    }

    // If the quaternions are very close, linear interpolation can be used
    if (dot > 0.9995f) {
        float4 result;
        result.x = q1.x + t * (q2.x - q1.x);
        result.y = q1.y + t * (q2.y - q1.y);
        result.z = q1.z + t * (q2.z - q1.z);
        result.w = q1.w + t * (q2.w - q1.w);
        return easyMath_normalizeQuaternion(result); // Normalize result
    }

    // Calculate the angle between the quaternions
    float theta_0 = acosf(dot); // theta_0 = angle between q1 and q2
    float theta = theta_0 * t;  // theta = angle to interpolate

    // Compute the orthogonal vector (the axis of rotation)
    float4 q2_perp;
    q2_perp.x = q2.x - dot * q1.x;
    q2_perp.y = q2.y - dot * q1.y;
    q2_perp.z = q2.z - dot * q1.z;
    q2_perp.w = q2.w - dot * q1.w;
    q2_perp = easyMath_normalizeQuaternion(q2_perp); // Normalize the perpendicular vector

    // Calculate the final quaternion
    float4 result;
    result.x = q1.x * cosf(theta) + q2_perp.x * sinf(theta);
    result.y = q1.y * cosf(theta) + q2_perp.y * sinf(theta);
    result.z = q1.z * cosf(theta) + q2_perp.z * sinf(theta);
    result.w = q1.w * cosf(theta) + q2_perp.w * sinf(theta);

    return result; // Return the interpolated quaternion
}

float4 multQuaternion(float4 q, float4 multiplier) {
	float4 result = {};
    result.w = q.w*multiplier.w - q.x*multiplier.x -
        q.y*multiplier.y - q.z*multiplier.z;
    result.x = q.w*multiplier.x + q.x*multiplier.w +
        q.y*multiplier.z - q.z*multiplier.y;
	result.y = q.w*multiplier.y + q.y*multiplier.w +
		q.z*multiplier.x - q.x*multiplier.z;
	result.z = q.w*multiplier.z + q.z*multiplier.w +
		q.x*multiplier.y - q.y*multiplier.x;
	return result;
}

float4 integrateAngularVelocity(const float4 q, const float3 angularVelocity, float dt) {
	float4 result = q;

    // Quaternion representation of angular velocity
    float4 omega = make_float4(angularVelocity.x*dt, angularVelocity.y*dt, angularVelocity.z*dt, 0);

	omega = multQuaternion(q, omega);

	result.x += 0.5f*omega.x;
	result.y += 0.5f*omega.y;
	result.z += 0.5f*omega.z;
	result.w += 0.5f*omega.w;

    // // Normalize quaternion
    float magnitude = sqrt(result.w * result.w + result.x * result.x + result.y * result.y + result.z * result.z);
    result.w /= magnitude;
    result.x /= magnitude;
    result.y /= magnitude;
    result.z /= magnitude;

	return result;
}


float16 sqt_to_float16(float4 q, float3 scale, float3 pos) {
    float16 result = quaternionToMatrix(q);
	result = float16_scale(result, scale);
	result = float16_multiply(float16_set_pos(float16_identity(), pos), result);
    return result;
}



