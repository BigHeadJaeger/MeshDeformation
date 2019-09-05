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

bool BoundingBox::RayDetect(vec3 dir, vec3 pos)
{
	float t;
	vec3 hitPoint;
	//与box的求交相似

	//x方向上的相交情况
	if (dir.x != 0)
	{
		if (dir.x > 0)
			t = (minPos.x - pos.x) / dir.x;
		else
			t = (maxPos.x - pos.x) / dir.x;

		if (t > 0)
		{
			hitPoint = pos + dir * t;
			if ((hitPoint.y > minPos.y) && (hitPoint.y < maxPos.y) && (hitPoint.z > minPos.z) && (hitPoint.z < maxPos.z))
				return true;
		}
	}

	//y方向
	if (dir.y != 0)
	{
		if (dir.y > 0)
			t = (minPos.y - pos.y) / dir.y;
		else
			t = (maxPos.y - pos.y) / dir.y;

		if (t > 0)
		{
			hitPoint = pos + dir * t;
			if ((hitPoint.x < maxPos.x) && (hitPoint.x > minPos.x) && (hitPoint.z < maxPos.z) && (hitPoint.z > minPos.z))
				return true;
		}
	}

	//z方向
	if (dir.z != 0)
	{
		if (dir.z > 0)
			t = (minPos.z - pos.z) / dir.z;
		else
			t = (maxPos.z - pos.z) / dir.z;

		if (t > 0)
		{
			hitPoint = pos + dir * t;
			if ((hitPoint.x < maxPos.x) && (hitPoint.x > minPos.x) && (hitPoint.y < maxPos.y) && (hitPoint.y > minPos.y))
				return true;
		}
	}

	return false;

}

