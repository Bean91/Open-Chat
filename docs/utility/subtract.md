```cpp
inline matrix subtract(const matrix& a, const matrix& b)
```
---
## Basic Info
Subtracts (multiplies) two matrices.
### Return Type
Returns a [`utility::matrix`](./matrix.md)
### Parameters
| Parameter | Type                             | Use     | Optional |
|-----------|----------------------------------|---------|----------|
| `a`       | [`utility::matrix`](./matrix.md) | Input A | ❌       |
| `b`       | [`utility::matrix`](./matrix.md) | Input B | ❌       |

---
## Example

```cpp
// Calling the subtract() function
utility::matrix a;
utility::matrix b;
utility::matrix c = utility::subtract(a, b);
```