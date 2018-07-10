# Jumbo Eagle

The aim of this project is build a graphical (flow-graph like) framework for ML.

## Generic notes

All custom blocks can be found in Core/Graph/Blocks and include some example sources, sinks, and blocks. 
In these cases, the objects have been templated to allow different input/output data types (this has since become a very pain to organise).

All blocks/sources/sinks must inherit from Block<B,I,O,T> however there are some simple typedefs for common Block templates.

The Block, in turn, inherits from \_BlockBase, which is follows the same template parameters and overrides common functionality such as draw, mousemoveevent, and getTabWidget. This class still has access to all the type information as Block.

The \_BlockBase class then inherits from IBlock which is the interface for all blocks. This is NOT a templated class and so any upcast to this interface loses all the type information. Fortunately, there are some virtual functions that are implemented in \_BlockBase to help infer the template parameters.

## Getting Started

### Prerequisites

The application is built using Qt Creator studio 4.6.2 (community) which can be downloaded for free at : https://www.qt.io/download

### Installing

## Running the tests

...

## Adding your own Blocks

1. Make a class inside Core/Graph/Blocks that inherits from _Block<B,I,O,T> and overrides the run() function and optionally overrides init()

```
#include "../BlockBase.h"

class MyCustomBlock : public _Block<block_t, int, int, graph_t> { ... }
```

2. #include the header file of your class inside Core/Graph/BlockLoader.h

3. Add an enum value to block_types in Core/Graph/BlockUtils.h and into the AddBlockDialog form dropdown menu 

4. Finally, add the factory constructor function for the new block inside Core/Graph/BlockUtils.cpp map

## Deployment

## Built With

## Contributing

## Versioning

## Authors

* **Roy Miles** - *Initial work* - [iyop45](https://github.com/iyop45)

See also the list of [contributors](https://github.com/JumboEagle/contributors) who participated in this project.

## License

## Acknowledgments