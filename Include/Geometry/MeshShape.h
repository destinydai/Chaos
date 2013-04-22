#pragma once


NS_CH_BEG

class MeshShape : public Shape
{
	CH_OBJ_TYPE_DECL(MeshShape,Shape)
protected:
	MeshShape();
	virtual ~MeshShape();
public:
	inline uint16 GetVertexCount() const { return m_nVertex; }
	inline void SetVertices(const vector<Vector3> &vertices);
	inline vector<Vector3> &GetVertices() { return m_vertices; }

	inline boolean HasNormals() const { return m_bNormals; }
	inline void SetNormals(const vector<Vector3> &normals);
	inline vector<Vector3> &GetNormals() { return m_normals; } 

	inline uint16 GetTexCoordsCount() const { return m_nTexCoords; }
	inline void AddTexCoords(const vector<Vector2> &texCoords);
	inline vector< vector<Vector2> > &GetTexCoords() { return m_texCoords; }
	inline void ClearTexCoords();

	virtual BBox ObjectBindBox() const{ return m_objectBindBox; }

	virtual bool IntersectP(const Ray &ray) const;

	void SetObjectBindBox(BBox &box) { m_objectBindBox = box; }

	virtual void ComputeBindBox();
private:
	//number of vertex
	uint16 m_nVertex;
	//the vertex array
	vector<Vector3> m_vertices;
	//has normal
	boolean m_bNormals;
	//the normal data array
	vector<Vector3> m_normals;
	//the texture coordinate set
	uint16 m_nTexCoords;
	vector< vector<Vector2> > m_texCoords;
	//bind box 
	BBox m_objectBindBox;
};


inline void MeshShape::SetVertices( const vector<Vector3> &vertices )
{
	m_vertices = vertices;
	m_nVertex = m_vertices.size();
}

inline void MeshShape::SetNormals( const vector<Vector3> &normals )
{
	m_normals = normals;
	m_bNormals = m_normals.size()!=0;
}

inline void MeshShape::AddTexCoords( const vector<Vector2> &texCoords )
{
	m_texCoords.push_back(texCoords);
	m_nTexCoords = m_texCoords.size();
}

inline void MeshShape::ClearTexCoords()
{
	m_texCoords.clear();
	m_nTexCoords = 0;
}

NS_CH_END