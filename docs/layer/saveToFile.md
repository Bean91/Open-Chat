```cpp
void saveToFile(std::filesystem::path output)
```
---
## Basic Info
Saves layer to file.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                    | Use         | Optional |
|-----------|-------------------------|-------------|----------|
| `output`  | `std::filesystem::path` | Output file | ❌        |

---
## Example

```cpp
// Calling the saveToFile() function
std::filesystem::path output; // Fill with your filepath
layer l(42, 420);
l.readFromFile(output);
```