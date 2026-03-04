#include "BowlingAlley.h"

#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/cModel.h"
#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/Time.h"

BowlingAlley::BowlingAlley() :
    Actor()
{
    mName = "Box";
}

BowlingAlley::~BowlingAlley()
{
}

void BowlingAlley::Start()
{
    Model* guardRails = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* walls = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* lightWalls = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* carpet = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* panel = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* gutterTop = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* gutterBot = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* alley = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* back = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* ballReturn = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* balls = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* ballsStandee = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* bench = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* chairs = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* decals = dynamic_cast<Model*>(AddComponent(new Model(this, "Transparency")));
    Model* tableTop = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* tableBot = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    Model* trash = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));

    guardRails->setMesh(Assets::GetMesh("B_Rails"));
    walls->setMesh(Assets::GetMesh("B_Walls"));
    lightWalls->setMesh(Assets::GetMesh("B_LightWalls"));
    carpet->setMesh(Assets::GetMesh("B_Carpet"));
    panel->setMesh(Assets::GetMesh("B_Panel"));
    gutterTop->setMesh(Assets::GetMesh("B_GutterTop"));
    gutterBot->setMesh(Assets::GetMesh("B_GutterBot"));
    alley->setMesh(Assets::GetMesh("B_Alley"));
    back->setMesh(Assets::GetMesh("B_Back"));
    ballReturn->setMesh(Assets::GetMesh("B_BallReturn"));
    balls->setMesh(Assets::GetMesh("B_Balls"));
    ballsStandee->setMesh(Assets::GetMesh("B_BallsStandee"));
    bench->setMesh(Assets::GetMesh("B_Bench"));
    chairs->setMesh(Assets::GetMesh("B_Chairs"));
    decals->setMesh(Assets::GetMesh("B_Decals"));
    tableTop->setMesh(Assets::GetMesh("B_TableTop"));
    tableBot->setMesh(Assets::GetMesh("B_TableBot"));
    trash->setMesh(Assets::GetMesh("B_Trash"));
    
    guardRails->getMesh()->AddTexture(Assets::GetTexture("B_Rails"));
    walls->getMesh()->AddTexture(Assets::GetTexture("B_Walls"));
    lightWalls->getMesh()->AddTexture(Assets::GetTexture("B_Walls"));
    carpet->getMesh()->AddTexture(Assets::GetTexture("B_Carpet"));
    panel->getMesh()->AddTexture(Assets::GetTexture("B_Panel"));
    gutterTop->getMesh()->AddTexture(Assets::GetTexture("B_GutterTop"));
    gutterBot->getMesh()->AddTexture(Assets::GetTexture("B_GutterBot"));
    alley->getMesh()->AddTexture(Assets::GetTexture("B_Alley"));
    back->getMesh()->AddTexture(Assets::GetTexture("B_Back"));
    ballReturn->getMesh()->AddTexture(Assets::GetTexture("B_BallReturn"));
    balls->getMesh()->AddTexture(Assets::GetTexture("B_Balls"));
    ballsStandee->getMesh()->AddTexture(Assets::GetTexture("B_BallsStandee"));
    bench->getMesh()->AddTexture(Assets::GetTexture("B_Bench"));
    chairs->getMesh()->AddTexture(Assets::GetTexture("B_Chairs"));
    decals->getMesh()->AddTexture(Assets::GetTexture("B_Decals"));
    tableTop->getMesh()->AddTexture(Assets::GetTexture("B_TableTop"));
    tableBot->getMesh()->AddTexture(Assets::GetTexture("B_TableBot"));
    trash->getMesh()->AddTexture(Assets::GetTexture("B_Trash"));
    
    BoxCollider* railLeft = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    BoxCollider* railRight = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    
    railLeft->setOffset(Vector3{-1.0f, 0.2f, 0.05f});
    railLeft->setSize(Vector3{1.0f, 0.05f, 0.1f});
    railLeft->setFriction(0.1f);
    
    railRight->setOffset(Vector3{-1.0f, -0.2f, 0.05f});
    railRight->setSize(Vector3{1.0f, 0.05f, 0.1f});
    railRight->setFriction(0.1f);
    
    Actor::Start();
}

void BowlingAlley::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
}

void BowlingAlley::Destroy()
{
    Actor::Destroy();
}
