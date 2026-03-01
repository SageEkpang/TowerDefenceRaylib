#ifndef PRIMARY_TOWER_H
#define PRIMARY_TOWER_H

#include "BaseTower.h"

class PrimaryTower : public BaseTower
{
public:

    // CLASS FUNCTION(s)
    PrimaryTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile);
    ~PrimaryTower();

    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;


    // GETTER(s)

    // SETTER(s)

};

#endif