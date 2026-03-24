#pragma once 
//Do not write anything in it. Auto-Generated in Assets.cpp.

enum GENERATED_TEXTURE
{
    PNG_NullShader,
    PNG_NullTexture,
    PNG_Coin_01,
    PNG_Coin_02,
    PNG_Coin_03,
    PNG_Coin_04,
    PNG_Coin_05,
    PNG_Coin_06,
    PNG_00_megaman,
    PNG_01_megaman,
    PNG_02_megaman,
    PNG_03_megaman,
    PNG_04_megaman,
    PNG_05_megaman,
    PNG_06_megaman,
    PNG_07_megaman,
    PNG_Ball,
    PNG_Block,
    PNG_Bowling_Alley_Alley,
    PNG_Bowling_Alley_Back,
    PNG_Bowling_Alley_BallReturn,
    PNG_Bowling_Alley_Balls,
    PNG_Bowling_Alley_BallsStandee,
    PNG_Bowling_Alley_Bench,
    PNG_Bowling_Alley_Carpet,
    PNG_Bowling_Alley_Chairs,
    PNG_Bowling_Alley_Decals,
    PNG_Bowling_Alley_GutterBot,
    PNG_Bowling_Alley_GutterTop,
    PNG_Bowling_Alley_Panel,
    PNG_Bowling_Alley_Rails,
    PNG_Bowling_Alley_TableBot,
    PNG_Bowling_Alley_TableTop,
    PNG_Bowling_Alley_Trash,
    PNG_Bowling_Alley_Walls,
    PNG_Pin,
    PNG_pokeball,
};

enum GENERATED_MESHES
{
    OBJ_Plane,
    OBJ_cube,
    OBJ_sphere,
    OBJ_Ball,
    OBJ_Bowling_Alley_Alley,
    OBJ_Bowling_Alley_Back,
    OBJ_Bowling_Alley_BallReturn,
    OBJ_Bowling_Alley_Balls,
    OBJ_Bowling_Alley_BallsStandee,
    OBJ_Bowling_Alley_Bench,
    OBJ_Bowling_Alley_Carpet,
    OBJ_Bowling_Alley_Chairs,
    OBJ_Bowling_Alley_Decals,
    OBJ_Bowling_Alley_GutterBot,
    OBJ_Bowling_Alley_GutterTop,
    OBJ_Bowling_Alley_LightWalls,
    OBJ_Bowling_Alley_Panel,
    OBJ_Bowling_Alley_Rails,
    OBJ_Bowling_Alley_TableBot,
    OBJ_Bowling_Alley_TableTop,
    OBJ_Bowling_Alley_Trash,
    OBJ_Bowling_Alley_Walls,
    OBJ_Pin,
};

enum GENERATED_SHADERS
{
    FRAG_NULL,
    VERT_NULL,
    FRAG_BasicModel,
    VERT_BasicModel,
    FRAG_Normal,
    FRAG_Simple,
    VERT_Simple,
    FRAG_SimpleTess,
    TESC_SimpleTess,
    TESE_SimpleTess,
    VERT_SimpleTess,
    FRAG_Sprite,
    VERT_Sprite,
    FRAG_Texture,
    VERT_Texture,
    FRAG_Transparency,
};

