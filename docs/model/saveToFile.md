```cpp
void saveToFile(std::pair<std::filesystem::path, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>> files)
```
---
## Basic Info
Saves the entire model to files.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                    | Use          | Optional |
|-----------|-------------------------|--------------|----------|
| `files`   | `std::pair<std::filesystem::path, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>>` | Output files | ❌        |

---
## Example

```cpp
// Calling the saveToFile() function
std::pair<std::filesystem::path, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>> files; // Fill with your filepath
model m();
m.saveToFile(files);
```