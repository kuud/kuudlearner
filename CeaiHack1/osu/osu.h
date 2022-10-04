#pragma once

#include "modes.h"

#include "player.h"
#include "game_base.h"
#include "window_utils.h"

// notes for me
// [from where]
// what to get
// 
//#=zdLJxrX5Y0pd7KawJUxF7qjUOhFbS:osu.GameModes.Play.Player
//#=zboyTjqZNouy2Mmigh81wEfRSHUpv_YKS9tB_jrXguuGI:osu.GameplayElements.Beatmaps.Beatmap
//#=zNzTwAPJzPXwhCy4vZTXIPcyyb8CJ:osu.GameplayElements.HitObjectManager
//#=zpUmO61wQkIsTAZfcRW2LpojPNmw6CbS2tw==:osu.GameplayElements.HitObjects.HitObject
//
//[Player]
//hitObjectManager 0x40
//haxCheckCount 0x164
//
//[Beatmap]
//Title 0x24
//Version 0xa8
//DifficultyHpDrainRate 0x34
//DifficultyCircleSize 0x30
//DifficultyOverall 0x38
//DifficultyApproachRate 0x2c
//PlayMode - 0x114
//
//[HitObjectManager]
//Beatmap - 0x30
//ActiveMods[OBFUSCATED] - 0x34
//hitObjects[LIST of HitObject] - 0x48
//
//[HitObject]
//StartTime 0x10
//EndTime 0x14
//Type 0x18
//IsHit 0x84
//BasePosition 0x8C
//
//template <class T>
//T ceaihack::osu::utils::deobfuscate_value(uintptr_t address) {
//	int salt = *(int*)(address + 0x08 + sizeof(T));
//
//	if (T == typeof(string)) {
//
//	else if (T == typeof(int))
//		return *(int*)(address + 0x08) ^ salt;
//	else if (T == typeof(double))
//		return *(double*)(address + 0x08) * (1.0f / salt);
//	else if (T == typeof(float))
//		return *(float*)(address + 0x08) * (1.0f / salt);
//	else if (T == typeof(enum))
//		return (T)(*(int*)(address + 0x08) ^ salt);
//
//	return *(T*)address + 0x08;
//}