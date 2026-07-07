```cpp
void changeOne(size_t tok, size_t dim, float d)
```
---
## Basic Info
Changes one individual parameter of the model

---
### Parameters
| Parameter | Type     | Use                       | Optional |
|-----------|----------|---------------------------|----------|
| `tok`     | `size_t` | Specifies the token ID    | ❌       |
| `dim`     | `size_t` | Specifies the dimension   | ❌       |
| `d`       | `float`  | Specifies change to value | ❌       |
---
## Example

```cpp
// Calling the changeOne() function
embedder e();
e.changeOne(12, 185);
```