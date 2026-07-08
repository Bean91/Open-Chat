```cpp
utility::matrix feedForward(utility::matrix x)
```
---
## Basic Info
Returns the transformed matrix to be fed into the next layer (or block).
### Return Type
Returns a `utility::matrix`

### Parameters
| Parameter | Type                                        | Use          | Optional |
|-----------|---------------------------------------------|--------------|----------|
| `x`       | [`utility::matrix`]("../utility/matrix.md") | Input matrix | ❌        |
---
## Example

```cpp
// Calling the feedForward() function
layer l(128, 512);
utility::matrix x; // Pass an embedded input matrix
x = l.feedForward(x);
```