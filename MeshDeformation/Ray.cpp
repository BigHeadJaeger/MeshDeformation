#include "Ray.h"

void Ray::PickRayInit(float mouseX, float mouseY, Camera& camera)
{
	//将左上(0,0)右下(width,height)的坐标系转换到左上(-1,1)，右下(1,-1)的坐标系中
	direction.x = (2 * mouseX) / WIDTH - 1.0;
	direction.y = 1.0 - (2 * mouseY) / HEIGHT;
	direction.z = 1.0;

	//将射线转换到世界坐标之下
	vec4 tempRay = vec4(direction, 1.0);		//vec4为了增加齐次坐标位
	tempRay = inverse(camera.view) * inverse(camera.pro) * tempRay;
	if (tempRay.w != 0)
		tempRay /= tempRay.w;
	direction = vec3(tempRay.x, tempRay.y, tempRay.z);

	position = camera.eyePos;
}

bool Ray::BoundingHit(Bounding& bounding)
{
	return bounding.RayDetect(direction, position);
}
