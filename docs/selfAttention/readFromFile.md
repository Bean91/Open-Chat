```cpp
void readFromFile(std::filesystem::path input)
```
---
## Basic Info
Reads from file to initialize the attention blocks. Used in the constructor.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                    | Use         | Optional |
|-----------|-------------------------|-------------|----------|
| `input`   | `std::filesystem::path` | Input file  | ❌       |
---
## Example

```cpp
// Calling the readFromFile() function
std::filesystem::path input; // Fill with your filepath
selfAttention a(128);
a.readFromFile(input);
```