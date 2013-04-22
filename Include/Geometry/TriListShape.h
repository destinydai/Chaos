#pragma once


NS_CH_BEG


class TriListShape : public MeshShape
{
	CH_OBJ_TYPE_DECL(TriListShape,MeshShape)
protected:
	TriListShape(void);
public:
	virtual ~TriListShape(void);
public:
	static Reference<TriListShape> Create();

	inline void AddTriangle(const Triangle &tri);
	inline void SetTriangles(const vector<Triangle> triangles);
	inline uint GetTriangleCount() { return m_triangles.size(); } 
	inline Triangle &GetTriangle(uint nIndex);
	inline vector<Triangle> &GetTriangleArray() { return m_triangles; }
private:
	//number of triangles
	uint m_nTriangles;
	//the index triangle data
	vector<Triangle> m_triangles;
};

inline void TriListShape::AddTriangle( const Triangle &tri )
{
	m_triangles.push_back(tri);
	m_nTriangles = m_triangles.size();
}

inline void TriListShape::SetTriangles( const vector<Triangle> triangles )
{
	m_triangles = triangles;
	m_nTriangles = m_triangles.size();
}

inline Triangle & TriListShape::GetTriangle( uint nIndex )
{
	CH_ASSERT(nIndex<m_triangles.size());
	return m_triangles[nIndex];
}

NS_CH_END