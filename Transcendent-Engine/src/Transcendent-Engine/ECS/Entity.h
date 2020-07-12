#pragma once

#include <Transcendent-Engine/ECS/Componant.h>
#include <rpc.h>

namespace TE {
	class Entity
	{
	public:
		Entity();
		~Entity();

		template<typename T>
		T Addcomponant();

	private:
		UUID m_ID;
	};
}
