# 14-Engine

## 28th of April's Update

### Doom Modifications

##### **Goal:**
The Doom Project had for main goal to try to remake the most of Doom in the engine.

##### **Main Features:**
- Asset Creation.
  The Engine will generate a file with on it the name and type of objects put in it's resource folder.
  It will also create shaders with a user-created prog file. It supports actually:

      . OBJ - Objects / Meshes
      . PNG - Textures
      . vert / frag / geom / tese / tesc - Shaders

- Map Creator
  Another Project was created in parallel of Doom as a Doom Map Maker to facilitate creation of levels.
  It is made with raylib and has these features:
  
      . Place walls
      . Place Floors
      . Place Actors
      . Texture choice for Walls and Floors
      . Action Menu to facilitate modifications
      . Save and Load via WinAPI

##### Secondary Features:
- Raycasts support
- Modified Map Loader originally made by [Joa Bories's](https://github.com/JoaBories) for [it's own engine](https://github.com/JoaBories/KiliEngine).
- UI

### The Game

##### How To Play:
- Mouse to look around
- ZQSD to Move
- E to Interact

##### What is and isn't available :
- Door Locked that can be Unlocked and Interacted
- Switch that can Unlock the referenced Door
- Shooting is implemented and can be activated with space but since nothing has an interaction with it, it's just there.
- Targets exist but since they are underdevelopped, I chose to not show them in this Demo.

---

#### ~~Goals of the Engine~~
- [ ] ~~Support multiple Gravity Types~~
- [ ] ~~Custom Render Pass for Portal Effect~~
- [ ] ~~Source-Like Console for debugging~~
~Next Engine
## Conventions

#### Headers
All headers must be written:   **#include "Directories/header.h"**

Exceptions:
**File.cpp** can have a **File.h** since they must be in the same directory.
Include files not in Engine like **glew.h** or others.

#### Common
Class:       **PascalCase**.
private var: **camelCase**.
static var:  **sPascalCase**.
pointer:     **pPascalCase**.
function:    **PascalCase** (func var **_camelCase**).

#### Variable
Variables are **always** private even **Static** ones.
They are followed by **getters & setters** to permit access & writing if needed.
**Getters & Setters** are camelCase "inline" functions -> always in the header.
**Getters** are always put before **setter**.


#### Classes
Classes are presented as followed:

Class Class
{
private:
    "all variables are here"
public:
    "all get/set-ers are here"

private:
    "private functions here"
public:
    "public functions here"
}

Protected functions & variables does exist if needed in parenting.
