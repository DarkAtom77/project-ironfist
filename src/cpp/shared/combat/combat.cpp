#include "base.h"
#include "adventure/adv.h"
#include "combat/combat.h"
#include "expansions.h"
#include "game/game.h"
#include "resource/resourceManager.h"
#include "artifacts.h"
#include "skills.h"
#include "sound/sound.h"
#include "spell/spells.h"

#include "gui/dialog.h"

#include "scripting/callback.h"
#include <string>
#include <set>

extern ironfistExtra gIronfistExtra;

int squaresAroundCaster[2][3] = {
  {14,27,40},
  {11,24,37}
};

void combatManager::InitNonVisualVars() {
  combatManager::InitNonVisualVars_orig();
        
  ScriptCallback("OnBattleStart");

  for(int i = 0; i < 2; i++) {
    HandlePandoraBox(i);
  }
}

/*
* What happens when a hero wins a battle using Pandora's Box, but loses their
* main army? They walk around with stacks of 0 creatures, of course! 
* 0-creature stacks are still useful in combat though, since all attacks do at least 1 damage.
*
* On a related note, in the original game, what happens when a hero wins a battle
* using temporarily-resurrected creatures, but has no army left at the end? They
* walk around with no creatures, and instantly lose their next battle.
*
* Winning a battle with nothing but summoned elementals remaining works, however.
*
* TL, DR: There is a bug when winning a battle with nothing but temporary creatures left,
* but it's also present in the original game.
*/
void combatManager::HandlePandoraBox(int side) {
  if(this->heroes[side] && this->heroes[side]->HasArtifact(ARTIFACT_PANDORA_BOX)) {

    //The HoMM II code appears to lack a definition of creature tier. This deserves investigation.
    //We temporarily hardcode the tier-1 creatures
    int creatChoices[] = {
      CREATURE_PEASANT, CREATURE_SPRITE,CREATURE_HALFLING, CREATURE_GOBLIN,
      CREATURE_SKELETON, CREATURE_CENTAUR, CREATURE_ROGUE, CREATURE_BLOODSUCKER
    };
    int creat = creatChoices[SRandom(0, ELEMENTS_IN(creatChoices)-1)];

    int hex = -1;
    int poss = ELEMENTS_IN(squaresAroundCaster[side]);
    int tryFirst = SRandom(0, poss-1);
    for(int i = 0; i < poss; i++) {
      int square = squaresAroundCaster[side][(i+tryFirst)%poss];
      if(gMonsterDatabase[creat].creature_flags & TWO_HEXER) {
        int dir = side == 0 ? 1 : -1;
        if(this->combatGrid[square+dir].unitOwner != -1)
          continue;
      }
      if(this->combatGrid[square].unitOwner == -1)
        hex = square;
    }

    if(hex==-1)
      return;

    int amt = gpGame->GetRandomNumTroops(creat);
    AddArmy(side, creat, amt, hex, 0x8000, 0);

    hexcell* cell = &this->combatGrid[hex];
    this->creatures[cell->unitOwner][cell->stackIdx].temporaryQty = amt;
  }
}

// We don't actually change anything in sElevationOverlay, but the disasm was causing some problems

#pragma pack(push, 1)
struct SElevationOverlay {
  __int16 terrains;
  char coveredHexes[15];
};
#pragma pack(pop)

