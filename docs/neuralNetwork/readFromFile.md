```cpp
void readFromFile(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> input)
```
---
## Basic Info
Reads from files to initialize the neural network. Used in the constructor.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                                                                   | Use         | Optional |
|-----------|------------------------------------------------------------------------|-------------|----------|
| `input`   | `std::pair<std::filesystem::path, std::vector<std::filesystem::path>>` | Input files| ❌        |
`input.first` is the dimensions of the network and `input.second` is a vector of each file for each layer of the network.

---
## Example

```cpp
// Calling the readFromFile() function
std::pair<std::filesystem::path, std::vector<std::filesystem::path>> input; // Fill with your filepaths
neuralNetwork n({128, 512, 128});
n.readFromFile(input);
```