#pragma once
#include "Engine/Component.h"
#include "Engine/Utilitaries/CommonLib.h"

class Texture;
class cUISprite : public Component
{
private:
    Texture* mTexture;
    std::string mShader;

    Vector4 mColor {1.0f, 1.0f, 1.0f, 1.0f};
    bool mVisible  { true };
    
public:
    Vector4 getColor() const { return mColor; }
    std::string getShaderName() const { return mShader; }
    bool getVisible() const { return mVisible; }
    Texture* getTexture(const uint16_t _i)  const { return mTexture; }
    
    virtual void setColor(Vector4 _color) { mColor = _color; }
    void setVisible(const bool _newVisibility) { mVisible = _newVisibility; }
    void setTexture(Texture* _t) {mTexture = _t;}

private:
public:
    cUISprite(Actor* _pOwner, std::string _shader);
    ~cUISprite() override;

    void OnStart() override;
    void Update(float _deltaTime) override {}
    virtual void Draw();
    void Destroy() override;

    void SetShader(const std::string _shader);
};
