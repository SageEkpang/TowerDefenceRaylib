#include "BaseStronghold.h"

class PrimaryStronghold : public BaseStronghold
{
public:

    // CLASS FUNCTION(s)
    PrimaryStronghold(GameManager* gameManager, GridManager* gridManager, std::string name, Vector2 position, float size, float hitBox, float health, float shield, Vector2 shieldPosition, float shieldSize, Tile tile);
    ~PrimaryStronghold();

    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;

    // GETTER FUNCTION(s)

    // SETTER FUNCTION(s)

};