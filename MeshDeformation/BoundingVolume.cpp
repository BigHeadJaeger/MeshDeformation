#include "BoundingVolume.h"

void BoundingBox::UpdatePos()
{
	mat4 world;
	world = translate(mat4(1.0), attachObj->GetTransform().position);
	world = scale(world, attachObj->GetTransform().scaler);
	if (attachObj->GetTransform().rotation.x != 0)
		world = rotate(world, attachObj->GetTransform().rotation.x, vec3(1.0, 0.0, 0.0));
	if (attachObj->GetTransform().rotation.y != 0)
		world = rotate(world, attachObj->GetTransform().rotation.y, vec3(0.0, 1.0, 0.0));
	if (attachObj->GetTransform().rotation.z != 0)
		world = rotate(world, attachObj->GetTransform().rotation.z, vec3(0.0, 0.0, 1.0));

	vec4 res = world * vec4(maxPos, 1.0);
	maxPos = vec3(res.x, res.y, res.z);

	res= world * vec4(minPos, 1.0);
	minPos = vec3(res.x, res.y, res.z);
}

void BoundingBox::Init(Object* obj)
{
	attachObj = obj;

	for (Mesh::VertexIter v_it = obj->GetMeshData().mesh.vertices_begin(); v_it != obj->GetMeshData().mesh.vertices_end(); v_it++)
	{
		float x, y, z;
		x = obj->GetMeshData().mesh.point(*v_it).data()[0];
		y = obj->GetMeshData().mesh.point(*v_it).data()[1];
		z = obj->GetMeshData().mesh.point(*v_it).data()[2];

		if (x > maxPos.x)maxPos.x = x;
		if (y > maxPos.y)maxPos.y = y;
		if (z > maxPos.z)maxPos.z = z;

		if (x < minPos.x)minPos.x = x;
		if (y < minPos.y)minPos.y = y;
		if (z < minPos.z)minPos.z = z;
	}

}

void Bounding::UpdatePos()
{
}
