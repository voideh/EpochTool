#pragma once
#include "pch-il2cpp.h"
#include <vector>
#define WIN32_LEAN_AND_MEAN

using namespace app;
GameObject* getPlayer();
bool getDamageable(GameObject* player);
BaseHealth* getBaseHealth(GameObject* player);

std::vector<Stats_Stat*> getStats(GameObject* player);
const char* getReadableSPName(SP__Enum sp);

void updateStats(GameObject* _player);
Stats_Stat* getMovespeed(GameObject* player);
Stats_Stat* getAttackSpeed(GameObject* player);
Stats_Stat* getCastSpeed(GameObject* player);
Stats_Stat* getDamage(GameObject* player);
Stats_Stat* getManaRegen(GameObject* player);

void DevAttemptCraftingMats();
void toggleFracture();
void genAffix();

// Experimental
void genCraftingMats();