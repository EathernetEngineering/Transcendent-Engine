#include <tepch.h>
#include <Transcendent-Engine/ECS/Entity.h>
#include <Transcendent-Engine/ECS/ECS.h>

namespace TE {
	Entity::Entity() 
	{
		UuidCreate(&m_ID);
	}

	template<typename T>
	T Entity::Addcomponant() {
		std::shared_ptr<T> monobehaviour;
	}

	template<>
	Mesh Entity::Addcomponant<Mesh>() {
		std::shared_ptr<Mesh> mesh;

		mesh = std::make_shared<Mesh>();

		ECS::AddMesh(m_ID, mesh);

		return *(mesh);
	}
}
