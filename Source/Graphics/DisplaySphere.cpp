#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(DisplaySphere,DisplayObject)

DisplaySphere::DisplaySphere( float radius ):m_radius(radius)
{

}

DisplaySphere::~DisplaySphere( void )
{

}

void DisplaySphere::Draw(const  Transform *pTransform )
{
	CH_ASSERT(false);
}


int  DisplaySphere::GenSphere ( int numSlices, float radius, float **vertices, float **normals, float **texCoords, uint16 **indices )
{
	int i;
	int j;
	int numParallels = numSlices / 2;
	int numVertices = ( numParallels + 1 ) * ( numSlices + 1 );
	int numIndices = numParallels * numSlices * 6;
	float angleStep = (2.0f * Math::PI) / ((float) numSlices);

	// Allocate memory for buffers
	if ( vertices != NULL )
		*vertices = (float*)malloc ( sizeof(float) * 3 * numVertices );

	if ( normals != NULL )
		*normals = (float*)malloc ( sizeof(float) * 3 * numVertices );

	if ( texCoords != NULL )
		*texCoords = (float*)malloc ( sizeof(float) * 2 * numVertices );

	if ( indices != NULL )
		*indices = (uint16*)malloc ( sizeof(uint16) * numIndices );

	for ( i = 0; i < numParallels + 1; i++ )
	{
		for ( j = 0; j < numSlices + 1; j++ )
		{
			int vertex = ( i * (numSlices + 1) + j ) * 3; 

			if ( vertices )
			{
				(*vertices)[vertex + 0] = radius * sinf ( angleStep * (float)i ) *
					sinf ( angleStep * (float)j );
				(*vertices)[vertex + 1] = radius * cosf ( angleStep * (float)i );
				(*vertices)[vertex + 2] = radius * sinf ( angleStep * (float)i ) *
					cosf ( angleStep * (float)j );
			}

			if ( normals )
			{
				(*normals)[vertex + 0] = (*vertices)[vertex + 0] / radius;
				(*normals)[vertex + 1] = (*vertices)[vertex + 1] / radius;
				(*normals)[vertex + 2] = (*vertices)[vertex + 2] / radius;
			}

			if ( texCoords )
			{
				int texIndex = ( i * (numSlices + 1) + j ) * 2;
				(*texCoords)[texIndex + 0] = (float) j / (float) numSlices;
				(*texCoords)[texIndex + 1] = ( 1.0f - (float) i ) / (float) (numParallels - 1 );
			}
		}
	}

	// Generate the indices
	if ( indices != NULL )
	{
		uint16 *indexBuf = (*indices);
		for ( i = 0; i < numParallels ; i++ ) 
		{
			for ( j = 0; j < numSlices; j++ )
			{
				*indexBuf++  = i * ( numSlices + 1 ) + j;
				*indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + j;
				*indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );

				*indexBuf++ = i * ( numSlices + 1 ) + j;
				*indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );
				*indexBuf++ = i * ( numSlices + 1 ) + ( j + 1 );
			}
		}
	}

	return numIndices;
}

Reference<DisplaySphere> DisplaySphere::Create( float radius )
{
	return Reference<DisplaySphere>(new DisplaySphere(radius));
}

NS_CH_END