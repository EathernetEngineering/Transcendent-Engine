#pragma once

#include <Transcendent-Engine/ECS/DefaultComponants.h>
#include <rpc.h>

namespace TE {
	class ECS
	{
	public:
		ECS();
		~ECS();

		static void Init();
		static void AddScript(UUID ID, std::shared_ptr<Behaviour> Script);
		static void AddMesh(UUID ID, std::shared_ptr<Mesh> Script);


	private:
		static std::map<UUID, Behaviour> Scripts;
		static std::map<UUID, Mesh>      Meshes;
	};
}