SElevationOverlay sElevationOverlay[25] =
{
  {
    0,
    {
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255,
      255
    }
  },
  { 2, { 30, 31, 32, 33, 47, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255 } },
  {
    2,
    { 56, 57, 58, 59, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  { 2, { 42, 55, 56, 57, 58, 59, 60, 48, 255, 255, 255, 255, 255, 255, 255 } },
  { 2, { 69, 70, 71, 72, 73, 60, 48, 255, 255, 255, 255, 255, 255, 255, 255 } },
  { 2, { 29, 30, 31, 32, 33, 34, 35, 81, 69, 70, 71, 72, 73, 74, 87 } },
  { 2, { 29, 17, 18, 19, 20, 21, 81, 95, 96, 97, 98, 99, 255, 255, 255 } },
  { 4, { 30, 31, 32, 33, 47, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255 } },
  {
    4,
    { 56, 57, 58, 59, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  { 4, { 42, 55, 56, 57, 58, 59, 47, 255, 255, 255, 255, 255, 255, 255, 255 } },
  { 4, { 69, 70, 71, 72, 73, 60, 48, 255, 255, 255, 255, 255, 255, 255, 255 } },
  { 4, { 18, 30, 43, 84, 85, 73, 60, 255, 255, 255, 255, 255, 255, 255, 255 } },
  { 4, { 21, 34, 48, 70, 83, 97, 98, 255, 255, 255, 255, 255, 255, 255, 255 } },
  {
    64,
    { 30, 31, 32, 33, 47, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  {
    64,
    { 56, 57, 58, 59, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  { 64, { 42, 55, 56, 57, 58, 59, 60, 48, 255, 255, 255, 255, 255, 255, 255 } },
  { 64, { 69, 70, 71, 72, 73, 60, 48, 255, 255, 255, 255, 255, 255, 255, 255 } },
  { 64, { 29, 30, 31, 32, 33, 34, 35, 81, 69, 70, 71, 72, 73, 74, 87 } },
  { 64, { 29, 17, 18, 19, 20, 21, 81, 95, 96, 97, 98, 99, 255, 255, 255 } },
  {
    128,
    { 30, 31, 32, 33, 47, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  {
    128,
    { 56, 57, 58, 59, 60, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  { 128, { 42, 55, 56, 57, 58, 59, 60, 48, 255, 255, 255, 255, 255, 255, 255 } },
  {
    128,
    { 69, 70, 71, 72, 73, 60, 48, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  {
    128,
    { 43, 30, 18, 84, 85, 73, 60, 255, 255, 255, 255, 255, 255, 255, 255 }
  },
  {
    128,
    { 21, 34, 48, 70, 83, 97, 98, 255, 255, 255, 255, 255, 255, 255, 255 }
  }
};

void combatManager::LowerDoor() {
  SAMPLE2 res = LoadPlaySample("drawbrg.82m");
  giMinExtentX = 304;
  giMinExtentY = 218;
  giMaxExtentX = 384;
  giMaxExtentY = 294;
  for (int i = 2; i >= 0; --i) {
    this->drawBridgePosition = i;
    this->DrawFrame(1, 0, 1, 0, 75, 1, 1);
  }
  WaitEndSample(res, res.sample);
}

void combatManager::ArcShot(icon *icn, int fromX, int fromY, int targX, int targY)
{
  bool firingLeft = false;
  if (fromX > targX)
    firingLeft = true;
  int imageIdx = 0; // changes the sprite when its angle changes

  // temporarily save the screen so we can clear it from the projectile sprite later
  bitmap *savedscreen = new bitmap(0, INTERNAL_WINDOW_WIDTH, INTERNAL_WINDOW_HEIGHT);
  gpWindowManager->screenBuffer->CopyTo(savedscreen, 0, 0, 0, 0, INTERNAL_WINDOW_WIDTH, INTERNAL_WINDOW_HEIGHT);

  std::vector<COORD> points;
  const int NUM_FRAMES = 24; // equals to the number of frames for the whole arc path
  points = MakeCatapultArc(NUM_FRAMES, firingLeft, fromX, fromY, targX, targY);
  for(int i = 0; i < (int)points.size(); i++) {
    if (i % 3 == 0) // every 3rd cycle
      if(imageIdx < (icn->numSprites - 1))
        imageIdx++; // changes the sprite of projectile
    savedscreen->CopyTo(gpWindowManager->screenBuffer, 0, 0, 0, 0, INTERNAL_WINDOW_WIDTH, INTERNAL_WINDOW_HEIGHT); // clear the screen from the previous projectile sprite
    icn->CombatClipDrawToBuffer(points[i].X, points[i].Y, imageIdx, NULL, firingLeft, 0, 0, 0);
    gpWindowManager->UpdateScreenRegion(0, 0, INTERNAL_WINDOW_WIDTH, INTERNAL_WINDOW_HEIGHT);
    glTimers = (signed __int64)((double)KBTickCount() + (double)40 * gfCombatSpeedMod[giCombatSpeed]);
    DelayTil(&glTimers);
  }
  delete savedscreen;
  this->DrawFrame(1, 0, 0, 0, 1, 1, 1); // clear screen from the projectile
}

void combatManager::ShowSpellMessage(int isCreatureAbility, int spell, army *stack) {
  char *creatureName;

  if (stack) {
    if (stack->quantity <= 1)
      creatureName = GetCreatureName(stack->creatureIdx);
    else
      creatureName = GetCreaturePluralName(stack->creatureIdx);
  }
  if (isCreatureAbility) {
    switch (spell) {
    case SPELL_PARALYZE:
      sprintf(gText, "The %s are paralyzed by the Cyclopes!", creatureName);
      break;
    case SPELL_BLIND:
      sprintf(gText, "The Unicorns' attack blinds the %s!", creatureName);
      break;
    case SPELL_MEDUSA_PETRIFY:
      sprintf(gText, "The Medusas' gaze turns the %s to stone!", creatureName);
      break;
    case SPELL_CURSE:
      sprintf(gText, "The Mummies' curse falls upon the %s!", creatureName);
      break;
    case SPELL_ARCHMAGI_DISPEL:
      sprintf(gText, "The Archmagi dispel all good spells\non the %s!", creatureName);
      break;
    case SPELL_SHADOW_MARK:
      sprintf(gText, "The Shadow Assassins mark the %s!", creatureName);
      break;
    }
  } else if (stack) {
    if (this->heroes[this->currentActionSide]->isCaptain)
      sprintf(gText, "The captain casts '%s' on the %s.", gSpellNames[spell], creatureName);
    else
      sprintf(gText,"%s casts '%s' on the %s.", this->heroes[this->currentActionSide]->name, gSpellNames[spell], creatureName);
  } else if (this->heroes[this->currentActionSide]->isCaptain) {
    sprintf(gText, "The captain casts '%s'.", gSpellNames[spell]);
  } else {
    sprintf(gText, "%s casts '%s'.", this->heroes[this->currentActionSide]->name, gSpellNames[spell]);
  }
  this->CombatMessage(gText, 1, 1, 0);
}

void combatManager::SpellMessage(int spell, int hex) {
  army *targ; // [sp+18h] [bp-4h]@7

  if (!gbNoShowCombat) {

    switch (spell) {
      case SPELL_FIREBALL:
      case SPELL_FIREBLAST:
      case SPELL_METEOR_SHOWER:
      case SPELL_COLD_RING:
      case SPELL_PLASMA_CONE:
        sprintf(gText, "Cast %s", gSpellNames[spell]);
        break;
      case SPELL_TELEPORT: {
        if (bInTeleportGetDest) {
          sprintf(gText, "Teleport Here");
          break;
        }
        targ = &this->creatures[this->combatGrid[hex].unitOwner][this->combatGrid[hex].stackIdx];

        char *creatureName;
        if (targ->quantity == 1)
          creatureName = GetCreatureName(targ->creatureIdx);
        else
          creatureName = GetCreaturePluralName(targ->creatureIdx);
        sprintf(gText, "Cast %s on %s", gSpellNames[spell], creatureName);
        break;
      }
      case SPELL_RESURRECT:
      case SPELL_RESURRECT_TRUE:
      case SPELL_ANIMATE_DEAD: {
        int resStack = this->FindResurrectArmyIndex(this->currentActionSide, spell, hex);
        targ = &this->creatures[this->currentActionSide][resStack];

        char *creatureName; 
        if (targ->quantity == 1)
          creatureName = GetCreatureName(targ->creatureIdx);
        else
          creatureName = GetCreaturePluralName(targ->creatureIdx);
        sprintf(gText, "Cast %s on %s", gSpellNames[spell], creatureName);
        break;
      }
      default: {
        targ = &this->creatures[this->combatGrid[hex].unitOwner][this->combatGrid[hex].stackIdx];
        char *creatureName; 
        if (targ->quantity == 1)
          creatureName = GetCreatureName(targ->creatureIdx);
        else
          creatureName = GetCreaturePluralName(targ->creatureIdx);
        sprintf(gText, "Cast %s on %s", gSpellNames[spell], creatureName);
        break;
      }
    }
    this->CombatMessage(gText, 1, 0, 0);
  }
}

int combatManager::ValidSpellTarget(int spell, int hexIdx) {
  if (ValidHex(hexIdx)) {
    army *stack = nullptr;
    if (spell != SPELL_FIREBALL
      && spell != SPELL_FIREBLAST
      && spell != SPELL_METEOR_SHOWER
      && spell != SPELL_COLD_RING
      && spell != SPELL_RESURRECT
      && spell != SPELL_RESURRECT_TRUE
      && spell != SPELL_ANIMATE_DEAD
      && this->combatGrid[hexIdx].unitOwner != -1
      && ((stack = &this->creatures[this->combatGrid[hexIdx].unitOwner][this->combatGrid[hexIdx].stackIdx],
        this->creatures[this->combatGrid[hexIdx].unitOwner][this->combatGrid[hexIdx].stackIdx].effectStrengths[EFFECT_ANTI_MAGIC])
        || this->creatures[this->combatGrid[hexIdx].unitOwner][this->combatGrid[hexIdx].stackIdx].creatureIdx == CREATURE_GREEN_DRAGON)) {
      return 0;
    } else if (stack && stack->SpellCastWorkChance(spell) <= 0.0) {
      return 0;
    } else {
      switch (spell) {
      case SPELL_HOLY_WORD:
      case SPELL_HOLY_SHOUT:
      case SPELL_DISPEL_MAGIC:
      case SPELL_MASS_DISPEL:
      case SPELL_ARMAGEDDON:
      case SPELL_ELEMENTAL_STORM:
      case SPELL_DEATH_RIPPLE:
      case SPELL_DEATH_WAVE:
        if (this->combatGrid[hexIdx].unitOwner != -1)
          return 1;
        return 0;
      case SPELL_RESURRECT:
      case SPELL_RESURRECT_TRUE:
      case SPELL_ANIMATE_DEAD:
        return this->FindResurrectArmyIndex(this->currentActionSide, spell, hexIdx) != -1;
      case SPELL_CURE:
      case SPELL_MASS_CURE:
      case SPELL_HASTE:
      case SPELL_MASS_HASTE:
      case SPELL_BLESS:
      case SPELL_MASS_BLESS:
      case SPELL_STONESKIN:
      case SPELL_STEELSKIN:
      case SPELL_ANTI_MAGIC:
      case SPELL_DRAGON_SLAYER:
      case SPELL_BLOOD_LUST:
      case SPELL_SHIELD:
      case SPELL_MASS_SHIELD:
        if (this->combatGrid[hexIdx].unitOwner == this->currentActionSide)
          return 1;
        return 0;
      case SPELL_FORCE_SHIELD:
      case SPELL_MASS_FORCE_SHIELD:
        if(this->combatGrid[hexIdx].unitOwner == this->currentActionSide)
          if(gIronfistExtra.combat.stack.forceShieldHP[stack] <= 0)
            return 1;
        return 0;
      case SPELL_MIRROR_IMAGE:
        if (this->combatGrid[hexIdx].unitOwner == this->currentActionSide) {
          if (this->creatures[this->combatGrid[hexIdx].unitOwner][this->combatGrid[hexIdx].stackIdx].mirrorIdx == -1
            && this->creatures[this->combatGrid[hexIdx].unitOwner][this->combatGrid[hexIdx].stackIdx].mirroredIdx == -1)
            return 1;
          return 0;
        } else {
          return 0;
        }
      case SPELL_LIGHTNING_BOLT:
      case SPELL_CHAIN_LIGHTNING:
      case SPELL_SLOW:
      case SPELL_MASS_SLOW:
      case SPELL_BLIND:
      case SPELL_CURSE:
      case SPELL_MASS_CURSE:
      case SPELL_MAGIC_ARROW:
      case SPELL_BERZERKER:
      case SPELL_PARALYZE:
      case SPELL_HYPNOTIZE:
      case SPELL_COLD_RAY:
      case SPELL_DISRUPTING_RAY:
      case SPELL_SHADOW_MARK:
      case SPELL_MARKSMAN_PIERCE:
        if (this->combatGrid[hexIdx].unitOwner == 1 - this->currentActionSide)
          return 1;
        return 0;
      case SPELL_TELEPORT:
        if (bInTeleportGetDest) {
          army* currentArmy = &this->creatures[gpCombatManager->combatGrid[giNextActionGridIndex].unitOwner][gpCombatManager->combatGrid[giNextActionGridIndex].stackIdx];
          if (hexIdx != giNextActionGridIndex && currentArmy->CanFit(hexIdx, 0, 0))
            return 1;
          return 0;
        } else {
          if (this->combatGrid[hexIdx].unitOwner == this->currentActionSide)
            return 1;
          return 0;
        }
        break;
      case SPELL_FIREBALL:
      case SPELL_FIREBLAST:
      case SPELL_METEOR_SHOWER:
      case SPELL_COLD_RING:
      case SPELL_PLASMA_CONE:
      case SPELL_FIRE_BOMB:
        if (hexIdx != -1 && hexIdx % 13 && hexIdx % 13 != 12)
          return 1;
        return 0;
      default:
        return 1;
      }
    }
  } else {
    return 0;
  }
}

void combatManager::SetupCombat(int arg0, int arg1, hero *h1, armyGroup *a1, town *t, hero *h2, armyGroup *a2, int arg2, int arg3, int arg4) {
    SetupCombat_orig(arg0, arg1, h1, a1, t, h2, a2, arg2, arg3, arg4);
    gIronfistExtra.combat.stack.abilityCounter.clear();
    gIronfistExtra.combat.stack.abilityNowAnimating.clear();
    gIronfistExtra.combat.stack.forceShieldHP.clear();
}

void combatManager::ResetRound() {
    ResetRound_orig();
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < MAX_STACKS; j++) {
            army* ptr = &gpCombatManager->creatures[i][j];
            if(ptr->creatureIdx >= 0 && CreatureHasAttribute(ptr->creatureIdx, ASTRAL_DODGE))
                gIronfistExtra.combat.stack.abilityCounter[ptr][ASTRAL_DODGE] = 1;
        }
    }
}

bool IsCastleWall(int hexIdx) {
    std::set<int> walls = {9, 22, 34, 47, 59, 73, 86, 100, 113, 92};
    return walls.find(hexIdx) != walls.end();
}

bool IsAICombatTurn() {
  int curPlayerID = gpCombatManager->playerID[gpCombatManager->currentActionSide];
  if(curPlayerID == -1) // AI neutral
    return 1;
  else if(!gbHumanPlayer[curPlayerID]) // AI player
    return 1;
  return 0;
}

int combatManager::GetCommand(int hex) {
  int v7 = 0;
  UpdateGrid(0, 0);
  int result = 0;
  switch(hex) {
    case -1:
      result = 0;
      break;
    case 25:
      if(this->heroes[1]) {
        if(this->currentActionSide == 1)
          result = 4;
        else
          result = 13;
      } else {
        result = 0;
      }
      break;
    case 26:
      if(this->heroes[0]) {
        if(this->currentActionSide)
          result = 13;
        else
          result = 4;
      } else {
        result = 0;
      }
      break;
    case 77:
      if(this->isCastleBattle)
        result = 5;
      else
        result = 0;
      break;
    default:
      if(hex % 13 == 12) {
        result = 0;
      } else {
        int tempOwner = this->combatGrid[hex].unitOwner;
        int tempStack = this->combatGrid[hex].stackIdx;
        army *a = &this->creatures[this->otherCurrentSideThing][this->someSortOfStackIdx];
        this->creatures[this->otherCurrentSideThing][this->someSortOfStackIdx].targetOwner = -1;
        a->targetStackIdx = -1;
        if(this->combatGrid[hex].isBlocked
          && (!gpCombatManager->isCastleBattle || hex != 58 && hex != 59 || gpCombatManager->drawBridgePosition == 4
            && (gpCombatManager->currentActionSide != 1 || gpCombatManager->combatGrid[58].unitOwner != -1 || gpCombatManager->combatGrid[58].numCorpses))) {
          result = 0;
        } else {
          if(tempOwner == -1) {
            if(this->creatures[this->otherCurrentSideThing][this->someSortOfStackIdx].ValidPath(hex, 0) == 1)
              result = 2 - ((*(DWORD *)&this->creatures[this->otherCurrentSideThing][this->someSortOfStackIdx].creature.creature_flags & (unsigned int)FLYER) < 1);
          } else {
            if(this->otherCurrentSideThing != tempOwner || this->someSortOfStackIdx != tempStack) {
              v7 = 1;
              if(!gbProcessingCombatAction) {
                if(!giNextAction) {
                  this->field_F547 = tempOwner;
                  this->field_F54B[1] = tempStack;
                  this->DrawSmallView(1, 1);
                }
              }
            }
            if(tempOwner >= 0 && tempOwner <= 1) {
              if(this->currentActionSide == tempOwner || this->otherCurrentSideThing == tempOwner && this->someSortOfStackIdx == tempStack)
                return 5;
              a->targetOwner = tempOwner;
              a->targetStackIdx = tempStack;
              if(a->creature.shots > 0 && a->GetAttackMask(a->occupiedHex, 1, -1) == 255) {
                if(this->ShotIsThroughWall(a->owningSide, a->occupiedHex, hex))
                  return 15;
                else
                  return 3;
              }
              // Makes charging possible if the path is completely blocked
              if(a->ValidPath(hex, 0) == 1 || (CreatureHasAttribute(a->creatureIdx, CHARGER) && a->TargetOnStraightLine(hex) && a->ValidFlight(hex, 0) && !a->FlightThroughObstacles(hex) && a->GetStraightLineDistanceToHex(hex) <= a->creature.speed))
                return 7;
              a->targetOwner = -1;
              a->targetStackIdx = -1;
              result = 0;
            }
          }
        }
      }
      break;
  }
  if(!v7) {
    if(!gbProcessingCombatAction) {
      this->field_F547 = -1;
      this->DrawSmallView(1, 1);
    }
  }
  return result;
}

void combatManager::SetupGridForArmy(army *stack) {
  this->SetupGridForArmy_orig(stack);
  // Will mark certain hexes black (possible to interact with)
  if(CreatureHasAttribute(stack->creatureIdx, CHARGER)) {
    for(int i = 0; i < NUM_HEXES; i++) {
      if((this->combatGrid[i].unitOwner != -1) && (this->combatGrid[i].unitOwner != stack->owningSide) && (!stack->FlightThroughObstacles(i)) && stack->TargetOnStraightLine(i)) {
        stack->targetHex = i;
        stack->targetOwner = this->combatGrid[i].unitOwner;
        stack->targetStackIdx = this->combatGrid[i].stackIdx;
        if(stack->ValidFlight(i, 0) && stack->GetStraightLineDistanceToHex(i) <= stack->creature.speed)
          this->field_49F[i] = this->field_42A[i] = 1;
      }
    }
  }
}

std::vector<COORD> MakeCatapultArc(int numPoints, bool lefttoright, float fromX, float fromY, float targX, float targY) {
  std::vector<COORD> points;
  float amplitude = 0.01282;
  float v33 = (double)((targX + fromX) / 2.);
  float stepX = (v33 - (double)fromX) / 12.5;
  float v32 = (double)targY - (double)(targX - fromX) * 0.3 - (double)targY * 0.35;
  if(lefttoright)
    v32 = (double)targY - (double)(fromX - targX) * 0.3 - (double)targY * 0.35;
  float stepY = (v32 - (double)fromY) * amplitude;
  int oldX = -1;
  int oldY = -1;

  float currentX = fromX;
  float currentY = fromY;
  for(int i = 0; i < numPoints; i++) {
    if(i == (numPoints / 2)) // reached the peak height
      stepY = (v32 - (double)targY) * amplitude;

    points.push_back({ (short)currentX, (short)currentY });

    oldX = (int)currentX;
    oldY = (int)currentY;
    currentX += stepX;
    currentY += (double)((numPoints / 2) - i) * stepY;
  }
  return points;
}

// Decides how a certain hex can be interacted from each direction by current creature
void combatManager::SetCombatDirections(int hexIdx) {
  if(this->field_F2B3)
    return;

  int v5[8]; // [sp+14h] [bp-74h]@31
  char v10[8]; // [sp+44h] [bp-44h]@53
  int a2[8]; // [sp+5Ch] [bp-2Ch]@9
  char v18[8]; // [sp+80h] [bp-8h]@47
  army* attacker = &this->creatures[this->otherCurrentSideThing][this->someSortOfStackIdx];
  int targetOwner = attacker->targetOwner;
  int targetStackIdx = attacker->targetStackIdx;
  attacker->targetOwner = -1;
  attacker->targetStackIdx = -1;
  army* target = &this->creatures[targetOwner][targetStackIdx];
  for(int i = 0; i < 8; ++i) {
    if(i != 6 && i != 7) {
      a2[i] = this->hexNeighbors[hexIdx][i];
    } else if(attacker->creature.creature_flags & TWO_HEXER) {
      if(attacker->facingRight == 1) {
        if(i == 6)
          a2[6] = this->hexNeighbors[hexIdx][5];
        if(i == 7)
          a2[7] = this->hexNeighbors[hexIdx][3];
      } else {
        if(i == 6)
          a2[6] = this->hexNeighbors[hexIdx][0];
        if(i == 7)
          a2[7] = this->hexNeighbors[hexIdx][2];
      }
    } else {
      a2[i] = -1;
    }
    if(attacker->creature.creature_flags & TWO_HEXER && a2[i] != -1) {
      if(attacker->facingRight == 1) {
        if(i == 5 || i == 4 || i == 3) {
          if(a2[i] % 13 == 1)
            a2[i] = -1;
          else
            --a2[i];
        }
        if(a2[i] % 13 == 11)
          v5[i] = -1;
        else
          v5[i] = a2[i] + 1;
      } else {
        if(!i || i == 1 || i == 2) {
          if(a2[i] % 13 == 11)
            a2[i] = -1;
          else
            ++a2[i];
        }
        if(a2[i] % 13 == 1)
          v5[i] = -1;
        else
          v5[i] = a2[i] - 1;
      }
    } else {
      v5[i] = -2;
    }
    v18[i] = this->ValidHexToStandOn(a2[i]) && this->ValidHexToStandOn(v5[i]);
  }
  if(attacker->creature.creature_flags & FLYER) {
    for(int i = 0; i < 8; ++i)
      v10[i] = v18[i];
  } else {
    for(int i = 0; i < 8; ++i) {
      if(v18[i])
        if((CreatureHasAttribute(attacker->creatureIdx, CHARGER) && attacker->GetStraightLineDistanceToHex(a2[i]) <= attacker->creature.speed && attacker->TargetOnStraightLine(a2[i]) && attacker->TargetOnStraightLine(hexIdx) && attacker->ValidFlight(a2[i], 0))) {
          v10[i] = a2[i] = 1;
        }
        else
          v10[i] = a2[i] == attacker->occupiedHex || attacker->ValidPath(a2[i], 1);
      else
        v10[i] = 0;
    }
  }
  this->field_F51F = 0;
  for(int i = 0; i < 8; ++i) {
    if(v10[i])
       this->field_F51F++;
  }
  if(!this->field_F51F)
    v10[6] = 1;
  memset(this->field_F503, 0xFFu, 0x18u);
  
  int v17;
  for(int i = 0; i < 8; ++i) {
    int v14 = i;
    if(i >= 6) {
      if(i == 6)
        v17 = 7;
      else
        v17 = 6;
    } else {
      v17 = (i + 3) % 6;
    }
    if(v10[v17]) {
      if(target->creature.creature_flags & TWO_HEXER) {
        if(i || this->combatGrid[hexIdx - 1].unitOwner != targetOwner || this->combatGrid[hexIdx - 1].stackIdx != targetStackIdx) {
          if(i != 5
            || this->combatGrid[hexIdx + 1].unitOwner != targetOwner
            || this->combatGrid[hexIdx + 1].stackIdx != targetStackIdx) {
            if(i != 2
              || this->combatGrid[hexIdx - 1].unitOwner != targetOwner
              || this->combatGrid[hexIdx - 1].stackIdx != targetStackIdx) {
              if(i == 3
                && this->combatGrid[hexIdx + 1].unitOwner == targetOwner
                && this->combatGrid[hexIdx + 1].stackIdx == targetStackIdx)
                v14 = 7;
            } else {
              v14 = 7;
            }
          } else {
            v14 = 6;
          }
        } else {
          v14 = 6;
        }
      }
      if(i >= 6) {
        if(i == 6) {
          this->field_F503[11] = v14;
          this->field_F503[12] = v14;
          this->field_F503[13] = v14;
        } else {
          this->field_F503[0] = v14;
          this->field_F503[1] = v14;
          this->field_F503[23] = v14;
        }
      } else {
        memset(&this->field_F503[4 * v17], v14, 4u);
      }
    }
  }
  int v12 = 24;
  while(v12 > 0) {
    for(int i = 0; i < 24; ++i) {
      if(this->field_F503[i] == -1) {
        int v6 = (i + 1) % 24;
        int v8 = (i + 23) % 24;
        if(this->field_F503[(i + 1) % 24] < 0 || this->field_F503[v6] > 7) {
          if(this->field_F503[v8] >= 0 &&  this->field_F503[v8] <= 7)
            this->field_F503[i] = this->field_F503[v8] + 10;
        } else {
           this->field_F503[i] = this->field_F503[v6] + 10;
        }
      }
    }
    v12 = 0;
    for(int i = 0; i < 24; ++i) {
      if(this->field_F503[i] < 10) {
        if(this->field_F503[i] == -1)
          ++v12;
      } else {
        this->field_F503[i] -= 10;
      }
    }
  }
  attacker->targetOwner = targetOwner;
  attacker->targetStackIdx = targetStackIdx;
}


void combatManager::CombatMessage(char* msg, int doUpdate, int keepPrevMessage, int a5) {
  // It already does this logging if gbNoShowCombat is true
  if (!gbNoShowCombat) {
    LogStr(msg);
  }
  this->CombatMessage_orig(msg, doUpdate, keepPrevMessage, a5);
}

void combatManager::DrawFrame(int redrawAll, int a3, int a4, int a5, signed int delay, int a7, int waitUntilItIsTime)
{
  int v8; // ecx@127
  int v9; // ST50_4@148
  int v10; // eax@146
  int offsetX; // [sp+24h] [bp-C4h]@22
  int offsetY; // [sp+28h] [bp-C0h]@19
  int offY; // [sp+34h] [bp-B4h]@96
  int imageIdx; // [sp+38h] [bp-B0h]@96
  int offX; // [sp+3Ch] [bp-ACh]@96
  unsigned __int8 v17[7]; // [sp+44h] [bp-A4h]@94
  Point16 v18[6][4]; // [sp+4Ch] [bp-9Ch]@94
  int v19; // [sp+ACh] [bp-3Ch]@151
  int colBound; // [sp+B0h] [bp-38h]@55
  int v21; // [sp+B4h] [bp-34h]@72
  int deltaX; // [sp+B8h] [bp-30h]@55
  int colStart; // [sp+BCh] [bp-2Ch]@55
  int i; // [sp+C0h] [bp-28h]@7
  int v25; // [sp+D4h] [bp-14h]@5
  int l; // [sp+DCh] [bp-Ch]@5
  int j; // [sp+E0h] [bp-8h]@47
  int k; // [sp+E4h] [bp-4h]@78

  if ( this->field_F357 || gbNoShowCombat || !this->field_F42F )
    return;
  PollSound();
  gpMouseManager->couldBeShowMouse = 0;
  if ( a3 )
  {
    v25 = 0;
    for ( l = 0; l < 2; ++l )
    {
      for ( i = 0; i < 20; ++i )
      {
        if ( this->limitCreature[l][i] > 0 )
        {
          v25 = 1;
          gbComputeExtent = 1;
          gbSaveBiggestExtent = 1;
          gbReturnAfterComputeExtent = 1;
          this->creatures[l][i].DrawToBuffer(
            this->combatGrid[this->creatures[l][i].occupiedHex].centerX,
            this->combatGrid[this->creatures[l][i].occupiedHex].occupyingCreatureBottomY,
            0);
          gbReturnAfterComputeExtent = 0;
          gbComputeExtent = 0;
          gbSaveBiggestExtent = 0;
        }
      }
    }
    for ( l = 0; l < 2; ++l )
    {
      if ( this->field_F41F[l] )
      {
        v25 = 1;
        gbComputeExtent = 1;
        gbSaveBiggestExtent = 1;
        gbReturnAfterComputeExtent = 1;
        this->heroIcon[l]->CombatClipDrawToBuffer(
          (unsigned int)l < 1 ? 30 : 610,
          (unsigned int)l < 1 ? 183 : 148,
          sCmbtHero[this->heroType[l]].frameIndex[this->heroAnimationType[l]][this->heroAnimationFrameCount[l]],
          &this->heroBounds[l],
          1,
          0,
          0,
          0);
        gbReturnAfterComputeExtent = 0;
        gbComputeExtent = 0;
        gbSaveBiggestExtent = 0;
      }
      if ( this->field_F427[l] )
      {
        v25 = 1;
        gbComputeExtent = 1;
        gbSaveBiggestExtent = 1;
        gbReturnAfterComputeExtent = 1;
        if ( l )
          offsetY = (unsigned int)this->heroes[l]->isCaptain < 1 ? 148 : 135;
        else
          offsetY = 183;
        if ( l )
          offsetX = (unsigned int)this->heroes[l]->isCaptain < 1 ? 610 : 103;
        else
          offsetX = 30;
        this->heroFlagIcon[l]->CombatClipDrawToBuffer(
          offsetX,
          offsetY,
          this->heroFlagIconIdx[l],
          &this->heroFlagBounds[l],
          1,
          0,
          0,
          0);
        gbReturnAfterComputeExtent = 0;
        gbComputeExtent = 0;
        gbSaveBiggestExtent = 0;
      }
    }
    if ( a5 || !v25 )
      goto LABEL_168;
    --giMinExtentX;
    --giMinExtentY;
    ++giMaxExtentX;
    ++giMaxExtentY;
    if ( giMinExtentX < 0 )
      giMinExtentX = 0;
    if ( giMinExtentY < 0 )
      giMinExtentY = 0;
    if ( giMaxExtentX > 639 )
      giMaxExtentX = 639;
    if ( giMaxExtentY > 442 )
      giMaxExtentY = 442;
  }
  if ( a7 )
  {
    if ( this->zeroedAfterAnimatingDeathAndHolySpells )
    {
      if ( a3 || a4 || gbLimitToExtent )
        this->probablyBitmapForCombatScreen->CopyTo(
          gpWindowManager->screenBuffer,
          giMinExtentX,
          giMinExtentY,
          giMinExtentX,
          giMinExtentY,
          giMaxExtentX - giMinExtentX + 1,
          giMaxExtentY - giMinExtentY + 1);
      else
        this->probablyBitmapForCombatScreen->CopyTo(gpWindowManager->screenBuffer, 0, 0, 0, 0, 640u, 443);
    }
    else
    {
      this->DrawBackground();
    }
  }
  if ( a3 )
  {
    gbLimitToExtent = 1;
    gbComputeExtent = 1;
  }
  for ( j = 0; j < 9; ++j )
  {
    if ( j == 1 && this->heroes[1] )
    {
      this->heroIcon[1]->CombatClipDrawToBuffer(
        (unsigned int)this->heroes[1]->isCaptain < 1 ? 610 : 103,
        (unsigned int)this->heroes[1]->isCaptain < 1 ? 148 : 0x87u,
        sCmbtHero[this->heroType[1]].frameIndex[this->heroAnimationType[1]][this->heroAnimationFrameCount[1]],
        &this->heroBounds[1],
        1,
        0,
        0,
        0);
      this->heroFlagIcon[1]->CombatClipDrawToBuffer(
        610,
        148,
        this->heroFlagIconIdx[1],
        &this->heroFlagBounds[1],
        1,
        0,
        0,
        0);
    }
    if ( j == 2 && this->heroes[0] )
    {
      this->heroIcon[0]->CombatClipDrawToBuffer(
        30,
        183,
        sCmbtHero[this->heroType[0]].frameIndex[this->heroAnimationType[0]][this->heroAnimationFrameCount[0]],
        this->heroBounds,
        0,
        0,
        0,
        0);
      this->heroFlagIcon[0]->CombatClipDrawToBuffer(
        30,
        183,
        this->heroFlagIconIdx[0],
        this->heroFlagBounds,
        0,
        0,
        0,
        0);
    }
    colStart = 1;
    colBound = 12;
    deltaX = 1;
    if ( this->isCastleBattle && j >= 5 )
    {
      colStart = 11;
      colBound = 0;
      deltaX = -1;
    }
    if ( this->isCastleBattle && j == 7 )
      this->combatScreenIcons[3]->CombatClipDrawToBuffer(
        22,
        390,
        this->probablyCatapultImgIdx[0],
        &this->catapultBounds,
        0,
        0,
        0,
        0);
    if ( this->isCastleBattle && j == 4 && this->drawBridgePosition != 4 )
      this->combatScreenIcons[5]->CombatClipDrawToBuffer(
        0,
        0,
        this->drawBridgePosition + 21,
        &this->drawbridgeBounds,
        0,
        0,
        0,
        0);
    if ( this->isCastleBattle && j == 5 && !this->drawBridgePosition )
      this->combatScreenIcons[5]->CombatClipDrawToBuffer(0, 0, 25, &this->field_F303, 0, 0, 0, 0);
    if ( this->isCastleBattle && j == 6 )
      this->combatScreenIcons[5]->CombatClipDrawToBuffer(
        0,
        0,
        (unsigned int)this->ballistaDestroyed < 1 ? 20 : 26,
        &this->ballistaBounds,
        0,
        0,
        0,
        0);
    v21 = 0;
    if ( this->isCastleBattle && this->wallStatus[3] != 2 && this->wallStatus[3] != 6 )
    {
      v21 = 1;
      for ( l = 0; l < 4; ++l )
      {
        this->combatGrid[114].DrawOccupant(l, 0);
        this->combatGrid[115].DrawOccupant(l, 0);
      }
    }
    for ( k = colStart; k != colBound; k += deltaX )
      this->combatGrid[13 * j + k].DrawLowerDeadOccupants();
    for ( k = colStart; k != colBound; k += deltaX )
      this->combatGrid[13 * j + k].DrawUpperDeadOccupant();
    for ( l = 0; l < 4; ++l )
    {
      if ( l == 1 )
      {
        for ( k = colStart; k != colBound; k += deltaX )
        {
          if ( this->combatGrid[13 * j + k].combatObjIdx != -1 )
            this->combatGrid[13 * j + k].DrawObstacle();
        }
      }
      for ( k = colStart; k != colBound; k += deltaX )
      {
        v18[0][0].x = 443;
        v18[0][0].y = 153;
        v18[0][1].x = 399;
        v18[0][1].y = 237;
        v18[0][2].x = 399;
        v18[0][2].y = 321;
        v18[0][3].x = 443;
        v18[0][3].y = 405;
        v18[1][0].x = 443;
        v18[1][0].y = 153;
        v18[1][1].x = 399;
        v18[1][1].y = 237;
        v18[1][2].x = 399;
        v18[1][2].y = 321;
        v18[1][3].x = 443;
        v18[1][3].y = 405;
        v18[2][0].x = 443;
        v18[2][0].y = 153;
        v18[2][1].x = 399;
        v18[2][1].y = 237;
        v18[2][2].x = 399;
        v18[2][2].y = 321;
        v18[2][3].x = 443;
        v18[2][3].y = 405;
        v18[3][0].x = 443;
        v18[3][0].y = 153;
        v18[3][1].x = 399;
        v18[3][1].y = 237;
        v18[3][2].x = 399;
        v18[3][2].y = 321;
        v18[3][3].x = 443;
        v18[3][3].y = 405;
        v18[4][0].x = 443;
        v18[4][0].y = 153;
        v18[4][1].x = 399;
        v18[4][1].y = 237;
        v18[4][2].x = 399;
        v18[4][2].y = 321;
        v18[4][3].x = 443;
        v18[4][3].y = 405;
        v18[5][0].x = 443;
        v18[5][0].y = 153;
        v18[5][1].x = 399;
        v18[5][1].y = 237;
        v18[5][2].x = 399;
        v18[5][2].y = 321;
        v18[5][3].x = 443;
        v18[5][3].y = 405;
        v17[0] = 0;
        v17[1] = 4;
        v17[2] = 8;
        v17[3] = 23;
        v17[4] = 27;
        v17[5] = 35;
        v17[6] = 31;
        if ( this->isCastleBattle && !l )
        {
          imageIdx = 0;
          offX = 0;
          offY = 0;
          switch ( k + 13 * j )
          {
            case 9:
              imageIdx = v17[this->wallStatus[0]] + 5;
              break;
            case 34:
              imageIdx = v17[this->wallStatus[1]] + 6;
              break;
            case 86:
              imageIdx = v17[this->wallStatus[2]] + 7;
              break;
            case 113:
              imageIdx = v17[this->wallStatus[3]] + 8;
              break;
            case 22:
              imageIdx = this->turretStatus[0] + 17;
              offX = *(DWORD *)v18[this->castles[1]->factionID] & 0xFFFF;
              offY = v18[this->castles[1]->factionID][0].y;
              break;
            case 47:
              imageIdx = this->turretStatus[1] + 17;
              offX = v18[this->castles[1]->factionID][1].x;
              offY = v18[this->castles[1]->factionID][1].y;
              break;
            case 73:
              imageIdx = this->turretStatus[2] + 17;
              offX = v18[this->castles[1]->factionID][2].x;
              offY = v18[this->castles[1]->factionID][2].y;
              break;
            case 100:
              imageIdx = this->turretStatus[3] + 17;
              offX = v18[this->castles[1]->factionID][3].x;
              offY = v18[this->castles[1]->factionID][3].y;
              break;
            case 59:
              if ( this->drawBridgePosition != 3 )
                imageIdx = 4;
              break;
            default:
              break;
          }
          if ( imageIdx )
            this->combatScreenIcons[5]->CombatClipDrawToBuffer(
              offX,
              offY,
              imageIdx,
              (H2RECT *)((char *)&this->combatGrid[13 * j].drawingBounds + 98 * k),
              0,
              0,
              0,
              0);
        }
        if ( !v21 || k + 13 * j != 114 && k + 13 * j != 115 )
          this->combatGrid[13 * j + k].DrawOccupant(l, 0);
      }
    }
    
    if ( this->isCastleBattle
      && (*((char*)&(this->castles[1]->buildingsBuiltFlags)+1)) & 0x10
      && (j != 4 || this->drawBridgePosition == 4) )
    {
      if ( moatCell[j] != giWalkingTo
        && moatCell[j] != giWalkingTo2
        && moatCell[j] != giWalkingFrom
        && moatCell[j] != giWalkingFrom2 )
      {
        if ( this->combatGrid[moatCell[j]].unitOwner != -1 )
          goto LABEL_150;
      }
      else
      {
        if ( abs(giWalkingTo - giWalkingFrom) <= 1 )
          goto LABEL_150;
        v8 = giWalkingFrom / 13;
        if ( giWalkingFrom / 13 <= giWalkingTo / 13 )
          v8 = giWalkingTo / 13;
        if ( v8 == j )
        {
          if ( gpCombatManager->drawBridgePosition == 4 || giWalkingTo / 13 != 4 && giWalkingFrom / 13 != 4 )
          {
            v10 = giWalkingFrom;
            if ( giWalkingFrom <= giWalkingTo )
              v10 = giWalkingTo;
            v9 = giWalkingYMod + this->combatGrid[giWalkingFrom].occupyingCreatureBottomY - 9;
            IconToBitmap(
              this->combatScreenIcons[14],
              gpWindowManager->screenBuffer,
              0,
              0,
              0,
              1,
              0,
              v9,
              0x280u,
              this->combatGrid[v10].occupyingCreatureBottomY + 5 - v9 + 1,
              0);
          }
          else if ( (giWalkingTo / 13 != 4 || giWalkingFrom / 13 != 3) && (giWalkingTo / 13 != 3 || giWalkingFrom / 13 != 4) )
          {
            if ( giWalkingFrom <= giWalkingTo )
            {
              if ( moatCell[j] == giWalkingTo || moatCell[j] == giWalkingTo2 )
              {
LABEL_150:
                this->combatScreenIcons[13]->CombatClipDrawToBuffer(
                  0,
                  0,
                  j,
                  &this->moatPartBounds[j],
                  0,
                  0,
                  0,
                  0);
                this->combatGrid[moatCell[j] + 19].DrawOccupant(100, 1);
                this->combatGrid[moatCell[j]].DrawOccupant(100, 1);
                this->combatGrid[moatCell[j] + 1].DrawOccupant(100, 1);
                goto LABEL_151;
              }
            }
            else if ( moatCell[j] == giWalkingFrom || moatCell[j] == giWalkingFrom2 )
            {
              goto LABEL_150;
            }
          }
        }
      }
    }
LABEL_151:
    v19 = 0;
  }
  
  if ( *(DWORD *)&combatArmyInfoLevel > 0 && this->field_F543 != -1 )
  {
    this->DrawSmallView(0, 0);
    this->DrawSmallView(1, 0);
  }
  gpMouseManager->couldBeShowMouse = 1;
  PollSound();
  if ( a3 || a4 )
  {
    gbLimitToExtent = 0;
    gbComputeExtent = 0;
    if ( waitUntilItIsTime )
      DelayTil(&glTimers);
    glTimers = (signed __int64)((double)KBTickCount() + (double)delay * gfCombatSpeedMod[giCombatSpeed]);
    gbFullCombatScreenDrawn = 0;
    if ( redrawAll == 1 )
    {
      if ( giMaxExtentY > 442 )
        giMaxExtentY = 442;
      gbEnlargeScreenBlit = 0;
      gpWindowManager->UpdateScreenRegion(
        giMinExtentX,
        giMinExtentY,
        giMaxExtentX - giMinExtentX + 1,
        giMaxExtentY - giMinExtentY + 1);
      gbEnlargeScreenBlit = 1;
    }
  }
  else if ( redrawAll == 1 )
  {
    if ( waitUntilItIsTime )
      DelayTil(&glTimers);
    gbFullCombatScreenDrawn = 1;
    glTimers = (signed __int64)((double)KBTickCount() + (double)delay * gfCombatSpeedMod[giCombatSpeed]);
    this->UpdateCombatArea();
  }
LABEL_168:
  gpMouseManager->couldBeShowMouse = 1;
  PollSound();
}

void combatManager::CycleCombatScreen() {
  this->CycleCombatScreen_orig();
}