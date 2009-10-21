#include "cylinder.h"

const Index CYLINDER_EDGES_PER_BASE = 20;
const Index CYLINDER_EDGES_PER_HEIGHT = 1;

extern const Index CYLINDER_VERTICES_COUNT = CYLINDER_EDGES_PER_BASE*(CYLINDER_EDGES_PER_HEIGHT + 1);
extern const DWORD CYLINDER_INDICES_COUNT = 2*CYLINDER_EDGES_PER_BASE*CYLINDER_EDGES_PER_HEIGHT // indices per CYLINDER_EDGES_PER_HEIGHT levels
                                          + 2*( CYLINDER_EDGES_PER_HEIGHT - 1 );  // plus two triangles to move from one level to another

void cylinder( D3DXVECTOR3 base_center, float radius, float height,
                Vertex *res_vertices, Index *res_indices)
// Writes data into arrays given as `res_vertices' and `res_indices',
{
    _ASSERT(res_vertices != NULL);
    _ASSERT(res_indices != NULL);

    Index vertex = 0; // current vertex
    DWORD index = 0; // current index

    const float STEP_ANGLE = 2*D3DX_PI/CYLINDER_EDGES_PER_BASE;
    const float STEP_UP = height/CYLINDER_EDGES_PER_HEIGHT;
    
    for( Index level = 0; level <= CYLINDER_EDGES_PER_HEIGHT; ++level )
    {
        for( Index step = 0; step < CYLINDER_EDGES_PER_BASE; ++step )
        {
            res_vertices[vertex] = Vertex( base_center
                                         + D3DXVECTOR3( radius*cos(step*STEP_ANGLE),
                                                        radius*sin(step*STEP_ANGLE),
                                                        level*STEP_UP)
                                          );
            if( level != 0 )
            {
                res_indices[index++] = vertex - CYLINDER_EDGES_PER_BASE; // from previous level
                res_indices[index++] = vertex;                           // from current level
            }
            ++vertex;
        }
    }
}
