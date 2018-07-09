## Welcome to the JumboEagle project

The aim of this project is build a graphical (flow-graph like) framework for ML.

### Brief overview of the project structure

All custom blocks can be found in Core/Graph/Blocks and include some example sources, sinks, and blocks. 
In these cases, the objects have been templated to allow different input/output data types (this has since become a very pain to organise).

All blocks/sources/sinks must inherit from Block<B,I,O,T> however there are some simple typedefs for common Block templates.

The Block, in turn, inherits from \_BlockBase, which is follows the same template parameters and overrides common functionality such as draw, mousemoveevent, and getTabWidget. This class still has access to all the type information as Block.

The \_BlockBase class then inherits from IBlock which is the interface for all blocks. This is NOT a templated class and so any upcast to this interface loses all the type information. Fortunately, there are some virtual functions that are implemented in \_BlockBase to help infer the template parameters.


I will clean up this brief description as I aim to have a thorough documentation of the project structure. This is because the code is quite dense with a lot of tightly coupled components which makes it very hard to get involved with directly without a complete understanding of every part.
