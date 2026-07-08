```cpp
void layerNorm(std::vector<float> &x, size_t start, size_t end)
```
---
## Basic Info
Applies a layer norm to the inputted vector.
### Return Type
Returns `void`
### Parameters
| Parameter | Type                     | Use            | Optional |
|-----------|--------------------------|----------------|----------|
| `x`       | `std::vector<float>`     | Input Vector   | ❌       |
| `start`   | `size_t`                 | Index of start | ❌       |
| `end`     | `size_t`                 | Index of end   | ❌       |

---
## Example

```cpp
// Calling the layerNorm() function
neuralNetwork n({128, 512, 128});
n.layerNorm({0.012, 0.4373, -0.463, 0.8747}, 1, 3);
```