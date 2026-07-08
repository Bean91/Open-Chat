```cpp
void init(float stddev = 0.02)
```
---
## Basic Info
Initializes the embedding table (called in a constructor normally).
### Return Type
Returns `void`
### Parameters
| Parameter | Type    | Use                | Optional |
|-----------|---------|--------------------|----------|
| `stddev`  | `float` | Standard Deviation | ✅       |

---
## Example

```cpp
// Calling the init() function
embedder e(42, 42);
e.init(0.069);
```