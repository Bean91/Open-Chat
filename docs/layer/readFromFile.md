```cpp
void readFromFile(std::filesystem::path input)
```
---
## Basic Info
Reads layer from file.
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
layer l(42, 420);
l.readFromFile(input);
```