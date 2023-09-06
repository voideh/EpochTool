#include "pch-il2cpp.h"
#include "utility.h"
#include <iostream>
using namespace app;
GameObject* getPlayer()
{
	GameObject* player = PlayerFinder_getPlayer(nullptr);
	return player;
}

bool getDamageable(GameObject* player)
{
	PlayerHealth* pHealth = GameObject_GetComponent_199(player, *GameObject_GetComponent_186__MethodInfo);

	return PlayerHealth_isDamageable(pHealth, nullptr);
}

BaseHealth* getBaseHealth(GameObject* player)
{
	BaseHealth* bHealth = GameObject_GetComponent_210(player, *GameObject_GetComponent_199__MethodInfo);
	return bHealth;
}

std::vector<Stats_Stat*> getStats(GameObject* player)
{
	std::vector<Stats_Stat*> stats = std::vector<Stats_Stat*>();

	BaseStats* playerBase = GameObject_GetComponent_119(player, *GameObject_GetComponent_119__MethodInfo);
	List_1_Stats_Stat_* statList = playerBase->fields._.stats;

	for (int i = 0; i < List_1_Stats_Stat__get_Count(statList, nullptr); i++)
	{
		Stats_Stat* s = List_1_Stats_Stat__get_Item(statList, i, nullptr);
		if (s->fields.tags == AT__Enum::None) {
			switch (s->fields.property)
			{
			case SP__Enum::Damage:
			case SP__Enum::AttackSpeed:
			case SP__Enum::CastSpeed:
			case SP__Enum::Movespeed:
				stats.push_back(s);
				break;
			default:
				break;
			}
		}
	}
	return stats;
}
Stats_Stat* getMovespeed(GameObject* player)
{
	BaseStats* playerBase = GameObject_GetComponent_119(player, *GameObject_GetComponent_119__MethodInfo);
	List_1_Stats_Stat_* statList = playerBase->fields._.stats;
	for (int i = 0; i < List_1_Stats_Stat__get_Count(statList, nullptr); i++)
	{
		Stats_Stat* s = List_1_Stats_Stat__get_Item(statList, i, nullptr);
		if (s->fields.tags == AT__Enum::None&& s->fields.property == SP__Enum::Movespeed) {
			return s;
		}
	}
	return nullptr;
}

Stats_Stat* getAttackSpeed(GameObject* player)
{
	BaseStats* playerBase = GameObject_GetComponent_119(player, *GameObject_GetComponent_119__MethodInfo);
	List_1_Stats_Stat_* statList = playerBase->fields._.stats;
	for (int i = 0; i < List_1_Stats_Stat__get_Count(statList, nullptr); i++)
	{
		Stats_Stat* s = List_1_Stats_Stat__get_Item(statList, i, nullptr);
		if (s->fields.tags == AT__Enum::None && s->fields.property == SP__Enum::AttackSpeed) {
			return s;
		}
	}
	return nullptr;
}

Stats_Stat* getCastSpeed(GameObject* player)
{
	BaseStats* playerBase = GameObject_GetComponent_119(player, *GameObject_GetComponent_119__MethodInfo);
	List_1_Stats_Stat_* statList = playerBase->fields._.stats;
	for (int i = 0; i < List_1_Stats_Stat__get_Count(statList, nullptr); i++)
	{
		Stats_Stat* s = List_1_Stats_Stat__get_Item(statList, i, nullptr);
		if (s->fields.tags == AT__Enum::None && s->fields.property == SP__Enum::CastSpeed) {
			return s;
		}
	}
	return nullptr;
}

Stats_Stat* getDamage(GameObject* player)
{
	BaseStats* playerBase = GameObject_GetComponent_119(player, *GameObject_GetComponent_119__MethodInfo);
	List_1_Stats_Stat_* statList = playerBase->fields._.stats;
	for (int i = 0; i < List_1_Stats_Stat__get_Count(statList, nullptr); i++)
	{
		Stats_Stat* s = List_1_Stats_Stat__get_Item(statList, i, nullptr);
		if (s->fields.tags == AT__Enum::None && s->fields.property == SP__Enum::Damage) {
			return s;
		}
	}
	return nullptr;
}

