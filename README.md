# Jumbo Eagle

The aim of this project is build a graphical (flow-graph like) framework for ML.
As the block data types are generic, graphs can be made to manipulate images, audio, matrices etc.

## Getting Started

### Prerequisites

The application is built using Qt Creator studio 4.6.2 (community) which can be downloaded for free at : https://www.qt.io/download

You may need to setup the Kits too.

### Installing

1. Download the latest version of [SourceTree](https://www.sourcetreeapp.com/)
2. In SourceTree, pull the [repository](https://github.com/iyop45/JumboEagle)
3. Open the project in Qt and build all.

Let me know if there are any dependancy/compiler issues.

## Running the tests

...

## How Blocks work

- All custom blocks can be found in Core/Graph/Blocks and include some example sources, sinks, and blocks.
- All blocks/sources/sinks must inherit from Block<B,I,O,T> however there are some simple typedefs for common Block templates. 
- The Block, in turn, inherits from \_BlockBase, which is follows the same template parameters and overrides common functionality such as draw, mousemoveevent, and getTabWidget. This class still has access to all the type information as Block.
- The \_BlockBase class then inherits from IBlock which is the interface for all blocks. This is NOT a templated class and so any upcast to this interface loses all the type information. Fortunately, there are some virtual functions that are implemented in \_BlockBase to help infer the template parameters.


## Adding your own Blocks

1. Make a class inside Core/Graph/Blocks that inherits from _Block<B,I,O,T> and overrides the run() function and optionally overrides init()

```
#include "../BlockBase.h"

class MyCustomBlock : public _Block<block_t, int, int, graph_t> { ... }
```

2. #include the header file of your class inside Core/Graph/BlockLoader.h

```
#include "MyCustomBlock.h"
```

3. Add an enum value to block_types in Core/Graph/BlockUtils.h and into the AddBlockDialog form dropdown menu 

The enum name should be specific as the enums will exist in the global scope, and we want to avoid any naming collisions.

```
enum block_types
{
	...
    MYCUSTOMBLOCK = 5
}
```

4. Finally, add the factory constructor function for the new block inside Core/Graph/BlockUtils.cpp map

```
std::map<block_types, std::function<std::shared_ptr<IBlock>()>> block_factory {
	...
    {block_types::MYCUSTOMBLOCK, [](){ return std::make_shared<MyCustomBlock>(); }}
}
```

The plan is to reduce all these steps so that only 1. is necessary. However, it is not quite there yet.

## Components

Unlike utility functions, which have no state, a component is a class which has a state along with a useful interface. 
For example, a plot component can contain all the information/data to draw the plot (state) along with an appropriate draw() function.

Every block has a vector of components (IComponent) which can be accessed using the templated function call getComponent<MyComponent>()
This will return an IComponent which has a big list of optionally overridable functions by the underlying component (this is the best way of doing it for now)

To make a new component, just inherit from IComponent and then optionally override the relevant functions that need to be exposed at the IComponent level. If a virtual function does not exist, just add it in IComponent class.

```
class MyCustomComponent : public IComponent
{
	...
	void draw() override;
}
```

## Contributing

## Versioning

Commit often and regularly. Try to ensure the commit does not break the compilation, however, if it does, just add a [broken] tag to the commit message.

## Authors

* **Roy Miles** - *Initial work* - [iyop45](https://github.com/iyop45)

See also the list of [contributors](https://github.com/JumboEagle/contributors) who participated in this project.

## License

## Acknowledgments