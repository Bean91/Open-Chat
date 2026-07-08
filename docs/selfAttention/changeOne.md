## Overloads
```cpp
void changeOne(char mat, size_t row, size_t col, float d)
```
### Parameters
| Parameter | Type     | Use                        | Optional |
|-----------|----------|----------------------------|----------|
| `mat`     | `char`   | Specifies attention matrix | ❌       |
| `row`     | `size_t` | Specifies row in matrix    | ❌       |
| `col`     | `size_t` | Specifies column in matrix | ❌       |
| `d`       | `float`  | Specifies change to value  | ❌       |
---

## Basic Info
Changes one individual parameter of the attention block

---
## Example

```cpp
// Calling the changeOne() function
selfAttention a(128);
a.changeOne("q", 12, 103, 0.01465);
```