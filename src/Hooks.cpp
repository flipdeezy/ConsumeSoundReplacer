#include "Hooks.h"
#include "Utility.h"

RE::TESBoundObject* lastEquippedObject;

std::unordered_map<RE::FormID, RE::BGSSoundDescriptorForm*> originalSoundsMap;

void ActorEquipManager::thunk(RE::ActorEquipManager* a_self, RE::Actor* a_actor, RE::TESBoundObject* a_object, std::uint64_t a_unk) {
    logger::info("ActorEquipManager - Equipping object: {}", a_object->GetName());

    if (a_object && a_object->Is(RE::FormType::AlchemyItem)) {
        auto alchemyItem = static_cast<RE::AlchemyItem*>(a_object);
        auto customSound = RE::TESForm::LookupByID<RE::BGSSoundDescriptorForm>(0x03C7BA);
        auto bPlayEquipSound = Utility::GetAnimationVariableBool(a_actor, "bPlayEquipSound");

        if (customSound) {
            logger::info("Custom sound: {}", customSound->GetFormID());
            if (alchemyItem->data.consumptionSound) {
                logger::info("Alchemy item sound: {}", alchemyItem->data.consumptionSound->GetFormID());

                // Store the original sound in the map if not already stored
                if (originalSoundsMap.find(alchemyItem->GetFormID()) == originalSoundsMap.end()) {
                    originalSoundsMap[alchemyItem->GetFormID()] = alchemyItem->data.consumptionSound;
                }

                // Change the sound to the custom sound
                alchemyItem->data.consumptionSound = customSound;

                // Revert the sound if bPlayEquipSound is true
                if (bPlayEquipSound) {
                    auto originalSoundIt = originalSoundsMap.find(alchemyItem->GetFormID());
                    if (originalSoundIt != originalSoundsMap.end()) {
                        alchemyItem->data.consumptionSound = originalSoundIt->second;
                        logger::info("Reverted alchemy item sound to original: {}", originalSoundIt->second->GetFormID());
                        originalSoundsMap.erase(originalSoundIt);
                    }
                }
            } else {
                logger::warn("Alchemy item has no consumption sound!");
            }
        } else {
            logger::warn("Custom sound not found!");
        }
    }

    func(a_self, a_actor, a_object, a_unk);
}

void ActorEquipManager::Install() {
    REL::Relocation<std::uintptr_t> target{RELOCATION_ID(37938, 38894), REL::VariantOffset(0xE5, 0x170, 0xE5)};
    stl::write_thunk_call<ActorEquipManager>(target.address());
    logger::info("ConsumeSoundReplacer Hook Installed");
    logger::info("");
}