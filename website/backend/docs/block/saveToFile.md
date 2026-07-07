```cpp
void saveToFile(std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> output)
```
---
## Basic Info
Saves parameters to files.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                                                                                                     | Use          | Optional |
|-----------|----------------------------------------------------------------------------------------------------------|--------------|----------|
| `output`  | `std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>` | Output files| ❌        |
`output.first.first` is the dimensions of the network, `output.first.second` is a vector of each file for each layer of the network, and `output.second` is the file for the self attention block.
---
## Example

```cpp
// Calling the saveToFile() function
std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path> output; // Fill with your filepaths
block b({128, 512, 128}, 128);
b.saveToFile(output);
```