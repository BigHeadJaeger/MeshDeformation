#include "Ray.h"

void Ray::PickRayInit(float mouseX, float mouseY, Camera& camera)
{
	//������(0,0)����(width,height)������ϵת��������(-1,1)������(1,-1)������ϵ��
	direction.x = (2 * mouseX) / WIDTH - 1.0;
	direction.y = 1.0 - (2 * mouseY) / HEIGHT;
	direction.z = 1.0;

	//������ת������������֮��
	vec4 tempRay = vec4(direction, 1.0);		//vec4Ϊ�������������λ
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
