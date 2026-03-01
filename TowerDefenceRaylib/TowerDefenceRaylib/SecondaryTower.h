#ifndef SECONDARY_TOWER_H
#define SECONDARY_TOWER_H

#include "BaseTower.h"

class SecondaryTower : public BaseTower
{
public:

    // CLASS FUNCTION(s)
    SecondaryTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile);
    ~SecondaryTower();

    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;

    // GETTER(s)

    // SETTER(s)

};

#endif