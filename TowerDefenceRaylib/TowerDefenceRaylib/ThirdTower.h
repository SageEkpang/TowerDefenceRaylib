#ifndef THIRD_TOWER_H
#define THIRD_TOWER_H

#include "BaseTower.h"

class ThirdTower : public BaseTower
{
public:

    // CLASS FUNCTION(s)
    ThirdTower(GameManager* gameManager, std::string name, Vector2 position, float size, Tile tile);
    ~ThirdTower();

    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;

    // GETTER(s)

    //SETTER(s)

};

#endif