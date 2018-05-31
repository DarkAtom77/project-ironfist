#ifndef HERO_EDIT_H
#define HERO_EDIT_H

#include "adventure/map.h"

int __fastcall EditHeroHandler(tag_message&);
extern int __fastcall EditHeroHandler_orig(tag_message&);
void __stdcall FillInHeroEdit(HeroExtra*);
extern void __stdcall FillInHeroEdit_orig(HeroExtra*);

// The EditHero dialog automatically fills in the artifacts from the base
// game and expansion. To get any extra artifacts defined in the xml file,
// we need to request that a function that runs after EditHero fill in the
// rest. (That function is FillInHeroEdit.)
void requestUserDefinedArtifacts();

#endif
