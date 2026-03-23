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

    guardRails->setMesh(Assets::GetMesh(TODO));
    walls->setMesh(Assets::GetMesh(TODO));
    lightWalls->setMesh(Assets::GetMesh(TODO));
    carpet->setMesh(Assets::GetMesh(TODO));
    panel->setMesh(Assets::GetMesh(TODO));
    gutterTop->setMesh(Assets::GetMesh(TODO));
    gutterBot->setMesh(Assets::GetMesh(TODO));
    alley->setMesh(Assets::GetMesh(TODO));
    back->setMesh(Assets::GetMesh(TODO));
    ballReturn->setMesh(Assets::GetMesh(TODO));
    balls->setMesh(Assets::GetMesh(TODO));
    ballsStandee->setMesh(Assets::GetMesh(TODO));
    bench->setMesh(Assets::GetMesh(TODO));
    chairs->setMesh(Assets::GetMesh(TODO));
    decals->setMesh(Assets::GetMesh(TODO));
    tableTop->setMesh(Assets::GetMesh(TODO));
    tableBot->setMesh(Assets::GetMesh(TODO));
    trash->setMesh(Assets::GetMesh(TODO));
    
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
    BoxCollider* floor = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    BoxCollider* gutter = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    
    railLeft->setOffset(Vector3{-1.0f, 0.1055f, 0.05f});
    railLeft->setSize(Vector3{5.0f, 0.02f, 0.1f});
    railLeft->setFriction(0.1f);
    
    railRight->setOffset(Vector3{-1.0f, -0.1055f, 0.05f});
    railRight->setSize(Vector3{5.0f, 0.02f, 0.1f});
    railRight->setFriction(0.1f);
    
    floor->setOffset(Vector3{-1.5f, 0, -0.0025f});
    floor->setSize(Vector3{3.1f, 0.145f, 0.01f});
    floor->setFriction(0.1f);
    
    gutter->setOffset(Vector3{-1.5f, 0, -0.0075f});
    gutter->setSize(Vector3{3.0f, 0.2f, 0.01f});
    gutter->setFriction(0.1f);
    
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
