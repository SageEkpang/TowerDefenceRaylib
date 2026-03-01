#ifndef PRIMARY_ENEMY_H
#define PRIMARY_ENEMY_H

#include "BaseEnemy.h"

class PrimaryEnemy : public BaseEnemy
{
public:

    // CLASS FUNCTION(s)
    PrimaryEnemy(GameManager* gameManager, std::string name, Vector2 position, float size);
    ~PrimaryEnemy();

    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;


    // GETTER(s)

    // SETTER(s)

};

#endif