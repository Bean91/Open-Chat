```cpp
utility::matrix forwardPass(std::forward_list<int> tokens)
```
---
## Basic Info
Runs a full forward pass on the tokenized input. It returns the probability distribution for the next token.
### Return Type
Returns a [`utility::matrix`](../utility/matrix.md)
### Parameters
| Parameter | Type                     | Use           | Optional |
|-----------|--------------------------|---------------|----------|
| `tokens`  | `std::forward_list<int>` | List of Token | ❌        |

---
## Example

```cpp
// Calling the forwardPass() function
model m();
utility::matrix dist = m.forwardPass({91, 42});
```