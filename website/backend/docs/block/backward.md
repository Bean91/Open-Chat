```cpp
std::pair<utility::matrix, std::pair<std::vector<std::pair<utility::matrix, utility::matrix>>, std::vector<utility::matrix>>> backward(utility::matrix dZ)
```
---
## Basic Info
Returns the gradient to be passed back (`backward(dZ).first`), a vector of the gradients (weights then biases) for each layer of the network (`backward(dZ.second.first)`), and finally a vector of the gradients for each self attention matrix (`backward(dZ.second.second`).
### Return Type
Returns a `std::pair<utility::matrix, std::pair<std::vector<std::pair<utility::matrix, utility::matrix>>, std::vector<utility::matrix>>>`

### Parameters
| Parameter | Type                                     | Use             | Optional |
|-----------|------------------------------------------|-----------------|----------|
| `dZ`      | [`utility::matrix`]("../utility/matrix") | Gradient matrix | ❌        |
---
## Example

```cpp
// Calling the backward() function
block b({128, 512, 128}, 128);
utility::matrix dZ; // Pass a gradient from undoing the unembed and softmax layer at the very end.
dZ = b.backward(dZ).first;
```