#include "Frustum.h"

Frustum::Frustum(FrustumData _data) : Entity(false)
{
	data = _data;

	for (int i = 0; i < FrustumPlanes::Length; i++)
	{
		planes.push_back(new FrustumPlane());
		addChild(dynamic_cast<Entity*>(planes[i]));
	}

	float horizontalFOV = data.verticalFOV * (data.width / data.height);

	//Plane setting
	//----------
	//Near & Far
	planes[FrustumPlanes::Near]->getTransform()->setPosition(transform->getPosition() + transform->getForward() * data.near);
	planes[FrustumPlanes::Near]->getTransform()->setScale(vec3(0.05f));
	planes[FrustumPlanes::Far]->getTransform()->setPosition(transform->getPosition() + transform->getForward() * data.far);
	planes[FrustumPlanes::Far]->getTransform()->rotate(0.0f, 180.0f, 0.0f);

	//Up & Down
	planes[FrustumPlanes::Up]->getTransform()->rotate(90.0f - data.verticalFOV / 2.0f, 0.0f, 0.0f);
	planes[FrustumPlanes::Down]->getTransform()->rotate(-90.0f + data.verticalFOV / 2.0f, 0.0f, 0.0f);
	vec3 up = planes[FrustumPlanes::Up]->getTransform()->getUp();
	vec3 down = planes[FrustumPlanes::Down]->getTransform()->getUp();
	planes[FrustumPlanes::Up]->getTransform()->translate(up * 5.0f);
	planes[FrustumPlanes::Down]->getTransform()->translate(down * -5.0f);

	//Right & Left
	planes[FrustumPlanes::Right]->getTransform()->rotate(0.0f, 90.0f - horizontalFOV / 2.0f, 0.0f);
	planes[FrustumPlanes::Left]->getTransform()->rotate(0.0f, -90.0f + horizontalFOV / 2.0f, 0.0f);
	vec3 right = planes[FrustumPlanes::Right]->getTransform()->getRight();
	vec3 left = planes[FrustumPlanes::Left]->getTransform()->getRight();
	planes[FrustumPlanes::Right]->getTransform()->translate(right * 5.0f);
	planes[FrustumPlanes::Left]->getTransform()->translate(left * -5.0f);
	//----------

	//transform->rotate(0.0f, 180.0f, 0.0f);

	//cout << "==========" << endl;
	//cout << "FRUSTUM" << endl;
	//vec3 frustumPosition = transform->getPosition();
	//vec3 frustumRotation = transform->getRotation();
	//vec3 frustumScale = transform->getScale();
	//vec3 frustumForward = transform->getForward();
	//cout << "frustumPosition: " << frustumPosition.x << " | " << frustumPosition.y << " | " << frustumPosition.z << endl;
	//cout << "frustumRotation: " << frustumRotation.x << " | " << frustumRotation.y << " | " << frustumRotation.z << endl;
	//cout << "frustumScale: " << frustumScale.x << " | " << frustumScale.y << " | " << frustumScale.z << endl;
	//cout << "frustumForward: " << frustumForward.x << " | " << frustumForward.y << " | " << frustumForward.z << endl;
	//cout << "==========" << endl;
	//
	//cout << "==========" << endl;
	//cout << "NEAR" << endl;
	//vec3 nearLocalPosition = planes[FrustumPlanes::Near]->getTransform()->getPosition();
	//vec3 nearGlobalPosition = planes[FrustumPlanes::Near]->getTransform()->getGlobalPosition();
	//vec3 nearRotation = planes[FrustumPlanes::Near]->getTransform()->getRotation();
	//vec3 nearScale = planes[FrustumPlanes::Near]->getTransform()->getScale();
	//vec3 nearForward = planes[FrustumPlanes::Near]->getTransform()->getForward();
	//cout << "nearLocalPosition: " << nearLocalPosition.x << " | " << nearLocalPosition.y << " | " << nearLocalPosition.z << endl;
	//cout << "nearGlobalPosition: " << nearGlobalPosition.x << " | " << nearGlobalPosition.y << " | " << nearGlobalPosition.z << endl;
	//cout << "nearRotation: " << nearRotation.x << " | " << nearRotation.y << " | " << nearRotation.z << endl;
	//cout << "nearScale: " << nearScale.x << " | " << nearScale.y << " | " << nearScale.z << endl;
	//cout << "nearForward: " << nearForward.x << " | " << nearForward.y << " | " << nearForward.z << endl;
	//cout << "==========" << endl;
	//
	//cout << "==========" << endl;
	//cout << "FAR" << endl;
	//vec3 farPosition = planes[FrustumPlanes::Far]->getTransform()->getPosition();
	//vec3 farRotation = planes[FrustumPlanes::Far]->getTransform()->getRotation();
	//vec3 farForward = planes[FrustumPlanes::Far]->getTransform()->getForward();
	//cout << "farPosition: " << farPosition.x << " | " << farPosition.y << " | " << farPosition.z << endl;
	//cout << "farRotation: " << farRotation.x << " | " << farRotation.y << " | " << farRotation.z << endl;
	//cout << "farForward: " << farForward.x << " | " << farForward.y << " | " << farForward.z << endl;
	//cout << "==========" << endl;
}