static std::string getTexturePath(GENERATED_TEXTURE _texture)
{
   switch (_texture)
	{
   case PNG_NullShader:  return"Engine/.EngineAssets/Textures/NullShader.png";
   case PNG_NullTexture:  return"Engine/.EngineAssets/Textures/NullTexture.png";
   case PNG_Coin_01:  return"Resources/CoinAnim/Coin-01.png";
   case PNG_Coin_02:  return"Resources/CoinAnim/Coin-02.png";
   case PNG_Coin_03:  return"Resources/CoinAnim/Coin-03.png";
   case PNG_Coin_04:  return"Resources/CoinAnim/Coin-04.png";
   case PNG_Coin_05:  return"Resources/CoinAnim/Coin-05.png";
   case PNG_Coin_06:  return"Resources/CoinAnim/Coin-06.png";
   case PNG_00_megaman:  return"Resources/MegaAnim/00_megaman.png";
   case PNG_01_megaman:  return"Resources/MegaAnim/01_megaman.png";
   case PNG_02_megaman:  return"Resources/MegaAnim/02_megaman.png";
   case PNG_03_megaman:  return"Resources/MegaAnim/03_megaman.png";
   case PNG_04_megaman:  return"Resources/MegaAnim/04_megaman.png";
   case PNG_05_megaman:  return"Resources/MegaAnim/05_megaman.png";
   case PNG_06_megaman:  return"Resources/MegaAnim/06_megaman.png";
   case PNG_07_megaman:  return"Resources/MegaAnim/07_megaman.png";
   case PNG_Ball:  return"Resources/Textures/Ball.png";
   case PNG_Block:  return"Resources/Textures/Block.png";
   case PNG_Bowling_Alley_Alley:  return"Resources/Textures/Bowling/Bowling_Alley_Alley.png";
   case PNG_Bowling_Alley_Back:  return"Resources/Textures/Bowling/Bowling_Alley_Back.png";
   case PNG_Bowling_Alley_BallReturn:  return"Resources/Textures/Bowling/Bowling_Alley_BallReturn.png";
   case PNG_Bowling_Alley_Balls:  return"Resources/Textures/Bowling/Bowling_Alley_Balls.png";
   case PNG_Bowling_Alley_BallsStandee:  return"Resources/Textures/Bowling/Bowling_Alley_BallsStandee.png";
   case PNG_Bowling_Alley_Bench:  return"Resources/Textures/Bowling/Bowling_Alley_Bench.png";
   case PNG_Bowling_Alley_Carpet:  return"Resources/Textures/Bowling/Bowling_Alley_Carpet.png";
   case PNG_Bowling_Alley_Chairs:  return"Resources/Textures/Bowling/Bowling_Alley_Chairs.png";
   case PNG_Bowling_Alley_Decals:  return"Resources/Textures/Bowling/Bowling_Alley_Decals.png";
   case PNG_Bowling_Alley_GutterBot:  return"Resources/Textures/Bowling/Bowling_Alley_GutterBot.png";
   case PNG_Bowling_Alley_GutterTop:  return"Resources/Textures/Bowling/Bowling_Alley_GutterTop.png";
   case PNG_Bowling_Alley_Panel:  return"Resources/Textures/Bowling/Bowling_Alley_Panel.png";
   case PNG_Bowling_Alley_Rails:  return"Resources/Textures/Bowling/Bowling_Alley_Rails.png";
   case PNG_Bowling_Alley_TableBot:  return"Resources/Textures/Bowling/Bowling_Alley_TableBot.png";
   case PNG_Bowling_Alley_TableTop:  return"Resources/Textures/Bowling/Bowling_Alley_TableTop.png";
   case PNG_Bowling_Alley_Trash:  return"Resources/Textures/Bowling/Bowling_Alley_Trash.png";
   case PNG_Bowling_Alley_Walls:  return"Resources/Textures/Bowling/Bowling_Alley_Walls.png";
   case PNG_Pin:  return"Resources/Textures/Pin.png";
   case PNG_pokeball:  return"Resources/Textures/pokeball.png";
	}
};

