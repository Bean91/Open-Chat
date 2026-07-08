```cpp
std::pair<utility::matrix, std::vector<utility::matrix>> backward(utility::matrix dZ)
```
---
## Basic Info
Returns the gradient to be passed back (`backward(dZ).first`) and a vector of the gradients for each self attention matrix (`backward(dZ.second`).
### Return Type
Returns a `std::pair<utility::matrix, std::vector<utility::matrix>>`

### Parameters
| Parameter | Type                                      | Use             | Optional |
|-----------|-------------------------------------------|-----------------|----------|
| `dZ`      | [`utility::matrix`](../utility/matrix.md) | Gradient matrix | ❌        |
---
## Example

```cpp
// Calling the backward() function
selfAttention a( 128);
utility::matrix dZ; // Pass a gradient from undoing the unembed and softmax layer at the very end.
dZ = a.backward(dZ).first;
```