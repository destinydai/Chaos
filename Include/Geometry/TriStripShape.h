#pragma once


NS_CH_BEG

class TriStripShape : public MeshShape
{
	CH_OBJ_TYPE_DECL(TriStripShape,MeshShape)
protected:
	TriStripShape(void);
public:
	virtual ~TriStripShape(void);
public:
	static Reference<TriStripShape> Create();

	inline void AddStrip(const vector<uint16> &strip);
	inline void ClearStrips();
	uint16 GetStripCount() { return m_nStrips; }
	inline uint GetTotalStripIndexCount();
	const vector<vector<uint16> > &GetStrips() const { return m_strips; }

protected:
	//number of tripes
	uint16 m_nStrips;
	//the number of vertex per strip
	vector<uint16> m_stripLengths;
	//the index of the vertex array
	vector< vector<uint16> > m_strips;
};


inline void TriStripShape::AddStrip( const vector<uint16> &strip )
{
	m_strips.push_back(strip);
	m_stripLengths.push_back((uint16)strip.size());
	m_nStrips = m_strips.size();
}

inline void TriStripShape::ClearStrips()
{
	m_strips.clear();
	m_nStrips = 0;
	m_stripLengths.clear();
}

inline uint TriStripShape::GetTotalStripIndexCount()
{
	uint nCount = 0;
	for(uint i=0; i<m_strips.size(); ++i)
	{
		nCount += m_strips[i].size();
	}
	return nCount;
}


NS_CH_END