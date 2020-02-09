#include "GameState.hpp"
#include "Engine.hpp"
#include "WorldLoader.hpp"
#include "ActorFactory.hpp"
#include "../Objects/Actor.hpp"

GameState::GameState(const Engine* engine) :
    engine(engine),
    money(0),
    resources{}
{
    
}

void GameState::startGame()
{
    WorldLoader::createWorld(engine, engine->activeWorld());
}

void GameState::actorSelected(Actor* actor, bool bMultiSelect, bool bCommand)
{
    if (bCommand) {
        if (actor->team() == Team::Enemy) {
            for (auto& selectedActor : selectedActors) selectedActor->setTarget(actor);
        }
    }
    else { // selection
        if (actor->team() == Team::Player) {
            if (!bMultiSelect) {
                for (auto& selectedActor : selectedActors) selectedActor->setSelected(false);
                selectedActors.clear();
            }
            selectedActors.push_back(actor);
            actor->setSelected(true);
        }
    }
}

void GameState::terrainSelected(const SDL_Point& position, bool bCommand)
{
    if (bCommand) {
        for (auto& actor : selectedActors) {
            SDL_FPoint dest{ static_cast<float>(position.x), static_cast<float>(position.y) };
            actor->setDestination(dest);
        }
    }
    else {
        for (auto& actor : selectedActors) actor->setSelected(false);
        selectedActors.clear();
    }
}

void GameState::actorKilled(Actor* actor)
{
    auto deleteIter = std::remove(selectedActors.begin(), selectedActors.end(), actor);
    if (deleteIter != selectedActors.end()) selectedActors.erase(deleteIter);
    
    if (actor->team() == Team::Enemy) {
        money += actor->getKillValue();
    }
}

bool GameState::isUnitBuildable(PlayerUnit unit) const
{
    return
        (resources.wood    >= ActorFactory::unitCost(unit, ResourceType::Wood)) &&
        (resources.iron    >= ActorFactory::unitCost(unit, ResourceType::Iron)) &&
        (resources.crystal >= ActorFactory::unitCost(unit, ResourceType::Crystal)) &&
        (resources.wolf    >= ActorFactory::unitCost(unit, ResourceType::Wolf));
}

bool GameState::buildUnit(PlayerUnit unit)
{
    if (!isUnitBuildable(unit)) return false;
    resources.wood    -= ActorFactory::unitCost(unit, ResourceType::Wood);
    resources.iron    -= ActorFactory::unitCost(unit, ResourceType::Iron);
    resources.crystal -= ActorFactory::unitCost(unit, ResourceType::Crystal);
    resources.wolf    -= ActorFactory::unitCost(unit, ResourceType::Wolf);
    ActorFactory::spawnUnit(engine->activeWorld(), unit, {});
    return true;
}
