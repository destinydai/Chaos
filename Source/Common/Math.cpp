#include "stdafx.h"
#include <sstream>

using namespace std;

NS_CH_BEG


/************************* Box ****************/


// BBox Method Definitions
BBox Union(const BBox &b, const Point3 &p) {
	BBox ret = b;
	ret.pMin.x = min(b.pMin.x, p.x);
	ret.pMin.y = min(b.pMin.y, p.y);
	ret.pMin.z = min(b.pMin.z, p.z);
	ret.pMax.x = max(b.pMax.x, p.x);
	ret.pMax.y = max(b.pMax.y, p.y);
	ret.pMax.z = max(b.pMax.z, p.z);
	return ret;
}


BBox Union(const BBox &b, const BBox &b2) {
	BBox ret;
	ret.pMin.x = min(b.pMin.x, b2.pMin.x);
	ret.pMin.y = min(b.pMin.y, b2.pMin.y);
	ret.pMin.z = min(b.pMin.z, b2.pMin.z);
	ret.pMax.x = max(b.pMax.x, b2.pMax.x);
	ret.pMax.y = max(b.pMax.y, b2.pMax.y);
	ret.pMax.z = max(b.pMax.z, b2.pMax.z);
	return ret;
}


void BBox::BoundingSphere(Point3 *c, float *rad) const 
{
	*c = .5f * pMin + .5f * pMax;
	*rad = Inside(*c) ? Math::Distance(*c, pMax) : 0.f;
}


bool BBox::IntersectP(const Ray &ray, float *hitt0,float *hitt1) const 
{
	float t0 = ray.mint, t1 = ray.maxt;
	for (int i = 0; i < 3; ++i) 
	{
		// Update interval for _i_th bounding box slab
		float invRayDir = 1.f / ray.d[i];
		float tNear = (pMin[i] - ray.o[i]) * invRayDir;
		float tFar  = (pMax[i] - ray.o[i]) * invRayDir;

		// Update parametric interval from slab intersection $t$s
		if (tNear > tFar) swap(tNear, tFar);
		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar  < t1 ? tFar  : t1;
		if (t0 > t1) return false;
	}
	if (hitt0) *hitt0 = t0;
	if (hitt1) *hitt1 = t1;
	return true;
}

/****************** Transform **********************/ 

string Transform::ToString() const
{
	std::ostringstream out;
	out<<"Scales:"<<m_scale<<endl;
	out<<"Translate:"<<m_translate<<endl;
	out<<"Rotation:"<<endl;
	out<<m_rotation;
	return out.str();
}

void Transform::Decompose( const Matrix4 &m, Vector3 *T, Rotation *R, Vector3 *S )
{
	*T = Vector3(m[3]);
	Rotation rotT;
	for ( int i = 0; i < 3; i++ ){
		for ( int j = 0; j < 3; j++ ){
			(*R)[i][j] = m[i][j];
			rotT[j][i] = m[i][j];
		}
	}
	Rotation mtx = (*R) * rotT;
	Vector3 scale3( sqrt(mtx[0][0]), sqrt(mtx[1][1]), sqrt(mtx[2][2]) );
	for ( int i = 0; i < 3; i++ ){
		for ( int j = 0; j < 3; j++ ){
			(*R)[i][j] /= scale3[i];
		}
	}

	//scale = (scale3[0] + scale3[1] + scale3[2]) / 3.0f;
	*S = scale3;
}

Transform Transform::IDENTITY;


string ToString( const Matrix4 &m )
{
	ostringstream out;
	out<<"[\n";
	for (int i = 0; i < 4; ++i) {
		out<<"  [ ";
		for (int j = 0; j < 4; ++j)  {
			out<<m[i][j];
			if (j != 3) out<<", ";
		}
		out<<" ]\n";
	} 
	out<<"] ";
	return out.str();
}


string ToString( const Rotation &m )
{
	ostringstream out;
	out<<"[\n";
	for (int i = 0; i < 3; ++i) 
	{
		out<<"  [ ";
		for (int j = 0; j < 3; ++j)  
		{
			out<<m[i][j];
			if (j != 3) out<<", ";
		}
		out<<" ]\n";
	} 
	out<<"] ";
	return out.str();
}


string ToString( const Vector3 &v )
{
	ostringstream out;
	out<<"["<<v[0]<<","<<v[1]<<","<<v[2]<<"]";
	return out.str();
}

string ToString( const Vector4 &v )
{
	ostringstream out;
	out<<"["<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]<<"]";
	return out.str();
}

NS_CH_END