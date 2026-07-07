```cpp
utility::matrix feedForward(utility::matrix x)
```
---
## Basic Info
Returns the transformed matrix to be fed into the next block (or decoding layer) after running through the attention and neural network blocks.
### Return Type
Returns a `utility::matrix`

### Parameters
| Parameter | Type                                     | Use          | Optional |
|-----------|------------------------------------------|--------------|----------|
| `x`       | [`utility::matrix`]("../utility/matrix") | Input matrix | ❌        |
---
## Example

```cpp
// Calling the feedForward() function
block b({128, 512, 128}, 128);
utility::matrix x; // Pass an embedded input matrix
x = b.feedForward(x);
```