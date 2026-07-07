```cpp
void backward(utility::matrix dZ, float lr)
```
---
## Basic Info
Updates the embedding table according to the gradient calculated throughout.
### Return Type
Returns `void`

### Parameters
| Parameter | Type                                        | Use             | Optional |
|-----------|---------------------------------------------|-----------------|----------|
| `dZ`      | [`utility::matrix`]("../utility/matrix.md") | Gradient matrix | ❌        |
| `lr`      | `float`                                     | Learning rate   | ❌        |
---
## Example

```cpp
// Calling the backward() function
embedder e();
e.backward();
```