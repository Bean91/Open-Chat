```cpp
void readFromFile(std::filesystem::path input)
```
---
## Basic Info
Reads embedding table from file.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                    | Use         | Optional |
|-----------|-------------------------|-------------|----------|
| `input`   | `std::filesystem::path` | Input file | ❌        |

---
## Example

```cpp
// Calling the readFromFile() function
std::filesystem::path input; // Fill with your filepath
embedder e(42, 420);
e.readFromFile(input);
```