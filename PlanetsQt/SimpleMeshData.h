#ifndef _SIMPLE_MESH_DATA_
#define _SIMPLE_MESH_DATA_

class Noise;

class SimpleMeshData
{
public:
    SimpleMeshData(Noise *pNoise);
    ~SimpleMeshData();

    void dump() const;

    const int *getColors() const                { return m_pColors; }
    const int *getIndices() const               { return m_pIndices; }
    const float *getVertices() const            { return m_pVertices; }
    int getNumberOfIndices() const              { return m_NumberOfIndices; }
    int getNumberOfVertices() const             { return m_NumberOfVertices; }

    void generateMeshForTime(float fTime);

protected:


private:
    void setupStaticArrays();

    int m_NumberOfVertices;
    int m_NumberOfIndices;

    int m_NumberInRowX;
    int m_NumberInRowY;

    //vertices
    float *m_pVertices;

    //colors
    int *m_pColors;

    //indices
    int *m_pIndices;

    Noise *m_pNoise;
};

#endif
