#include <gl/glut.h>
#include <fstream>
#include <cmath>
using namespace std;
//3D Classes for Graphics
//@@@@@@@@@@@@@@@@@@ Point3 class @@@@@@@@@@@@@@@@
class Point3{ 
public: 
	float x,y,z;
	void set(float dx, float dy, float dz){x = dx; y = dy; z = dz;}
	void set(Point3& p){x = p.x; y = p.y; z = p.z;} 	
 Point3(float xx,     float yy, float zz){x = xx; y = yy; z = zz;}
	Point3(){x = y = z = 0;}
	void build4tuple(float v[])
	{// load 4-tuple with this color: v[3] = 1 for homogeneous
		v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
	}	
};
//@@@@@@@@@@@@@@@@@@ Vector3 class @@@@@@@@@@@@@@@@
class Vector3{ 
public: 
	float x,y,z;
	void set(float dx, float dy, float dz){ x = dx; y = dy; z = dz;} 
	void set(Vector3& v){ x = v.x; y = v.y; z = v.z;}
	void flip(){x = -x; y = -y; z = -z;} // reverse this vector
	void setDiff(Point3& a, Point3& b)//set to difference a - b
	{ x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}
	void normalize()//adjust this vector to unit length
	{		
		double sizeSq = x * x + y * y + z * z;
		if(sizeSq < 0.0000001)
		{
			//cerr << "\nnormalize() sees vector (0,0,0)!";
			return; // does nothing to zero vectors;
		}
		float scaleFactor = 1.0/(float)sqrt(sizeSq);
		x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
	}
	Vector3(float xx, float yy, float zz){x = xx; y = yy; z = zz;}
	Vector3(Vector3& v){x = v.x; y = v.y; z = v.z;}
	Vector3(){x = y = z = 0;} //default constructor
	Vector3 cross(Vector3 b) //return this cross b
	{
	   Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	   return c;
	}
	float dot(Vector3 b) // return this dotted with b
 {return x * b.x + y * b.y + z * b.z;}
};
//################# VertexID ###################
class VertexID{
	public:
		int vertIndex; // index of this vert in the vertex list
		int normIndex; // index of this vertex's normal
};
//#################### Face ##################
class Face{
  public:
	int nVerts; // number of vertices in this face
	VertexID * vert; // the list of vertex and normal indices
	Face() {nVerts = 0; vert = NULL;} // constructor
	~Face() {delete[] vert; nVerts = 0;} // destructor
};

class Mesh {
private:
	int numVerts;	// number of vertices in the mesh
	Point3* pt;	      // array of 3D vertices
	int numNorms;   // number of normal vectors for the mesh
	Vector3 *norm;    // array of normals 
	int numFaces; 	// number of faces in the mesh
	Face* face;	      // array of face data
public:
	int readFile(char *fileName);
	void Draw();
};

int Mesh::readFile(char *fileName)
{
	fstream infile;
	infile.open(fileName, ios::in);
	if(infile.fail()) return -1; // error - can't open file
	if(infile.eof())  return -1; // error - empty file
	infile >> numVerts >> numNorms >> numFaces;
	pt = new Point3[numVerts];
	norm = new Vector3[numNorms];
	face = new Face[numFaces];
	//check that enough memory was found:
	if( !pt || !norm || !face) return -1; // out of memory
	for (int p = 0; p < numVerts; p++) // read the vertices
	infile >> pt[p].x >> pt[p].y >> pt[p].z;
	for (int n = 0; n < numNorms; n++) // read the normals
	infile >> norm[n].x >> norm[n].y >> norm[n].z;
	for (int f = 0; f < numFaces; f++)// read the faces
	{
		infile >> face[f].nVerts;
		face[f].vert = new VertexID[face[f].nVerts];
		for(int i = 0; i < face[f].nVerts; i++) { // vertex list
			infile >> face[f].vert[i].vertIndex;
		}	
		for(int i = 0; i < face[f].nVerts; i++) { // normal list
		    infile >> face[f].vert[i].normIndex;
		}
	} 
	return 0; // success
} 

void Mesh::Draw() 
{
	for(int f = 0; f < numFaces; f++) // draw each face
	{
		glBegin(GL_POLYGON);
		//glBegin(GL_LINE_LOOP); // Draw wireframe
		for(int v = 0; v < face[f].nVerts; v++) // for each one..
		{
		  int in = face[f].vert[v].normIndex ; // index of this normal
		  int iv =  face[f].vert[v].vertIndex ; // index of this vertex
		  glNormal3f(norm[in].x, norm[in].y, norm[in].z);
		  glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		 }
		glEnd();
	}
}