Stats_Stat* getManaRegen(GameObject* player)
{
	BaseStats* playerBase = GameObject_GetComponent_119(player, *GameObject_GetComponent_119__MethodInfo);
	List_1_Stats_Stat_* statList = playerBase->fields._.stats;
	for (int i = 0; i < List_1_Stats_Stat__get_Count(statList, nullptr); i++)
	{
		Stats_Stat* s = List_1_Stats_Stat__get_Item(statList, i, nullptr);
		if (s->fields.tags == AT__Enum::None && s->fields.property == SP__Enum::ManaRegen) {
			return s;
		}
	}
	return nullptr;
}

const char* getReadableSPName(SP__Enum sp) 
{
	switch (sp) 
	{
	case SP__Enum::Damage:
		return "Damage";
	case SP__Enum::AttackSpeed:
		return "Attack Speed";
	case SP__Enum::CastSpeed:
		return "Cast Speed";
	case SP__Enum::Movespeed:
		return "Move Speed";
	default:
		return "IDK";
	}
}

void updateStats(GameObject* player)
{
	BaseStats* playerBase = GameObject_GetComponent_119(player, *GameObject_GetComponent_119__MethodInfo);
	BaseStats_UpdateStats(playerBase, nullptr);
}

// TODO: Get this working somehow...
void DevAttemptCraftingMats()
{
	DeveloperMode* dvMode = (DeveloperMode*)il2cpp_object_new((Il2CppClass*)*DeveloperMode__TypeInfo);
	DeveloperMode__ctor(dvMode, nullptr);

	dvMode->fields.status = true;

	std::cout << "Wakingup dev mode..." << std::endl;
	DeveloperMode_Awake(dvMode, nullptr);
	//DeveloperMode_Start(dvMode, nullptr);
	std::cout << "Attempting to craft mats..." << std::endl;
	DeveloperMode_CreateCraftingMats(dvMode, nullptr);
	
}

void toggleFracture()
{
	std::cout << "TEST : ToggleFracture?? Does it exist" << std::endl;
	CraftingSlotManager* csm = (*CraftingSlotManager__TypeInfo)->static_fields->instance;
	if (csm)
	{
		const char* status = csm->fields.debugNoFracture ? "No" : "Yes";
		std::cout << "Fracturing enabled ?? : " << status << std::endl;
		csm->fields.debugNoFracture = true;

	}
	else
	{
		std::cout << "Couldn't find it chief" << std::endl;
	}
}


// RIP: Crashes game everytime :(
/*
void genAffix()
{
	CraftingSlotManager* csm = (*CraftingSlotManager__TypeInfo)->static_fields->instance;

	if (csm)
	{
		std::cout << "Lets see what this does.." << std::endl;

		AffixList* al = AffixList_get(nullptr);
		std::cout << "Grabbing Affixlist.." << std::endl;
		if (al)
		{
			std::cout << "Attempting to add shards from list..." << std::endl;
			CraftingSlotManager_AddShardsFromList(csm, (AffixList_Affix__Array*)al->fields.singleAffixes, nullptr);
		}
		std::cout << "Huzzah!" << std::endl;

	}
	else
		std::cout << "No crafting manager found..." << std::endl;
}


void genCraftingMats()
{

	Actor_2* pActor = PlayerFinder_getPlayerActor(nullptr);

	if(pActor){
		Vector3 position = Actor_2_position(pActor, nullptr);
		std::cout << "Going to drop at x: " << position.x 
				  << ", y : " << position.y 
				  << ", z : " << position.z 
				  << std::endl;
		GenerateItems* genner = pActor->fields.generateItems;
		if (genner)
			GenerateItems_SpawnCraftingItem(pActor->fields.generateItems, 1, position, nullptr);
		else
			std::cout << "FUCK OFF" << std::endl;
	}
}

*/