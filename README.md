# 14-Engine

#### Goals of the Engine
- [ ] Support multiple Gravity Types
- [ ] Custom Render Pass for Portal Effect
- [ ] Source-Like Console for debbuging

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