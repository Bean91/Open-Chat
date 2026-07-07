## Constructors
```cpp
block(std::vector<size_t> dimensions, size_t n_embd)
```
Initializes a new neural network and self attention blocks following the dimensions passed as paramaters.

```cpp
block(std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> input)
```
Reads saved neural network and self attention blocks from the inputed filepaths. `input.first.first` is the dimensions of the network, `input.first.second` is a vector of each file for each layer of the network, and `input.second` is the file for the self attention block.

---
## Basic Info
A wrapper class that holds a [`neuralNetwork`]("../neural_network/neuralNetwork") and a [`selfAttention`]("../self_attention/selfAttention) block.

### Instance Variables
| Variable    | Type                                                 |
|-------------|------------------------------------------------------|
| `network`   | [`neuralNetwork`]("../neural_network/neuralNetwork") |
| `attention` | [`selfAttention`]("../self_attention/selfAttention") |
| `n_embd`    | `size_t`                                             |
---
## Functions
 - [`backward()`]("./backward")
 - [`changeOne()`]("./changeOne")
 - [`feedForward()`]("./feedForward")
 - [`init()`]("./init")
 - [`readFromFile()`]("./readFromFile")
 - [`saveToFile()`]("./saveToFile")
---
## Example

```cpp
// Initializing a block
block b({128, 512, 128}, 128);
```