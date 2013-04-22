#pragma once

#include <float.h>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/quaternion.hpp>

NS_CH_BEG

typedef glm::detail::tvec2<int> Point;
typedef glm::vec3 Point3;

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::vec3 Normal;

typedef glm::vec3 Color3;
typedef glm::vec4 Color4;
typedef glm::vec2 Texcoord;

typedef glm::mat2 Matrix2;
typedef glm::mat3 Matrix3;
typedef glm::mat4 Matrix4;

typedef glm::mat3 Rotation;
typedef glm::quat Quaternion;

// index triangle
typedef glm::detail::tvec3<uint16> Triangle;

using std::min;
using std::max;


#ifdef CH_PLATFORM_WINDOWS
	#define isnan _isnan
	#define isinf(f) (!_finite((f)))
#else
	#define isnan
	#define isinf(f)
#endif


#ifndef INFINITY
#define INFINITY FLT_MAX
#endif

#ifdef CH_PLATFORM_WINDOWS
#pragma warning(disable:4244) 
#endif

namespace Math
{
	const double PI = 3.14159265358979323846;
	const double INV_PI = 0.31830988618379067154;
	const double INV_TWOPI = 0.15915494309189533577;
	const double INV_FOURPI= 0.07957747154594766788f;

	const Vector3 vXAxis(1.0f,0,0);
	const Vector3 vYAxis(0,1.0f,0);
	const Vector3 vZAxis(0,0,1.0f);
	
	const Matrix4 mIdentity4(1.0f);
	
	// Global Inline Functions
	inline float Lerp(float t, float v1, float v2) {
		return (1.f - t) * v1 + t * v2;
	}

	inline float Clamp(float val, float low, float high) {
		if (val < low) return low;
		else if (val > high) return high;
		else return val;
	}


	inline int Clamp(int val, int low, int high) {
		if (val < low) return low;
		else if (val > high) return high;
		else return val;
	}


	inline int Mod(int a, int b) {
		int n = int(a/b);
		a -= n*b;
		if (a < 0) a += b;
		return a;
	}


	inline float Radians(float deg) {
		return ((float)PI/180.f) * deg;
	}


	inline float Degrees(float rad) {
		return (180.f/(float)PI) * rad;
	}


	inline float Log2(float x) {
		static float invLog2 = 1.f / logf(2.f);
		return logf(x) * invLog2;
	}


	inline int Floor2Int(float val);
	inline int Log2Int(float v) {
		return Floor2Int(Log2(v));
	}


	inline bool IsPowerOf2(int v) {
		return (v & (v - 1)) == 0;
	}

	inline uint32 RoundUpPow2(uint32 v) {
		v--;
		v |= v >> 1;    v |= v >> 2;
		v |= v >> 4;    v |= v >> 8;
		v |= v >> 16;
		return v+1;
	}


	inline int Floor2Int(float val) {
		return (int)floorf(val);
	}


	inline int Round2Int(float val) {
		return Floor2Int(val + 0.5f);
	}


	inline int Float2Int(float val) {
		return (int)val;
	}


	inline int Ceil2Int(float val) {
		return (int)ceilf(val);
	}

	inline bool Quadratic(float A, float B, float C, float *t0, float *t1) {
		// Find quadratic discriminant
		float discrim = B * B - 4.f * A * C;
		if (discrim <= 0.) return false;
		float rootDiscrim = sqrtf(discrim);

		// Compute quadratic _t_ values
		float q;
		if (B < 0) q = -.5f * (B - rootDiscrim);
		else       q = -.5f * (B + rootDiscrim);
		*t0 = q / A;
		*t1 = C / q;
		if (*t0 > *t1) swap(*t0, *t1);
		return true;
	}


	inline bool HasNaNs(const Vector3 &v)
	{
		//return isnan(v[0]) || isnan(v[1]) || isnan(v[2]);
		return false;
	}

	inline bool HasNaNs(const Vector2 &v)
	{
		//return isnan(v[0]) || isnan(v[1]);
		return false;
	}

	inline float DistanceSquared(const Point3 &p1, const Point3 &p2) 
	{
		Vector3 v = p1 - p2;
		return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	}

	inline float Distance(const Point3 &v1,const Point3 &v2)
	{
		return glm::distance(v1,v2);
	}

