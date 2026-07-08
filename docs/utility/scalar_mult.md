```cpp
inline matrix scalar_mult(matrix a, float b)
```
---
## Basic Info
Multiplies every value by a scalar.
### Return Type
Returns a [`utility::matrix`](./matrix.md)
### Parameters
| Parameter | Type                             | Use          | Optional |
|-----------|----------------------------------|--------------|----------|
| `a`       | [`utility::matrix`](./matrix.md) | Matrix input | ❌       |
| `b`       | `float`                          | Scalar input | ❌       |

---
## Example

```cpp
// Calling the scalar_mult() function
utility::matrix a;
utility::matrix mulitplechickenscrossedtheroad = utility::scalar_mult(a, 0.12234345);
```