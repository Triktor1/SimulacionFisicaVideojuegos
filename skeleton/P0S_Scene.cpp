#include "P0S_Scene.h"
#include "Vector3D.h"
void P0S_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	physx::PxTransform* t1 = new physx::PxTransform(physx::PxVec3(2.0f, 0.0f, 3.0f));
	transforms.push_back(t1);
	RenderItem* ri1 = new RenderItem(shape, t1, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	renderItems.push_back(ri1);

#pragma region RETO A
	// RETO A --------------------------------------------
	//	Vector3D u = Vector3D(3.0f, 1.0f, 0.0f), 
	//		v = Vector3D(0.0f, 4.0f, 0.0f), 
	//		w = u.cross(v);

	//	u = u.normalize() * 5.0f;
	//	v = v.normalize() * 5.0f;
	//	w = w.normalize() * 5.0f;

	//		physx::PxTransform* t2 = new physx::PxTransform(u);
	//		transforms.push_back(t2);
	//		RenderItem* ri2 = new RenderItem(shape, t2, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	//		renderItems.push_back(ri2);

	//		physx::PxTransform* t3 = new physx::PxTransform(v);
	//		transforms.push_back(t3);
	//		RenderItem* ri3 = new RenderItem(shape, t3, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	//		renderItems.push_back(ri3);

	//		physx::PxTransform* t4 = new physx::PxTransform(w);
	//		transforms.push_back(t4);
	//		RenderItem* ri4 = new RenderItem(shape, t4, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	//		renderItems.push_back(ri4);
#pragma endregion 

#pragma region RETO B
//Vector3D visionDir = Vector3D(0, 0, 1);

//Vector3D v1 = Vector3D(-4, 0, 1);
//physx::PxTransform* t2 = new physx::PxTransform(physx::PxVec3(v1));
//transforms.push_back(t2);
//Vector3D v2 = Vector3D(0, 0, 5);
//physx::PxTransform* t3 = new physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 5.0f));
//transforms.push_back(t3);
//Vector3D v3 = Vector3D(3, 0, 0);
//physx::PxTransform* t4 = new physx::PxTransform(physx::PxVec3(3.0f, 0.0f, 0.0f));
//transforms.push_back(t4);
//
//Vector4 c1;
//if (visionDir.dot(v1) > 0)
//	c1 = Vector4(1, 0, 0, 1);
//else if (visionDir.dot(v1) == 0)
//	c1 = Vector4(1, 1, 0, 1);
//else c1 = Vector4(0, 1, 0, 1);
//Vector4 c2;
//if (visionDir.dot(v2) > 0)
//	c2 = Vector4(1, 0, 0, 1);
//else if (visionDir.dot(v2) == 0)
//	c2 = Vector4(1, 1, 0, 1);
//else c2 = Vector4(0, 1, 0, 1);
//Vector4 c3;
//if (visionDir.dot(v3) > 0)
//	c3 = Vector4(1, 0, 0, 1);
//else if (visionDir.dot(v3) == 0)
//	c3 = Vector4(1, 1, 0, 1);
//else c3 = Vector4(0, 1, 0, 1);

//RenderItem* ri2 = new RenderItem(shape, t2, c1);
//renderItems.push_back(ri2);
//RenderItem* ri3 = new RenderItem(shape, t3, c2);
//renderItems.push_back(ri3);
//RenderItem* ri4 = new RenderItem(shape, t4, c3);
//renderItems.push_back(ri4);
#pragma endregion 

#pragma region RETO C
	//physx::PxTransform* a = new physx::PxTransform(physx::PxVec3(-8.0f, 1.0f, -8.0f));
	//transforms.push_back(a);
	//RenderItem* ra = new RenderItem(shape, a, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	//renderItems.push_back(ra);
	//physx::PxTransform* b = new physx::PxTransform(physx::PxVec3(8.0f, 8.0f, 8.0f));
	//transforms.push_back(b);
	//RenderItem* rb = new RenderItem(shape, b, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	//renderItems.push_back(rb);
	//for (int i = 0; i < 10; i++) {
	//	Vector3D transform;
	//	transform = a->p + ((1 + i) / 11.0f) * (b->p - a->p);
	//	physx::PxTransform* t = new physx::PxTransform(transform);
	//	transforms.push_back(t);
	//	RenderItem* rt = new RenderItem(shape, t, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	//	renderItems.push_back(rt);
	//}
#pragma endregion
}

void P0S_Scene::cleanup() {
	for (auto& r : renderItems) {
		if (r != nullptr) {
			r->release();
			r = nullptr;
		}
	}
	for (auto& t : transforms) {
		if (t != nullptr) {
			delete t;
			t = nullptr;
		}
	}
}