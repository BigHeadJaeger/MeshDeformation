#include "MeshObject.h"

void MeshObject::readObjFile(string fileName)
{
	meshData.mesh.request_vertex_normals();

	
	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(meshData.mesh, fileName), opt)
	{
		cout << "init mesh failed" << endl;
	}

	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		meshData.mesh.request_face_normals();
		meshData.mesh.update_normals();
		meshData.mesh.release_face_normals();

	}

	if (!opt.check(OpenMesh::IO::Options::VertexTexCoord))
		meshData.providedTex = false;
	else
	{
		meshData.mesh.request_vertex_texcoords2D();
	}


}
