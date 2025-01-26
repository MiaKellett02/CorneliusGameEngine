#pragma once

//Project includes.
#include "Vector2.h"

//Library includes.
#include <map>
#include <vector>
#include <limits>

//Class definitions.
namespace CorneliusEngine {

	class DjikstraPosition {
	public:
		//Variables.
		Vector2Int position;
		std::map<DjikstraPosition*, float> connections; // Key = position, value = cost to move to that position.
		// Djikstra position stored as pointer but not owned by this object.

		const float START_COST = 10000000;
		float totalCostToStart = START_COST;
		DjikstraPosition* connectingNodeToStart = nullptr;

		//Functions,
		void MakeConnection(DjikstraPosition* a_newConnection, float a_movementCostMultiplier);
		float CalculateMovementCost(DjikstraPosition* a_other, float a_movementCostMultiplier);
	};
}

namespace CorneliusEngine {

	class DjikstraPathfinding {
	public:
		static std::vector<Vector2Int> FindPath(CorneliusEngine::DjikstraPosition* a_startPos, CorneliusEngine::DjikstraPosition* a_goalPos);

		static void SortPositions(std::vector<CorneliusEngine::DjikstraPosition*>& a_positonsToSort);

	private:
		static bool ListHasValue(DjikstraPosition* a_value, std::vector<DjikstraPosition*>& a_list);
		static void RemoveValue(DjikstraPosition* a_value, std::vector<DjikstraPosition*>& a_list);
	};
}