# 14-Engine

#### Goals of the Engine
- [ ] Support multiple Gravity Types
- [ ] Custom Render Pass for Portal Effect
- [ ] Source-Like Console for debbuging

#### Conventions

###### Common
Class **PascalCase**;
public var **cameCase**;
private var **mPascalCase**;
function **PascalCase** (func var **_camelCase**);

###### Variable
Variables are **always** private even **Static** ones.
They are followed by **getters & setters** to permit access & writing if needed.

###### Classes
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