	inline float Dot(const Vector3 &v1, const Vector3 &v2) 
	{
		CH_ASSERT(!HasNaNs(v1) && !HasNaNs(v2));
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}


	inline float AbsDot(const Vector3 &v1, const Vector3 &v2) 
	{
		CH_ASSERT(!HasNaNs(v1) && !HasNaNs(v2));
		return fabsf(Dot(v1, v2));
	}


	inline Vector3 Cross(const Vector3 &v1, const Vector3 &v2) 
	{
		CH_ASSERT(!HasNaNs(v1) && !HasNaNs(v2));
		double v1x = v1.x, v1y = v1.y, v1z = v1.z;
		double v2x = v2.x, v2y = v2.y, v2z = v2.z;
		return Vector3((v1y * v2z) - (v1z * v2y),
			(v1z * v2x) - (v1x * v2z),
			(v1x * v2y) - (v1y * v2x));
	}

	inline void CoordinateSystem(const Vector3 &v1, Vector3 *v2, Vector3 *v3) 
	{
		if (fabsf(v1.x) > fabsf(v1.y)) {
			float invLen = 1.f / sqrtf(v1.x*v1.x + v1.z*v1.z);
			*v2 = Vector3(-v1.z * invLen, 0.f, v1.x * invLen);
		}
		else {
			float invLen = 1.f / sqrtf(v1.y*v1.y + v1.z*v1.z);
			*v2 = Vector3(0.f, v1.z * invLen, -v1.y * invLen);
		}
		*v3 = Cross(v1, *v2);
	}


	inline Vector3 Faceforward(const Vector3 &v, const Vector3 &v2) {
		return (Dot(v, v2) < 0.f) ? -v : v;
	}

	inline Vector3 SphericalDirection(float sintheta,float costheta, float phi) 
	{
		return Vector3(sintheta * cosf(phi), sintheta * sinf(phi), costheta);
	}

	inline Vector3 SphericalDirection(float sintheta, float costheta,float phi, 
		const Vector3 &x,const Vector3 &y, const Vector3 &z) 
	{
		return sintheta * cosf(phi) * x +
			sintheta * sinf(phi) * y + costheta * z;
	}


	inline float SphericalTheta(const Vector3 &v) 
	{
		return acosf(Clamp(v.z, -1.f, 1.f));
	}


	inline float SphericalPhi(const Vector3 &v) 
	{
		float p = atan2f(v.y, v.x);
		return (p < 0.f) ? p + 2.f*PI : p;
	}

}

string ToString(const Matrix4 &m);
string ToString(const Rotation &m);
string ToString(const Vector3 &v);
string ToString(const Vector4 &v);

inline std::ostream &operator<<(std::ostream &out,const Vector3 &v)
{
	out<<ToString(v);
	return out;
}

inline std::ostream &operator<<(std::ostream &out,const Vector4 &v)
{
	out<<ToString(v);
	return out;
}

inline std::ostream &operator<<(std::ostream &out, const Matrix4 &m)
{
	out<<ToString(m);
	return out;
}

inline std::ostream &operator<<(std::ostream &out, const Rotation &m)
{
	out<<ToString(m);
	return out;
}

struct Rect
{
	int x,y;
	int width,height;
public:
	Rect():x(0),y(0),width(0),height(0){}
	Rect(int _x,int _y,int _weight,int _height):x(_x),y(_y),width(_weight),height(_height){}
};

class Ray {
public:
	// Ray Public Methods
	Ray() : mint(0.f), maxt(INFINITY), time(0.f), depth(0) { }
	Ray(const Point3 &origin, const Vector3 &direction,
		float start, float end = INFINITY, float t = 0.f, int d = 0)
		: o(origin), d(direction), mint(start), maxt(end), time(t), depth(d) { }
	Ray(const Point3 &origin, const Vector3 &direction, const Ray &parent,
		float start, float end = INFINITY)
		: o(origin), d(direction), mint(start), maxt(end),
		time(parent.time), depth(parent.depth+1) { }
	Point3 operator()(float t) const { return o + d * t; }

	// Ray Public Data
	Point3 o;
	Vector3 d;
	mutable float mint, maxt;
	float time;
	int depth;
};