Frustum::~Frustum()
{
	for (int i = 0; i < planes.size(); i++) if (planes[i]) delete planes[i];
}

FrustumData Frustum::getFrustumData() { return data; }

FrustumPlane* Frustum::getPlane(FrustumPlanes plane)
{
	if (plane == FrustumPlanes::Length)
	{
		cout << "Can't return plane: given parameter is invalid, returning null." << endl;
		return NULL;
	}

	return planes[plane];
}

bool Frustum::isInside(vec3 point)
{
	//cout << "point position: " << point.x << " | " << point.y << " | " << point.z << endl;
	//cout << "distance to far: " << planes[FrustumPlanes::Far]->distanceToPoint(point) << endl;
	//cout << endl;

	for (int i = 0; i < FrustumPlanes::Length; i++) if (planes[i]->distanceToPoint(point) < 0.0f) return false;
	return true;
}

bool Frustum::isInside(Entity* entity)
{
	vector<vec3> vertices = entity->getCollisionVertices();
	for (int i = 0; i < vertices.size(); i++)
	{
		bool inside = true;

		for (int j = 0; j < FrustumPlanes::Length; j++) if (planes[j]->distanceToPoint(vertices[i]) < 0.0f)
		{
			inside = false;
			break;
		}

		if (inside) return true;
	}

	return false;
}

#pragma region Collision Box
vector<vec3> Frustum::getCollisionVertices()
{
	cout << "Can not generate collision vertices for this class (Frustum)" << endl;
	return vector<vec3>();
}
#pragma endregion

void Frustum::printDebugData()
{
	//cout << endl << endl;
	//cout << "==========" << endl;
	//cout << "FRUSTUM" << endl;
	//vec3 frustumLocalPosition = transform->getPosition();
	//vec3 frustumGlobalPosition = transform->getGlobalPosition();
	//vec3 frustumRotation = transform->getRotation();
	//vec3 frustumForward = transform->getForward();
	//cout << "frustumLocalPosition: " << frustumLocalPosition.x << " | " << frustumLocalPosition.y << " | " << frustumLocalPosition.z << endl;
	//cout << "frustumGlobalPosition: " << frustumGlobalPosition.x << " | " << frustumGlobalPosition.y << " | " << frustumGlobalPosition.z << endl;
	//cout << "frustumRotation: " << frustumRotation.x << " | " << frustumRotation.y << " | " << frustumRotation.z << endl;
	//cout << "frustumForward: " << frustumForward.x << " | " << frustumForward.y << " | " << frustumForward.z << endl;
	//cout << "==========" << endl;
	//
	//cout << "==========" << endl;
	//cout << "NEAR" << endl;
	//vec3 nearLocalPosition = planes[FrustumPlanes::Near]->getTransform()->getPosition();
	//vec3 nearGlobalPosition = planes[FrustumPlanes::Near]->getTransform()->getGlobalPosition();
	//vec3 nearRotation = planes[FrustumPlanes::Near]->getTransform()->getRotation();
	//vec3 nearScale = planes[FrustumPlanes::Near]->getTransform()->getScale();
	//vec3 nearForward = planes[FrustumPlanes::Near]->getTransform()->getForward();
	//cout << "nearLocalPosition: " << nearLocalPosition.x << " | " << nearLocalPosition.y << " | " << nearLocalPosition.z << endl;
	//cout << "nearGlobalPosition: " << nearGlobalPosition.x << " | " << nearGlobalPosition.y << " | " << nearGlobalPosition.z << endl;
	//cout << "nearRotation: " << nearRotation.x << " | " << nearRotation.y << " | " << nearRotation.z << endl;
	//cout << "nearForward: " << nearForward.x << " | " << nearForward.y << " | " << nearForward.z << endl;
	//cout << "==========" << endl;
}

void Frustum::draw()
{
	for (int i = 0; i < planes.size(); i++) if (planes[i]) planes[i]->draw();
}