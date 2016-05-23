#include<stdlib.h>
#include<string.h>
#include<Windows.h>

#include "array.h"

#include "base.h"
#include "combat/creatures.h"
#include "game/game.h"
#include "gui/dialog.h"

#include "combat/creatures_xml.hxx"


#include<iostream>
#include<sstream>

using namespace std;

//using namespace tinyxml2;

/*
* Still missing: 
*
* 1) Filenames for projectile icons are still hardcoded in army::LoadResources
* 2) Creature types in high scores (GetMonType)
* 3) Debug menu free creatures
*/

#define MAX_CREATURES 256
#define RAND_DEFAULT 3

tag_monsterInfo gMonsterDatabase[MAX_CREATURES];

const char* CREATURE_DATA = ".\\DATA\\creatures.xml";

int giNumCreatures;
char *cMonFilename[MAX_CREATURES];
char *cArmyFrameFileNames[MAX_CREATURES];
char *gArmyNames[MAX_CREATURES];
char *gArmyNamesPlural[MAX_CREATURES];
int gMonRandBound[MAX_CREATURES][2];
int gMonSecondaryCost[MAX_CREATURES][6][2];

struct attributeNameTableEntry{char* name; int flag;};

attributeNameTableEntry creatureAttributeNameTable[] = {
	{"two-hex", TWO_HEXER},
	{"flies", FLYER},
	{"shoots", SHOOTER},
	{"two-hex-attack", TWO_HEX_ATTACKER},
	{"undead", UNDEAD}
};

struct secondaryCostIdxTableEntry { char * resource; int idx; };

secondaryCostIdxTableEntry secondaryCostIdxTable[] = {
	{"wood", 0},
	{"mercury", 1},
	{"ore", 2},
	{"sulfer", 3},
	{"crystal", 4},
	{"gems", 5}
};

char* ironfistAttributeNames[] = {STRIKE_AND_RETURN};
int ironfistAttributeTable[ELEMENTS_IN(ironfistAttributeNames)][MAX_CREATURES];

void ResetCreatureAttributes() {
	memset(ironfistAttributeTable, 0, sizeof(ironfistAttributeTable));
}

void GrantCreatureAttribute(int id, const char* name) {
	for(int i = 0; i < ELEMENTS_IN(ironfistAttributeNames); i++) {
		if(0 == strcmp(ironfistAttributeNames[i], name)) {
			ironfistAttributeTable[i][id] = 1;
			return;
		}
	}

	EarlyShutdown((char*)name, "Attempted to grant attribute that does not exist. Check creatures.xml .");
}

int CreatureHasAttribute(int id, const char* name) {
	for(int i = 0; i < ELEMENTS_IN(ironfistAttributeNames); i++) {
		if(0 == strcmp(ironfistAttributeNames[i], name)) {
			return ironfistAttributeTable[i][id];
		}
	}

	return 0;
}

char* GetCreatureName(int id) {
	return gArmyNames[id];
}

char* GetCreaturePluralName(int id) {
	return gArmyNamesPlural[id];
}

int GetNumCreatures() {
	return giNumCreatures;
}

