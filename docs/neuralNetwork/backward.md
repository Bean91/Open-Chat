```cpp
std::pair<utility::matrix, std::vector<std::pair<utility::matrix, utility::matrix>>> backward(utility::matrix dZ)
```
---
## Basic Info
Returns the gradient to be passed back (`backward(dZ).first`), a vector of the gradients (weights then biases) for each layer of the network (`backward(dZ.second)`).
### Return Type
Returns a `std::pair<utility::matrix, std::vector<std::pair<utility::matrix, utility::matrix>>>`

### Parameters
| Parameter | Type                                      | Use             | Optional |
|-----------|-------------------------------------------|-----------------|----------|
| `dZ`      | [`utility::matrix`](../utility/matrix.md) | Gradient matrix | ❌       |
---
## Example

```cpp
// Calling the backward() function
neuralNetwork n({128, 512, 128});
utility::matrix dZ; // Pass a gradient from undoing the unembed and softmax layer at the very end.
dZ = n.backward(dZ).first;
```