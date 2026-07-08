```cpp
std::forward_list<int> tokenize(std::string input)
```
---
## Basic Info
Encodes a string into a list of tokens.
### Return Type
Returns an `std::forward_list<int>`
### Parameters
| Parameter | Type          | Use          | Optional |
|-----------|---------------|--------------|----------|
| `input`   | `std::string` | Input String | ❌        |

---
## Example

```cpp
// Calling the tokenize() function
model m();
std::forward_list<int> toks = m.tokenize("Hello, World!");
```