void LoadCreatures() {

	ResetCreatureAttributes();

	try {
		auto_ptr<creatures_t> creats = creatures(string(CREATURE_DATA));

		giNumCreatures = 0;

		for(creatures_t::creature_const_iterator i(creats->creature().begin());
			i != creats->creature().end();
			i++) {
				creature_t c = *i;
				c.damage().begin()->minimum();

				int id = c.id();

				cMonFilename[id] = strdup(c.icn().c_str());
				cArmyFrameFileNames[id] = strdup(c.frm().c_str());
				gArmyNames[id] = strdup(c.name_singular().c_str());
				gArmyNamesPlural[id] = strdup(c.name_plural().c_str());
				gMonRandBound[id][0] = c.random_spawn().begin()->minimum();
				gMonRandBound[id][1] = c.random_spawn().begin()->maximum();

				giNumCreatures++;

				int creature_flags = 0;
				for(creature_t::creature_attribute_const_iterator j = c.creature_attribute().begin();
					j != c.creature_attribute().end();
					j++) {
						bool attr_found = false; 
						for(int k = 0; k < ELEMENTS_IN(creatureAttributeNameTable); k++) {
							if(strcmp(creatureAttributeNameTable[k].name,
								 j->name().c_str())
								== 0){
									creature_flags |= creatureAttributeNameTable[k].flag;
									attr_found = true;
									break;
							}
						}

						if(!attr_found) {
							//Ironfist-only attribute; using general attribute engine
							GrantCreatureAttribute(id, j->name().c_str());
						}
				}

				for (int i = 0; i < 6; i++) {
					gMonSecondaryCost[id][i][0] = 0;
					gMonSecondaryCost[id][i][1] = 0;
				}
				bool secondary_cost = false;
				for (creature_t::secondary_cost_iterator i = c.secondary_cost().begin();
				     i != c.secondary_cost().end();
					 ++i) {
					    for (int k = 0; k < ELEMENTS_IN(secondaryCostIdxTable); k++) {
						   if (strcmp(secondaryCostIdxTable[k].resource, i->resource().c_str())
							   == 0) {
							   if (!secondary_cost) {
								   gMonSecondaryCost[id][k][0] = 1;
								   gMonSecondaryCost[id][k][1] = i->cost();
								   secondary_cost = true;
							   }
							   else {
								   EarlyShutdown("Startup Error", 
									   "Error loading creature.xml.\nToo many secondary resource costs per creature!");
							   }
							       
						   }
					    }
				}
				
				gMonsterDatabase[id] = tag_monsterInfo(
					c.cost(),
					c.fight_value(),
					c.fight_value_aux(),
					c.growth(),
					c.hp(),
					c.faction(),
					c.speed(),
					c.attack(),
					c.defense(),
					c.damage().begin()->minimum(),
					c.damage().begin()->maximum(),
					c.shots(),
					c.short_name().c_str(),
					creature_flags,
					0);
				
		}
	} catch(const xml_schema::exception& e) {
		EarlyShutdown("Startup Error", "Error loading creatures.xml. Try reinstalling Ironfist.");
	}
}

void UnloadCreatures() {
	for(int i = 0; i < MAX_CREATURES; i++) {
		if(cMonFilename[i] != NULL) free(cMonFilename[i]);
		if(cArmyFrameFileNames[i] != NULL) free(cArmyFrameFileNames[i]);
		if(gArmyNames[i] != NULL) free(gArmyNames[i]);
		if(gArmyNamesPlural[i] != NULL) free(gArmyNamesPlural[i]);
	}
}

void __fastcall GetMonsterCost(int mon, int *const costs) {
	
	int i;
	bool customed_sc = false;
	for (i = 0; i < 6; ++i)
	{
		if (gMonSecondaryCost[mon][i][0])
		{
			costs[i] = gMonSecondaryCost[mon][i][1];
			customed_sc = true;
		}
		else
			costs[i] = 0;
	}
	costs[6] = gMonsterDatabase[mon].cost;

	if (!customed_sc) {
		switch (mon)
		{
		case CREATURE_GENIE:
			costs[5] = 1;
			break;
		case CREATURE_PHOENIX:
			costs[1] = 1;
			break;
		case CREATURE_CYCLOPS:
			costs[4] = 1;
			break;
		case CREATURE_GREEN_DRAGON:
		case CREATURE_RED_DRAGON:
			costs[3] = 1;
			break;
		case CREATURE_BLACK_DRAGON:
			costs[3] = 2;
			break;
		case CREATURE_GIANT:
			costs[5] = 1;
			break;
		case CREATURE_TITAN:
			costs[5] = 2;
			break;
		default:
			return;
		}
	}
}