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
    Model* guardRails =     dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* walls =          dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* lightWalls =     dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* carpet =         dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* panel =          dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* gutterTop =      dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* gutterBot =      dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* alley =          dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* back =           dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* ballReturn =     dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* balls =          dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* ballsStandee =   dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* bench =          dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* chairs =         dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* decals =         dynamic_cast<Model*>(AddComponent(new Model(this, PROG_Transparent)));
    Model* tableTop =       dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* tableBot =       dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Model* trash =          dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));

    guardRails->  setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Rails));
    walls->       setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Walls));
    lightWalls->  setMesh(Assets::GetMesh(OBJ_Bowling_Alley_LightWalls));
    carpet->      setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Carpet));
    panel->       setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Panel));
    gutterTop->   setMesh(Assets::GetMesh(OBJ_Bowling_Alley_GutterBot));
    gutterBot->   setMesh(Assets::GetMesh(OBJ_Bowling_Alley_GutterBot));
    alley->       setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Alley));
    back->        setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Back));
    ballReturn->  setMesh(Assets::GetMesh(OBJ_Bowling_Alley_BallReturn));
    balls->       setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Balls));
    ballsStandee->setMesh(Assets::GetMesh(OBJ_Bowling_Alley_BallsStandee));
    bench->       setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Bench));
    chairs->      setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Chairs));
    decals->      setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Decals));
    tableTop->    setMesh(Assets::GetMesh(OBJ_Bowling_Alley_TableTop));
    tableBot->    setMesh(Assets::GetMesh(OBJ_Bowling_Alley_TableBot));
    trash->       setMesh(Assets::GetMesh(OBJ_Bowling_Alley_Trash));
    
    guardRails->  getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Rails));
    walls->       getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Walls));
    lightWalls->  getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Walls));
    carpet->      getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Carpet));
    panel->       getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Panel));
    gutterTop->   getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_GutterBot));
    gutterBot->   getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_GutterBot));
    alley->       getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Alley));
    back->        getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Back));
    ballReturn->  getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_BallReturn));
    balls->       getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Balls));
    ballsStandee->getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_BallsStandee));
    bench->       getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Bench));
    chairs->      getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Chairs));
    decals->      getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Decals));
    tableTop->    getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_TableTop));
    tableBot->    getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_TableBot));
    trash->       getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_Bowling_Alley_Trash));
    
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
