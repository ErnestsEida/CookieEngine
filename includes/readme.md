# CLASS DESCRIPTIONS
This description guide will skip - __getters__ & __setters__ & __constructors__ - and focus on less known functions and describing what all attributes do. There will be special cases where there will be a constructor or a setter in a table

**ONLY PUBLIC METHODS ARE SHOWN**, considering that private and protected methods are not meant to be used


- [GameObject](#gameobject)
- [Collider](#collider)
- [GraphicsRenderer](#graphicsrenderer)


## GameObject
Class is necessarry to be inherited for every object you want to display or use as child in other gameobjects

### Attributes  
| Accessabilty | Type                   | Name       | Description                                                  |
| ------------ | ---------------------- | ---------- | ------------------------------------------------------------ |
| Private      | float                  | x          | Used in components for position                              |
| Private      | float                  | y          | Used in components for position                              |
| Private      | float                  | mirrorX    | Used to calculate offset coordinates from parent             |
| Private      | float                  | mirrorY    | Used to calculate offset coordinates from parent             |
| Private      | float                  | z          | Used to determine which gameobject to draw first             |
| Private      | string                 | objectName | Can be used for debugging or finding gameobjects             |
| Private      | string                 | tag        | Used in gameobject finding and in Collider helpers           |
| Private      | [Collider*](#collider) | collider   | Can be used in collision detection                           |
| Private      | bool                   | isChild    | Is a flag that stores info if gameobject is a child          |
| Private      | GameObject*            | parent     | Used to update gameobject children                           |
| Private      | vector<GameObject*>    | children   | Every frame these gameobjects get updated as children        |
| Private      | vector<Drawable*>      | drawables  | Every frame this vector gets re-read from main loop and stores drawable components |
| _static_ | int | objectCount | Used in default gameobject creation for objectnames |
| _static_ | vector<GameObject*> | objects | Used in engine main-loop. Stores all created gameobjects |

### Methods
| Return type | Name | Description |
| ----------- | ---- | ----------- |
| vector<GameObject*> | getAllObjects() | **STATIC** Returns all created gameobjects until calling this method |
| vector<GameObject*> | getParentObjects() | **STATIC** Returns all gameobjects that are **NOT** flagged as child |
| vector<GameObject*> | getChildObjects() | **STATIC** Returns all gameobjects that are flagged as child |
| GameObject*         | isColliding(string tag) | if no tag is specified, method returns first gameobject that this object collides with |
| GameObject*         | isCollidingAtPoint(float x, float y, string tag) | **STATIC** Checks if something is colliding at given point |
| void                | move(float x, float y) | Moves gameobject |

## Collider
This class is used in [GameObject](#gameobject) for collisions and their methods

### Attributes
| Accessabilty | Type | Name | Description |
| ------------ | ---- | ---- | ----------- |
| Private      | FloatRect* | area | holds the collision area for gameobject |
| Private      | float | width | Value of collision rectangles width |
| Private      | float | height | Value of collision rectangles height |
| Private      | void* | holder | Stores value of collider holder |

### Methods
There arent any collider methods meant to be used by user, if you're very intersted, you can go through Collider.hpp

## GraphicsRenderer

### Attributes
| Accessabilty | Type | Name | Description |
| ------------ | ---- | ---- | ----------- |
| Private | Vector2f | origin | holds coordinates of drawable origin* |

**origin** - place in a shape or a sprite that it starts drawing from. 

### Methods
| Return type | Name | Description |
| ----------- | ---- | ----------- |