class BBox 
{
public:
	// BBox Public Methods
	BBox() {
		pMin = Point3( INFINITY,  INFINITY,  INFINITY);
		pMax = Point3(-INFINITY, -INFINITY, -INFINITY);
	}
	BBox(const Point3 &p) : pMin(p), pMax(p) { }
	BBox(const Point3 &p1, const Point3 &p2) 
	{
		pMin = Point3(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
		pMax = Point3(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
	}
	friend BBox Union(const BBox &b, const Point3 &p);
	friend BBox Union(const BBox &b, const BBox &b2);
	
	bool Overlaps(const BBox &b) const 
	{
		bool x = (pMax.x >= b.pMin.x) && (pMin.x <= b.pMax.x);
		bool y = (pMax.y >= b.pMin.y) && (pMin.y <= b.pMax.y);
		bool z = (pMax.z >= b.pMin.z) && (pMin.z <= b.pMax.z);
		return (x && y && z);
	}
	
	bool Inside(const Point3 &pt) const 
	{
		return (pt.x >= pMin.x && pt.x <= pMax.x &&
			pt.y >= pMin.y && pt.y <= pMax.y &&
			pt.z >= pMin.z && pt.z <= pMax.z);
	}
	
	void Expand(float delta) 
	{
		pMin -= Vector3(delta, delta, delta);
		pMax += Vector3(delta, delta, delta);
	}
	float SurfaceArea() const 
	{
		Vector3 d = pMax - pMin;
		return 2.f * (d.x * d.y + d.x * d.z + d.y * d.z);
	}
	float Volume() const 
	{
		Vector3 d = pMax - pMin;
		return d.x * d.y * d.z;
	}
	
	int MaximumExtent() const 
	{
		Vector3 diag = pMax - pMin;
		if (diag.x > diag.y && diag.x > diag.z)
			return 0;
		else if (diag.y > diag.z)
			return 1;
		else
			return 2;
	}
	const Point3 &operator[](int i) const;
	Point3 &operator[](int i);
	
	Point3 Lerp(float tx, float ty, float tz) const 
	{
		return Point3(Math::Lerp(tx, pMin.x, pMax.x), Math::Lerp(ty, pMin.y, pMax.y),
			Math::Lerp(tz, pMin.z, pMax.z));
	}
	Vector3 Offset(const Point3 &p) const {
		return Vector3((p.x - pMin.x) / (pMax.x - pMin.x),
			(p.y - pMin.y) / (pMax.y - pMin.y),
			(p.z - pMin.z) / (pMax.z - pMin.z));
	}
	
	void BoundingSphere(Point3 *c, float *rad) const;
	
	bool IntersectP(const Ray &ray, float *hitt0 = NULL, float *hitt1 = NULL) const;

	bool operator==(const BBox &b) const {
		return b.pMin == pMin && b.pMax == pMax;
	}
	bool operator!=(const BBox &b) const {
		return b.pMin != pMin || b.pMax != pMax;
	}

	// BBox Public Data
	Point3 pMin, pMax;
};


class Transform
{
public:
	Transform():m_scale(1.0f,1.0f,1.0f){}
	Transform( const Vector3 &t,const Quaternion &r, const Vector3 &s):
	m_scale(s),m_translate(t)
	{
		m_rotation = glm::mat3_cast(r);
	}

	Transform(const Vector3 &t,const Rotation &r, const Vector3 &s):
	m_rotation(r),m_scale(s),m_translate(t) {}

	Transform(const Matrix4 &m)
	{
		Decompose(m,&m_translate,&m_rotation,&m_scale);
	}

	static Transform IDENTITY;

	void SetRotation(const Quaternion &q) { m_rotation = glm::mat3_cast(q); }
	void SetRotation(const Rotation &m) { m_rotation = m; }
	void SetScales(const Vector3 &v) 
	{ CH_ASSERT(m_scale.x!=.0f && m_scale.y!=.0f && m_scale.z !=.0f); m_scale = v; }

	void SetTranslate(const Vector3 &v) { m_translate = v; }

	static void Decompose(const Matrix4 &m, Vector3 *T, Rotation *R, Vector3 *S);

	const Rotation &GetRotation() const { return m_rotation; }

	Quaternion GetQuaternion() const { return glm::quat_cast(m_rotation); }

	const Vector3 &GetScale() const { return m_scale; }

	const Vector3 &GetTranslate() const { return m_translate; }

	inline Matrix4 GetMatrix() const ;

	inline Normal TransfromNormal(const Normal &n) const;
	inline Normal TransfromNormal(const Transform &nInv,const Normal &n) const;

	string ToString() const;
	
	inline void Inverse();

	inline Vector3 operator * (const Vector3 &v) const;
	inline void operator()(const Vector3 &v,Vector3 *pv) const;
	inline BBox operator*(const BBox &b) const;
	inline Ray operator*(const Ray &r)const;
	inline Transform operator*(const Transform &B)const;

public:
	Rotation m_rotation;
	Vector3 m_scale;
	Vector3 m_translate;
};

namespace Math
{
	inline Rotation Transpose(const Rotation rot)
	{
		return glm::transpose(rot);
	}


	inline void Inverse(const Transform &t,Transform *pOut)
	{
		pOut->m_scale.x= 1.0f/t.m_scale.x;
		pOut->m_scale.y = 1.0f/t.m_scale.y;
		pOut->m_scale.z = 1.0f/t.m_scale.z;

		pOut->m_rotation = glm::transpose(t.m_rotation);
		pOut->m_translate = - (pOut->m_rotation * t.m_translate);
	}

}




class QsTransform
{
public:

};


inline Vector3 Transform::operator*( const Vector3 &v ) const
{
	Vector3 vOut;
	vOut.x = m_scale.x * v.x;
	vOut.y = m_scale.y * v.y;
	vOut.z = m_scale.z * v.z;

	vOut = m_rotation * vOut;

	vOut += m_translate;
	return vOut;
}

inline void Transform::operator()( const Vector3 &v,Vector3 *pv ) const
{
	pv->x = m_scale.x * v.x;
	pv->y = m_scale.y * v.y;
	pv->z = m_scale.z * v.z;

	*pv = m_rotation * (*pv);

	(*pv) += m_translate;
}

inline BBox Transform::operator*( const BBox &b ) const
{
	const Transform &M = *this;
	BBox ret(        M*Point3(b.pMin.x, b.pMin.y, b.pMin.z));
	ret = Union(ret, M * Point3(b.pMax.x, b.pMin.y, b.pMin.z));
	ret = Union(ret, M * Point3(b.pMin.x, b.pMax.y, b.pMin.z));
	ret = Union(ret, M * Point3(b.pMin.x, b.pMin.y, b.pMax.z));
	ret = Union(ret, M * Point3(b.pMin.x, b.pMax.y, b.pMax.z));
	ret = Union(ret, M * Point3(b.pMax.x, b.pMax.y, b.pMin.z));
	ret = Union(ret, M * Point3(b.pMax.x, b.pMin.y, b.pMax.z));
	ret = Union(ret, M * Point3(b.pMax.x, b.pMax.y, b.pMax.z));
	return ret;

}

inline Ray Transform::operator*( const Ray &r ) const
{
	Ray ret;
	(*this)(r.o,&ret.o);
	(*this)(r.d,&ret.d);
	return ret;
}

inline void Transform::Inverse()
{
	m_scale.x= 1.0f/m_scale.x;
	m_scale.y = 1.0f/m_scale.y;
	m_scale.z = 1.0f/m_scale.z;

	m_rotation = Math::Transpose(m_rotation);
	m_translate = - (m_rotation * m_translate);
}


inline Transform Transform::operator*( const Transform &B ) const
{ 
	Transform C;
	const Transform &A = *this;
	C.m_translate = A.m_translate + A.m_rotation * B.m_translate;
	C.m_rotation = A.m_rotation * B.m_rotation;

	C.m_scale.x = A.m_scale.x * B.m_scale.x;
	C.m_scale.y = A.m_scale.y * B.m_scale.y;
	C.m_scale.z = A.m_scale.z * B.m_scale.z;
	return C;
}


inline Matrix4 Transform::GetMatrix() const
{
	Matrix4 m(m_rotation);

	Matrix4 mScale;
	mScale[0][0] = m_scale.x;
	mScale[1][1] = m_scale.y;
	mScale[2][2] = m_scale.z;
	m = m*mScale;

	m[3].x = m_translate.x;
	m[3].y = m_translate.y;
	m[3].z = m_translate.z;

	return m;
}


inline Normal Transform::TransfromNormal( const Normal &n ) const 
{
	return Normal(0,0,0);
}

inline Normal Transform::TransfromNormal( const Transform &nInv,const Normal &n ) const
{
	return Normal(0,0,0);
}


NS_CH_END
