#include "BoundingVolume.h"

void BoundingBox::UpdatePos(Transform& trans)
{
	mat4 world;
	world = translate(mat4(1.0), trans.position);
	world = scale(world, trans.scaler);
	if (trans.rotation.x != 0)
		world = rotate(world, trans.rotation.x, vec3(1.0, 0.0, 0.0));
	if (trans.rotation.y != 0)
		world = rotate(world, trans.rotation.y, vec3(0.0, 1.0, 0.0));
	if (trans.rotation.z != 0)
		world = rotate(world, trans.rotation.z, vec3(0.0, 0.0, 1.0));

	vec4 res = world * vec4(maxPos, 1.0);
	maxPos = vec3(res.x, res.y, res.z);

	res= world * vec4(minPos, 1.0);
	minPos = vec3(res.x, res.y, res.z);
}

void BoundingBox::Init(MeshData& meshData)
{
	//attachObj = obj;

	for (Mesh::VertexIter v_it = meshData.mesh.vertices_begin(); v_it != meshData.mesh.vertices_end(); v_it++)
	{
		float x, y, z;
		x = meshData.mesh.point(*v_it).data()[0];
		y = meshData.mesh.point(*v_it).data()[1];
		z = meshData.mesh.point(*v_it).data()[2];

		if (x > maxPos.x)maxPos.x = x;
		if (y > maxPos.y)maxPos.y = y;
		if (z > maxPos.z)maxPos.z = z;

		if (x < minPos.x)minPos.x = x;
		if (y < minPos.y)minPos.y = y;
		if (z < minPos.z)minPos.z = z;
	}

}

