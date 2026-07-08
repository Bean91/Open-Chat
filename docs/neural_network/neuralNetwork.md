## Constructors
```cpp
neuralNetwork(std::vector<size_t> dimensions)
```
Initializes a new neural network following the dimensions passed as paramaters.

```cpp
neuralNetwork(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> input)
```
Reads saved neural network from the inputed filepaths. `input.first` is the dimensions of the network and `input.second` is a vector of each file for each layer of the network.

---
## Basic Info
A feed forward neural network class.

### Instance Variables
| Variable     | Type                                      |
|--------------|-------------------------------------------|
| `network`    | [`std::vector<layer>`](../layer/layer.md) |
| `dimensions` | `std::vector<size_t>`                     |
---
## Functions
 - [`backward()`](./backward.md)
 - [`changeOne()`](./changeOne.md)
 - [`feedForward()`](./feedForward.md)
 - [`init()`](./init.md)
 - [`layerNorm()`](./layerNorm.md)
 - [`readFromFile()`](./readFromFile.md)
 - [`saveToFile()`](./saveToFile.md)
---
## Example

```cpp
// Initializing a neural network
neuralNetwork n("thegreatestneuralnetworktoeverlive.bin");
```