static std::string getMeshPath(GENERATED_MESHES _mesh)
{
   switch (_mesh)
	{
   case OBJ_Plane:  return"Engine/.EngineAssets/Models/Plane.obj";
   case OBJ_cube:  return"Engine/.EngineAssets/Models/cube.obj";
   case OBJ_sphere:  return"Engine/.EngineAssets/Models/sphere.obj";
   case OBJ_Ball:  return"Resources/Models/Ball.obj";
   case OBJ_Bowling_Alley_Alley:  return"Resources/Models/Bowling/Bowling_Alley_Alley.obj";
   case OBJ_Bowling_Alley_Back:  return"Resources/Models/Bowling/Bowling_Alley_Back.obj";
   case OBJ_Bowling_Alley_BallReturn:  return"Resources/Models/Bowling/Bowling_Alley_BallReturn.obj";
   case OBJ_Bowling_Alley_Balls:  return"Resources/Models/Bowling/Bowling_Alley_Balls.obj";
   case OBJ_Bowling_Alley_BallsStandee:  return"Resources/Models/Bowling/Bowling_Alley_BallsStandee.obj";
   case OBJ_Bowling_Alley_Bench:  return"Resources/Models/Bowling/Bowling_Alley_Bench.obj";
   case OBJ_Bowling_Alley_Carpet:  return"Resources/Models/Bowling/Bowling_Alley_Carpet.obj";
   case OBJ_Bowling_Alley_Chairs:  return"Resources/Models/Bowling/Bowling_Alley_Chairs.obj";
   case OBJ_Bowling_Alley_Decals:  return"Resources/Models/Bowling/Bowling_Alley_Decals.obj";
   case OBJ_Bowling_Alley_GutterBot:  return"Resources/Models/Bowling/Bowling_Alley_GutterBot.obj";
   case OBJ_Bowling_Alley_GutterTop:  return"Resources/Models/Bowling/Bowling_Alley_GutterTop.obj";
   case OBJ_Bowling_Alley_LightWalls:  return"Resources/Models/Bowling/Bowling_Alley_LightWalls.obj";
   case OBJ_Bowling_Alley_Panel:  return"Resources/Models/Bowling/Bowling_Alley_Panel.obj";
   case OBJ_Bowling_Alley_Rails:  return"Resources/Models/Bowling/Bowling_Alley_Rails.obj";
   case OBJ_Bowling_Alley_TableBot:  return"Resources/Models/Bowling/Bowling_Alley_TableBot.obj";
   case OBJ_Bowling_Alley_TableTop:  return"Resources/Models/Bowling/Bowling_Alley_TableTop.obj";
   case OBJ_Bowling_Alley_Trash:  return"Resources/Models/Bowling/Bowling_Alley_Trash.obj";
   case OBJ_Bowling_Alley_Walls:  return"Resources/Models/Bowling/Bowling_Alley_Walls.obj";
   case OBJ_Pin:  return"Resources/Models/Pin.obj";
	}
};

static std::string getShaderPath(GENERATED_SHADERS _shader)
{
   switch (_shader)
	{
   case FRAG_NULL:  return"Engine/.EngineAssets/Shaders/NULL.frag";
   case VERT_NULL:  return"Engine/.EngineAssets/Shaders/NULL.vert";
   case FRAG_BasicModel:  return"Resources/Shaders/BasicModel.frag";
   case VERT_BasicModel:  return"Resources/Shaders/BasicModel.vert";
   case FRAG_Normal:  return"Resources/Shaders/Normal.frag";
   case FRAG_Simple:  return"Resources/Shaders/Simple.frag";
   case VERT_Simple:  return"Resources/Shaders/Simple.vert";
   case FRAG_SimpleTess:  return"Resources/Shaders/SimpleTess.frag";
   case TESC_SimpleTess:  return"Resources/Shaders/SimpleTess.tesc";
   case TESE_SimpleTess:  return"Resources/Shaders/SimpleTess.tese";
   case VERT_SimpleTess:  return"Resources/Shaders/SimpleTess.vert";
   case FRAG_Sprite:  return"Resources/Shaders/Sprite.frag";
   case VERT_Sprite:  return"Resources/Shaders/Sprite.vert";
   case FRAG_Texture:  return"Resources/Shaders/Texture.frag";
   case VERT_Texture:  return"Resources/Shaders/Texture.vert";
   case FRAG_Transparency:  return"Resources/Shaders/Transparency.frag";
	}
};
