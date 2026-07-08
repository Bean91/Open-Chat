```cpp
void saveToFile(std::pair<std::filesystem::path, std::vector<std::filesystem::path>> output)
```
---
## Basic Info
Reads from files to initialize the neural network. Used in the constructor.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                                                                    | Use         | Optional |
|-----------|-------------------------------------------------------------------------|-------------|----------|
| `output`   | `std::pair<std::filesystem::path, std::vector<std::filesystem::path>>` | Output files| ❌        |
`output.first` is the dimensions of the network and `output.second` is a vector of each file for each layer of the network.

---
## Example

```cpp
// Calling the saveToFile() function
std::pair<std::filesystem::path, std::vector<std::filesystem::path>> output; // Fill with your filepaths
neuralNetwork n({128, 512, 128});
n.saveToFile(output);
```