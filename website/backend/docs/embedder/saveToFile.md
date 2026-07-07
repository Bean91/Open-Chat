```cpp
void saveToFile(std::filesystem::path input)
```
---
## Basic Info
Saves embedding table to file.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                    | Use         | Optional |
|-----------|-------------------------|-------------|----------|
| `output`   | `std::filesystem::path` | Output file | ❌        |

---
## Example

```cpp
// Calling the saveToFile() function
std::filesystem::path output; // Fill with your filepath
embedder e(42, 420);
e.readFromFile(output);
```