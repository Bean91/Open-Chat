```cpp
inline matrix scalar_div(matrix a, float b)
```
---
## Basic Info
Divides every value by a scalar.
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
// Calling the scalar_div() function
utility::matrix a;
utility::matrix divisionsimplificationdiv = utility::scalar_div(a, -0.88784939);
```