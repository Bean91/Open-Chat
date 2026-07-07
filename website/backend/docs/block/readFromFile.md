```cpp
void readFromFile(std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> input)
```
---
## Basic Info
Reads from files to initialize the neural network and attention blocks. Used in the constructor.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                                                                                                     | Use         | Optional |
|-----------|----------------------------------------------------------------------------------------------------------|-------------|----------|
| `input`   | `std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>` | Input files| ❌        |
`input.first.first` is the dimensions of the network, `input.first.second` is a vector of each file for each layer of the network, and `input.second` is the file for the self attention block.
---
## Example

```cpp
// Calling the readFromFile() function
std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> input; // Fill with your filepaths
block b({128, 512, 128}, 128);
b.readFromFile(input);
```