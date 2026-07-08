```cpp
std::pair<utility::matrix, std::pair<utility::matrix, utility::matrix>> backward(utility::matrix dZ)
```
---
## Basic Info
Calculates the gradients for the weights and biases, as well as the gradient matrix to be passed back.
### Return Type
Returns `std::pair<utility::matrix, std::pair<utility::matrix, utility::matrix>>`

`backward(dZ).first` is the gradient to be passed backwards, `backward(dZ).second.first` is the gradient for the weights, and `backward(dZ).second.second` is the gradient for the biases.

### Parameters
| Parameter | Type                                        | Use             | Optional |
|-----------|---------------------------------------------|-----------------|----------|
| `dZ`      | [`utility::matrix`]("../utility/matrix.md") | Gradient matrix | ❌        |
---
## Example

```cpp
// Calling the backward() function
utility::matrix dZ;
layer l(42, 420);
l.backward(dZ);
```