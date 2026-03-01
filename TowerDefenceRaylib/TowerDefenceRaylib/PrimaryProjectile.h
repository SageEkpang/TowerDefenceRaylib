#include "BaseProjectile.h"

class PrimaryProjectile : public BaseProjectile
{
public:

    // CLASS FUNCTION(s)
    PrimaryProjectile(GameManager* gameManager, BaseTower* owner, Vector2 position, float size, Vector2 direction, float speed = 100.f, float rotation = 0.f);
    ~PrimaryProjectile();


    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;

    // GETTER(s)

    // SETTER(s)

};