```cpp
inline matrix dot(const matrix& a, const matrix& b)
```
---
## Basic Info
Dot products (multiplies) two matrices.
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
// Calling the dot() function
utility::matrix a;
utility::matrix b;
utility::matrix c = utility::dot(a, b);
```