## Constructors
```cpp
layer(size_t n_in, size_t n_out)
```
Initializes a new neural network layer with `n_in` input neurons and `n_out` output neurons.

```cpp
layer(std::filesystem::path input)
```
Reads a saved neural network layer.

---
## Basic Info
A layer for a feed forward neural network.

### Instance Variables
| Variable    | Type                                        |
|-------------|---------------------------------------------|
| `weights`   | [`utility::matrix`]("../utility/matrix.md") |
| `biases`    | [`utility::matrix`]("../utility/matrix.md") |
| `X`         | [`utility::matrix`]("../utility/matrix.md") |
| `Z`         | [`utility::matrix`]("../utility/matrix.md") |
| `generator` | `std::default_random_engine`                |
| `initDist`  | `std::normal_distribution<float>`           |
---
## Functions
 - [`backward()`]("./backward.md")
 - [`changeOne()`]("./changeOne.md")
 - [`feedForward()`]("./feedForward.md")
 - [`init()`]("./init.md")
 - [`readFromFile()`]("./readFromFile.md")
 - [`saveToFile()`]("./saveToFile.md")
---
## Example

```cpp
// Initializing a layer
layer l("./bestlayerever.bin");
```