```cpp
void init(size_t n_in)
```
---
## Basic Info
Initializes the embedding table (called in a constructor normally).
### Return Type
Returns `void`
### Parameters
| Parameter | Type     | Use           | Optional |
|-----------|----------|---------------|----------|
| `n_in`    | `size_t` | Input neurons | ❌       |

---
## Example

```cpp
// Calling the init() function
layer l(42, 42);
l.init(42);
```